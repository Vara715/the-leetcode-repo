# push.ps1
# Usage: .\push.ps1 "Added daily solution 7"
#
# Commits + pushes. If the push is rejected because the README-bot pushed a
# commit in the meantime, automatically pulls with --rebase and retries once.

param(
    [Parameter(Mandatory = $true)]
    [string]$Message
)

git add .
git commit -m $Message

git push origin main
if ($LASTEXITCODE -ne 0) {
    Write-Host "Push rejected (likely the README bot's commit) — syncing and retrying..." -ForegroundColor Yellow
    git pull origin main --rebase
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Rebase failed — resolve conflicts manually, then run: git rebase --continue; git push origin main" -ForegroundColor Red
        exit 1
    }
    git push origin main
}

if ($LASTEXITCODE -eq 0) {
    Write-Host "Done." -ForegroundColor Green
} else {
    Write-Host "Push still failing — check the error above." -ForegroundColor Red
}