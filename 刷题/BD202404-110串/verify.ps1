# Ad-hoc verification for BD202404 (compile + sample + brute-force cross-check)
# Usage: run from this directory:  powershell -ExecutionPolicy Bypass -File verify.ps1
$ErrorActionPreference = 'Stop'

javac -encoding UTF-8 BD202404.java Brute110.java
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: javac'; exit 1 }
g++ -O2 -static -std=c++17 -o BD202404.exe BD202404.cpp
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: g++'; exit 1 }

$fail = $false

# official sample on both versions
Set-Content in.txt '5 2
11000' -Encoding ascii
$j = (cmd /c "java BD202404 < in.txt").Trim()
$c = (cmd /c "BD202404.exe < in.txt").Trim()
Remove-Item in.txt -ErrorAction SilentlyContinue

if ($j -eq '8' -and $c -eq '8') { Write-Output 'PASS: sample n=5 k=2 11000 -> 8 (java+cpp)' }
else { Write-Output "FAIL: sample java=$j cpp=$c"; $fail = $true }

# brute-force cross-check (exhaustive n=1..10 + random n=11..14)
$brute = (cmd /c "java Brute110" 2>&1 | Out-String)
if ($brute -match 'all .* cases match' -and $brute -match 'expect 8') { Write-Output 'PASS: brute-force cross-check' }
else { Write-Output "FAIL: brute -> $brute"; $fail = $true }

if ($fail) { Write-Output 'VERIFY FAIL'; exit 1 } else { Write-Output 'VERIFY PASS (ad-hoc)' }
