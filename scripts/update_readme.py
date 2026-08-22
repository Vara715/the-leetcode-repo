import hashlib
import json
import os
import re
import subprocess
import sys
import urllib.request
import urllib.error
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
README_PATH = REPO_ROOT / "README.md"
CACHE_PATH = Path(__file__).resolve().parent / ".metadata_cache.json"

START_MARKER = "<!-- SOLUTIONS:START -->"
END_MARKER = "<!-- SOLUTIONS:END -->"

SKIP_DIRS = {".git", ".github", "scripts", "node_modules"}

# Every extension leetcode_sync.py's LANG_EXT map can produce, plus common
# manually-added languages. Deliberately excludes .txt — an unrecognized
# submission language falling back to .txt is a signal something needs a
# LANG_EXT entry, not something that should silently start appearing here.
SOLUTION_EXTENSIONS = {
    "cpp", "c", "py", "java", "js", "ts", "cs", "go", "kt", "swift",
    "rs", "rb", "scala", "php", "sql",
}
FIELD_ORDER = ["Title", "Platform", "Difficulty", "Link", "Tags", "Summary"]
FIELD_RE = re.compile(r"^\s*\*\s*(\w[\w ]*?):\s*(.*)$")

LIGHTWEIGHT_RE = re.compile(r"^\s*//\s*Problem:\s*(.*)$", re.MULTILINE)

ANTHROPIC_API_KEY = os.environ.get("ANTHROPIC_API_KEY", "")
ANTHROPIC_MODEL = "claude-haiku-4-5-20251001"  # fast + cheap, good enough for a one-liner

GROQ_API_KEY = os.environ.get("GROQ_API_KEY", "")
GROQ_MODEL = "llama-3.3-70b-versatile"  # free tier, OpenAI-compatible endpoint


# ---------------------------------------------------------------------------
# Cache helpers
# ---------------------------------------------------------------------------

def load_cache():
    if CACHE_PATH.exists():
        try:
            return json.loads(CACHE_PATH.read_text())
        except Exception:
            return {}
    return {}


def save_cache(cache):
    CACHE_PATH.write_text(json.dumps(cache, indent=2, sort_keys=True))


def content_hash(text):
    return hashlib.sha256(text.encode("utf-8", errors="ignore")).hexdigest()[:16]


SYNC_STATE_PATH = Path(__file__).resolve().parent / ".leetcode_sync_state.json"


def load_solved_timestamps():
    """slug -> unix timestamp (int), as recorded by leetcode_sync.py from
    LeetCode's own submission timestamp. Used to sort the README by when a
    problem was actually solved, rather than by git commit date (which is
    identical for every file synced in the same run)."""
    if not SYNC_STATE_PATH.exists():
        return {}
    try:
        state = json.loads(SYNC_STATE_PATH.read_text())
        return {slug: int(ts) for slug, ts in state.get("solved_timestamps", {}).items()}
    except Exception:
        return {}


# ---------------------------------------------------------------------------
# File discovery
# ---------------------------------------------------------------------------

def find_cpp_files():
    files = []
    for dirpath, dirnames, filenames in os.walk(REPO_ROOT):
        dirnames[:] = [d for d in dirnames if d not in SKIP_DIRS and not d.startswith(".")]
        for fname in filenames:
            if any(fname.endswith(f".{ext}") for ext in SOLUTION_EXTENSIONS):
                files.append(Path(dirpath) / fname)
    return files


def git_commit_date(path):
    try:
        out = subprocess.check_output(
            ["git", "log", "-1", "--format=%ct", "--", str(path)],
            cwd=REPO_ROOT, stderr=subprocess.DEVNULL, text=True,
        ).strip()
        if out:
            return int(out)
    except Exception:
        pass
    return int(path.stat().st_mtime)


# ---------------------------------------------------------------------------
# 1. Legacy full-header parsing
# ---------------------------------------------------------------------------

def parse_legacy_header(text):
    match = re.search(r"/\*(.*?)\*/", text, re.DOTALL)
    if not match:
        return None
    block = match.group(1)
    if "Title:" not in block:
        return None

    fields = {key: "" for key in FIELD_ORDER}
    current_key = None
    for raw_line in block.splitlines():
        m = FIELD_RE.match(raw_line)
        if m and m.group(1).strip() in FIELD_ORDER:
            current_key = m.group(1).strip()
            fields[current_key] = m.group(2).strip()
        elif current_key:
            cont = raw_line.strip().lstrip("*").strip()
            if cont:
                fields[current_key] = (fields[current_key] + " " + cont).strip()
    return fields


# ---------------------------------------------------------------------------
# 2. LeetCode GraphQL auto-fetch
# ---------------------------------------------------------------------------

LEETCODE_GRAPHQL_URL = "https://leetcode.com/graphql"

LEETCODE_QUERY = """
query questionData($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    title
    difficulty
    content
    topicTags { name }
  }
}
"""


def strip_html(html):
    text = re.sub(r"<[^>]+>", " ", html or "")
    text = re.sub(r"&nbsp;", " ", text)
    text = re.sub(r"&[a-z]+;", " ", text)
    text = re.sub(r"\s+", " ", text).strip()
    return text


def fetch_leetcode_metadata(slug):
    payload = json.dumps({
        "query": LEETCODE_QUERY,
        "variables": {"titleSlug": slug},
    }).encode("utf-8")

    req = urllib.request.Request(
        LEETCODE_GRAPHQL_URL,
        data=payload,
        headers={
            "Content-Type": "application/json",
            "Referer": f"https://leetcode.com/problems/{slug}/",
            "Origin": "https://leetcode.com",
            # LeetCode's endpoint blocks requests without a browser-like UA
            # (the default "Python-urllib/3.x" UA gets rejected outright).
            "User-Agent": (
                "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
                "(KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36"
            ),
            "Accept": "application/json",
        },
    )
    try:
        with urllib.request.urlopen(req, timeout=15) as resp:
            raw = resp.read().decode("utf-8")
            data = json.loads(raw)
    except urllib.error.HTTPError as e:
        body = ""
        try:
            body = e.read().decode("utf-8", errors="ignore")[:300]
        except Exception:
            pass
        print(f"  [leetcode] HTTP {e.code} for slug '{slug}': {body}")
        return None
    except (urllib.error.URLError, TimeoutError, json.JSONDecodeError) as e:
        print(f"  [leetcode] fetch failed for slug '{slug}': {e}")
        return None

    q = data.get("data", {}).get("question")
    if not q:
        print(f"  [leetcode] no question found for slug '{slug}'")
        return None

    plain = strip_html(q.get("content", ""))
    naive_summary = plain[:220].rsplit(" ", 1)[0] + "…" if len(plain) > 220 else plain

    return {
        "Title": q.get("title", slug),
        "Platform": "LeetCode",
        "Difficulty": q.get("difficulty", ""),
        "Link": f"https://leetcode.com/problems/{slug}/",
        "Tags": ", ".join(t["name"] for t in q.get("topicTags", [])),
        "Summary": naive_summary,   # may get refined by Claude below
        "_raw_problem_text": plain,
    }


def slug_from_path(path):
    stem = path.stem
    slug = re.sub(r"[_\s]+", "-", stem).lower()
    slug = re.sub(r"[^a-z0-9\-]", "", slug)
    return slug


# ---------------------------------------------------------------------------
# 3. Lightweight one-line header (non-LeetCode platforms)
# ---------------------------------------------------------------------------

def parse_lightweight_header(text):
    m = LIGHTWEIGHT_RE.search(text)
    if not m:
        return None
    rest = m.group(1)
    fields = {key: "" for key in FIELD_ORDER}
    fields["Title"] = rest.split("|")[0].strip()

    for part in rest.split("|")[1:]:
        if ":" not in part:
            continue
        key, _, val = part.partition(":")
        key = key.strip()
        val = val.strip()
        if key in FIELD_ORDER:
            fields[key] = val
    return fields


# ---------------------------------------------------------------------------
# Claude-generated summary / tags
# ---------------------------------------------------------------------------

def _call_anthropic(prompt, max_tokens):
    payload = json.dumps({
        "model": ANTHROPIC_MODEL,
        "max_tokens": max_tokens,
        "messages": [{"role": "user", "content": prompt}],
    }).encode("utf-8")

    req = urllib.request.Request(
        "https://api.anthropic.com/v1/messages",
        data=payload,
        headers={
            "Content-Type": "application/json",
            "x-api-key": ANTHROPIC_API_KEY,
            "anthropic-version": "2023-06-01",
        },
    )
    with urllib.request.urlopen(req, timeout=30) as resp:
        data = json.loads(resp.read().decode("utf-8"))
    return "".join(b.get("text", "") for b in data.get("content", []) if b.get("type") == "text").strip()


def _call_groq(prompt, max_tokens):
    payload = json.dumps({
        "model": GROQ_MODEL,
        "max_tokens": max_tokens,
        "messages": [{"role": "user", "content": prompt}],
    }).encode("utf-8")

    req = urllib.request.Request(
        "https://api.groq.com/openai/v1/chat/completions",
        data=payload,
        headers={
            "Content-Type": "application/json",
            "Authorization": f"Bearer {GROQ_API_KEY}",
        },
    )
    with urllib.request.urlopen(req, timeout=30) as resp:
        data = json.loads(resp.read().decode("utf-8"))
    return data["choices"][0]["message"]["content"].strip()


def claude_generate(prompt, max_tokens=200):
    """Tries Anthropic first (if key set), then falls back to the free Groq
    tier (if that key is set instead/also). Returns None if neither is
    configured or both calls fail — callers handle None gracefully."""
    if ANTHROPIC_API_KEY:
        try:
            return _call_anthropic(prompt, max_tokens)
        except Exception as e:
            print(f"  [anthropic] generation failed, trying Groq if available: {e}")

    if GROQ_API_KEY:
        try:
            return _call_groq(prompt, max_tokens)
        except Exception as e:
            print(f"  [groq] generation failed: {e}")

    return None


def refine_summary_with_claude(problem_text, code_text, title):
    prompt = (
        "You write terse one-line summaries for a DSA solutions README table. "
        f"Problem title: {title}\n\n"
        f"Problem statement (may be partial): {problem_text[:1500]}\n\n"
        "In ONE sentence (max 25 words), summarize what the problem asks for. "
        "No preamble, no quotes, just the sentence."
    )
    result = claude_generate(prompt, max_tokens=100)
    return result


def summarize_from_code_with_claude(code_text, title):
    prompt = (
        "You write terse one-line summaries for a DSA solutions README table, "
        "based only on the C++ solution code (no problem statement available). "
        f"Problem title: {title}\n\n"
        f"Code:\n{code_text[:3000]}\n\n"
        "In ONE sentence (max 25 words), infer and describe what problem this code solves. "
        "Also suggest 2-4 short comma-separated tags (e.g. Array, Two Pointers, DP). "
        "Respond in exactly this format:\n"
        "Summary: <one sentence>\n"
        "Tags: <tag1, tag2, tag3>"
    )
    result = claude_generate(prompt, max_tokens=150)
    if not result:
        return None, None
    summary_m = re.search(r"Summary:\s*(.+)", result)
    tags_m = re.search(r"Tags:\s*(.+)", result)
    return (
        summary_m.group(1).strip() if summary_m else None,
        tags_m.group(1).strip() if tags_m else None,
    )


# ---------------------------------------------------------------------------
# Per-file resolution
# ---------------------------------------------------------------------------

def resolve_metadata(path, text, rel_path):
    legacy = parse_legacy_header(text)
    if legacy:
        return legacy

    top_folder = rel_path.parts[0].lower() if len(rel_path.parts) > 1 else ""

    if top_folder == "leetcode":
        slug = slug_from_path(path)
        meta = fetch_leetcode_metadata(slug)
        if meta:
            refined = refine_summary_with_claude(meta.pop("_raw_problem_text", ""), text, meta["Title"])
            if refined:
                meta["Summary"] = refined
            return meta

    light = parse_lightweight_header(text)
    if light:
        if not light.get("Platform"):
            light["Platform"] = top_folder.upper() if top_folder else ""
        if not light.get("Summary") or not light.get("Tags"):
            summary, tags = summarize_from_code_with_claude(text, light.get("Title") or path.stem)
            if summary and not light.get("Summary"):
                light["Summary"] = summary
            if tags and not light.get("Tags"):
                light["Tags"] = tags
        return light

    guess_title = path.stem.replace("_", " ").replace("-", " ").title()
    summary, tags = summarize_from_code_with_claude(text, guess_title)
    return {
        "Title": guess_title,
        "Platform": top_folder.upper() if top_folder else "-",
        "Difficulty": "",
        "Link": "",
        "Tags": tags or "",
        "Summary": summary or "No description available — add a header comment.",
    }


# ---------------------------------------------------------------------------
# Table generation
# ---------------------------------------------------------------------------

def build_table_row(rel_path, meta):
    title = meta.get("Title") or rel_path.stem
    platform = meta.get("Platform") or "-"
    difficulty = meta.get("Difficulty") or "-"
    link = meta.get("Link", "")
    tags = meta.get("Tags") or "-"
    summary = meta.get("Summary") or "-"

    title_cell = f"[{title}]({rel_path.as_posix()})"
    problem_cell = f"[Problem]({link})" if link else "-"

    return f"| {title_cell} | {platform} | {difficulty} | {tags} | {summary} | {problem_cell} |"


def generate_table(cache):
    rows = []
    updated_cache = dict(cache)
    seen_content = {}  # content hash -> first file path that had it
    solved_timestamps = load_solved_timestamps()

    for path in sorted(find_cpp_files()):
        text = path.read_text(errors="ignore")
        rel_path = path.relative_to(REPO_ROOT)
        key = rel_path.as_posix()
        h = content_hash(text)
        top_folder = rel_path.parts[0].lower() if len(rel_path.parts) > 1 else ""

        if h in seen_content:
            print(f"[duplicate] {key} has identical content to {seen_content[h]} — skipping row")
            continue
        seen_content[h] = key

        cached = cache.get(key)
        cache_valid = cached and cached.get("hash") == h

        # A cached LeetCode entry with no Link means a previous fetch failed
        # (Cloudflare block, wrong slug, transient error, etc). Don't trust
        # that as a "success" forever — retry it on every run until it works.
        if cache_valid and top_folder == "leetcode" and not cached["meta"].get("Link"):
            cache_valid = False

        if cache_valid:
            meta = cached["meta"]
            print(f"[cache hit] {key}")
        else:
            print(f"[processing] {key}")
            meta = resolve_metadata(path, text, rel_path)
            updated_cache[key] = {"hash": h, "meta": meta}

        # Prefer the real LeetCode solve timestamp (accurate even when many
        # files land in the same git commit). Fall back to git commit date
        # for manually-added files on other platforms.
        slug = path.stem
        sort_ts = solved_timestamps.get(slug) if top_folder == "leetcode" else None
        if sort_ts is None:
            sort_ts = git_commit_date(path)

        rows.append((sort_ts, rel_path, meta))

    rows.sort(key=lambda r: r[0], reverse=True)

    if not rows:
        table = "_No solutions pushed yet._"
    else:
        header = "| Problem | Platform | Difficulty | Tags | Summary | Link |\n"
        header += "|---|---|---|---|---|---|\n"
        body = "\n".join(build_table_row(rel_path, meta) for _, rel_path, meta in rows)
        table = header + body

    return table, updated_cache


# ---------------------------------------------------------------------------
# README rewrite
# ---------------------------------------------------------------------------

def read_text_safely(path):
    """Read a text file even if it wasn't saved as plain UTF-8 (e.g. a file
    saved as UTF-16 by Windows Notepad, or with a UTF-8 BOM). Always returns
    a str; never raises UnicodeDecodeError."""
    raw = path.read_bytes()
    for encoding in ("utf-8", "utf-8-sig", "utf-16"):
        try:
            return raw.decode(encoding)
        except UnicodeDecodeError:
            continue
    return raw.decode("utf-8", errors="replace")


def update_readme():
    if not README_PATH.exists():
        README_PATH.write_text(f"# DSA Solutions\n\n{START_MARKER}\n{END_MARKER}\n", encoding="utf-8")

    content = read_text_safely(README_PATH)
    if START_MARKER not in content or END_MARKER not in content:
        print(f"Markers not found in README.md. Add {START_MARKER} / {END_MARKER} and re-run.")
        sys.exit(1)

    cache = load_cache()
    table, updated_cache = generate_table(cache)
    save_cache(updated_cache)

    new_block = f"{START_MARKER}\n{table}\n{END_MARKER}"
    pattern = re.compile(re.escape(START_MARKER) + r".*?" + re.escape(END_MARKER), re.DOTALL)
    new_content = pattern.sub(new_block, content)

    if new_content != content:
        # Always write back as plain UTF-8 (no BOM), so any weird encoding
        # the file previously had gets normalized going forward.
        README_PATH.write_text(new_content, encoding="utf-8")
        print("README.md updated.")
    else:
        print("README.md already up to date.")


if __name__ == "__main__":
    update_readme()