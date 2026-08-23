# Root-level canonical test entry: run verification for every problem subdir.
# ASCII only - PS 5.1 mis-decodes UTF-8 Chinese bytes in .ps1 files.
$ErrorActionPreference = 'Stop'

$root = $PSScriptRoot
$fail = $false
$count = 0

Get-ChildItem -Directory $root | Sort-Object Name | ForEach-Object {
    $v = Join-Path $_.FullName 'verify.ps1'
    if (Test-Path $v) {
        $count++
        Push-Location $_.FullName
        $out = (powershell -NoProfile -ExecutionPolicy Bypass -File $v 2>&1 | Out-String)
        Pop-Location
        if ($out -match 'VERIFY PASS') { Write-Output "PASS: $($_.Name)" }
        else { Write-Output "FAIL: $($_.Name) -> $out"; $fail = $true }
    }
}

if ($count -eq 0) { Write-Output 'ROOT VERIFY FAIL: no verify.ps1 found'; exit 1 }
if ($fail) { Write-Output 'ROOT VERIFY FAIL'; exit 1 }
Write-Output "ROOT VERIFY PASS: $count problems verified (ad-hoc)"
