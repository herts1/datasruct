# Cross-check Java vs C++ for n=1..50 (run from project dir)
# Usage: powershell -ExecutionPolicy Bypass -File crosscheck.ps1
$ErrorActionPreference = 'Stop'

$fail = $false
for ($n = 1; $n -le 50; $n++) {
    Set-Content -Path in.txt -Value "$n" -Encoding ascii
    $javaOut = (cmd /c "java -Xmx1g BD202402 < in.txt").Trim()
    $cppOut  = (cmd /c "BD202402.exe < in.txt").Trim()
    if ($javaOut -ne $cppOut) {
        Write-Output ("MISMATCH n=$n java=$javaOut cpp=$cppOut")
        $fail = $true
    }
}
Remove-Item in.txt -ErrorAction SilentlyContinue
if ($fail) { Write-Output 'CROSSCHECK FAIL'; exit 1 }
else { Write-Output 'CROSSCHECK PASS: Java vs C++ identical for n=1..50' }
