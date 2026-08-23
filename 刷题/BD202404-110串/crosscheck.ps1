# Cross-check Java vs C++ on 100 random small cases (run from project dir)
$ErrorActionPreference = 'Stop'

$fail = $false
for ($t = 1; $t -le 100; $t++) {
    $n = Get-Random -Minimum 1 -Maximum 61
    $k = Get-Random -Minimum 0 -Maximum 61
    $chars = for ($i = 0; $i -lt $n; $i++) { Get-Random -Maximum 2 }
    $s = -join $chars
    Set-Content -Path in.txt -Value "$n $k`n$s" -Encoding ascii
    $j = (cmd /c "java BD202404 < in.txt").Trim()
    $c = (cmd /c "BD202404.exe < in.txt").Trim()
    if ($j -ne $c) {
        Write-Output "MISMATCH t=$t n=$n k=$k s=$s java=$j cpp=$c"
        $fail = $true
        break
    }
}
Remove-Item in.txt -ErrorAction SilentlyContinue
if ($fail) { Write-Output 'CROSSCHECK FAIL'; exit 1 }
else { Write-Output 'CROSSCHECK PASS: Java vs C++ identical on 100 random cases' }
