# Ad-hoc verification for BD202402 (compile + cross-check + official samples)
# Usage: run from this directory:  powershell -ExecutionPolicy Bypass -File verify.ps1
$ErrorActionPreference = 'Stop'

javac -encoding UTF-8 BD202402.java Verify.java
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: compile error'; exit 1 }

$out = (& java -Xmx1g Verify 2>&1 | Out-String)

$checks = @(
    @{ Name = 'formula-vs-simulate (n=1..10)';  Pattern = 'n=1..10' },
    @{ Name = 'mod-vs-BigInteger (n=1..60)';    Pattern = 'n=1..60' },
    @{ Name = 'sample1 n=3 -> 8';               Pattern = '=> 8' },
    @{ Name = 'sample2 n=10^7 -> 424046265';    Pattern = '424046265' }
)
$fail = $false
foreach ($c in $checks) {
    if ($out -match [regex]::Escape($c.Pattern)) { Write-Output ("PASS: " + $c.Name) }
    else { Write-Output ("FAIL: " + $c.Name + "  (output: " + $out.Trim() + ")"); $fail = $true }
}
if ($fail) { Write-Output 'VERIFY FAIL'; exit 1 } else { Write-Output 'VERIFY PASS (ad-hoc)' }
