import json
import os
import urllib.request
import urllib.error
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
STATE_PATH = Path(__file__).resolve().parent / ".leetcode_sync_state.json"
LEETCODE_DIR = REPO_ROOT / "leetcode"

GRAPHQL_URL = "https://leetcode.com/graphql"

USERNAME = os.environ.get("LEETCODE_USERNAME", "")
SESSION = os.environ.get("LEETCODE_SESSION", "")
CSRF_TOKEN = os.environ.get("LEETCODE_CSRF_TOKEN", "")

UA = (
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
    "(KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36"
)

LANG_EXT = {
    "cpp": "cpp", "c": "c", "python3": "py", "python": "py", "java": "java",
    "javascript": "js", "typescript": "ts", "csharp": "cs", "golang": "go",
    "kotlin": "kt", "swift": "swift", "rust": "rs", "ruby": "rb",
    "scala": "scala", "php": "php",
}

RECENT_AC_QUERY = """
query recentAcSubmissions($username: String!, $limit: Int!) {
  recentAcSubmissionList(username: $username, limit: $limit) {
    id
    title
    titleSlug
    timestamp
  }
}
"""

SUBMISSION_DETAILS_QUERY = """
query submissionDetails($submissionId: Int!) {
  submissionDetails(submissionId: $submissionId) {
    code
    lang { name }
    question { titleSlug }
  }
}
"""


def load_state():
    if STATE_PATH.exists():
        try:
            return json.loads(STATE_PATH.read_text())
        except Exception:
            return {"synced_ids": []}
    return {"synced_ids": []}


def save_state(state):
    STATE_PATH.write_text(json.dumps(state, indent=2))


def _post(query, variables, authenticated):
    payload = json.dumps({"query": query, "variables": variables}).encode("utf-8")
    headers = {
        "Content-Type": "application/json",
        "Referer": "https://leetcode.com",
        "Origin": "https://leetcode.com",
        "User-Agent": UA,
        "Accept": "application/json",
    }
    if authenticated:
        headers["Cookie"] = f"LEETCODE_SESSION={SESSION}; csrftoken={CSRF_TOKEN}"
        headers["x-csrftoken"] = CSRF_TOKEN

    req = urllib.request.Request(GRAPHQL_URL, data=payload, headers=headers)
    with urllib.request.urlopen(req, timeout=15) as resp:
        return json.loads(resp.read().decode("utf-8"))


def fetch_recent_accepted(limit=20):
    if not USERNAME:
        print("LEETCODE_USERNAME not set — cannot check for new submissions.")
        return []
    try:
        data = _post(RECENT_AC_QUERY, {"username": USERNAME, "limit": limit}, authenticated=False)
    except urllib.error.HTTPError as e:
        body = ""
        try:
            body = e.read().decode("utf-8", errors="ignore")[:300]
        except Exception:
            pass
        print(f"Failed to fetch recent accepted submissions: HTTP {e.code}: {body}")
        return []
    except Exception as e:
        print(f"Failed to fetch recent accepted submissions: {e}")
        return []
    return data.get("data", {}).get("recentAcSubmissionList", []) or []


def fetch_submission_code(submission_id):
    if not SESSION or not CSRF_TOKEN:
        print("LEETCODE_SESSION / LEETCODE_CSRF_TOKEN not set — cannot fetch code for this submission.")
        return None
    try:
        data = _post(SUBMISSION_DETAILS_QUERY, {"submissionId": int(submission_id)}, authenticated=True)
    except urllib.error.HTTPError as e:
        body = ""
        try:
            body = e.read().decode("utf-8", errors="ignore")[:300]
        except Exception:
            pass
        print(f"  HTTP {e.code} fetching submission {submission_id}: {body}")
        return None
    except Exception as e:
        print(f"  Failed to fetch code for submission {submission_id}: {e}")
        return None

    details = data.get("data", {}).get("submissionDetails")
    if not details:
        print(f"  No submissionDetails returned for {submission_id} — session may be expired or invalid.")
        return None
    return details


def write_solution_file(slug, lang_name, code):
    ext = LANG_EXT.get(lang_name.lower().replace(" ", ""), "txt")
    LEETCODE_DIR.mkdir(exist_ok=True)
    path = LEETCODE_DIR / f"{slug}.{ext}"
    path.write_text(code)
    return path


def sync():
    state = load_state()
    synced_ids = set(state.get("synced_ids", []))
    solved_timestamps = state.get("solved_timestamps", {})  # slug -> unix timestamp (str)

    submissions = fetch_recent_accepted(limit=60)
    if not submissions:
        print("No recent accepted submissions found (or fetch failed).")
        return

    new_count = 0
    for sub in submissions:
        sub_id = str(sub.get("id"))
        slug = sub.get("titleSlug")
        timestamp = sub.get("timestamp")

        # Always keep the freshest known timestamp for this slug, even if
        # this particular submission id was already synced before (e.g. a
        # re-submission of the same problem) — the README should reflect
        # when you MOST RECENTLY solved it, not just first-sync order.
        if slug and timestamp:
            existing = solved_timestamps.get(slug)
            if existing is None or int(timestamp) > int(existing):
                solved_timestamps[slug] = str(timestamp)

        if sub_id in synced_ids:
            continue

        print(f"[new] {sub.get('title')} (id={sub_id}, slug={slug})")

        details = fetch_submission_code(sub_id)
        if not details:
            print(f"  Skipping {slug} for now — will retry on the next run.")
            continue

        code = details.get("code", "")
        lang_name = (details.get("lang") or {}).get("name", "cpp")

        path = write_solution_file(slug, lang_name, code)
        rel = path.relative_to(REPO_ROOT)
        print(f"  Wrote {rel}")

        synced_ids.add(sub_id)
        new_count += 1

    state["synced_ids"] = sorted(synced_ids)
    state["solved_timestamps"] = solved_timestamps
    save_state(state)
    print(f"Sync complete. {new_count} new solution(s) written.")


if __name__ == "__main__":
    sync()