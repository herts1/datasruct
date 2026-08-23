# Ad-hoc verification for LC0006 (compile + 3 samples + 300 random vs brute)
# Usage: run from this directory:  powershell -ExecutionPolicy Bypass -File verify.ps1
$ErrorActionPreference = 'Stop'

gcc -O2 -static -std=c11 -o zigzag_c.exe zigzag.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc C'; exit 1 }
g++ -O2 -static -std=c++17 -o zigzag_cpp.exe zigzag.cpp
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: g++ C++'; exit 1 }
gcc -O2 -static -std=c11 -o brute_c.exe brute.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc brute'; exit 1 }

$fail = $false

# --- official samples ---
$samples = @(
    @('PAYPALISHIRING', 3, 'PAHNAPLSIIGYIR'),
    @('PAYPALISHIRING', 4, 'PINALSIGYAHRPI'),
    @('A', 1, 'A')
)
foreach ($case in $samples) {
    $s = $case[0]; $r = $case[1]; $exp = $case[2]
    Set-Content in.txt "$s $r" -Encoding ascii
    $o1 = (cmd /c "zigzag_c.exe < in.txt").Trim()
    $o2 = (cmd /c "zigzag_cpp.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if ($o1 -eq $exp -and $o2 -eq $exp) {
        Write-Output "PASS: sample numRows=$r -> $o1"
    } else {
        Write-Output "FAIL: sample numRows=$r c=$o1 cpp=$o2 exp=$exp"; $fail = $true
    }
}

# --- random cross-check vs brute (300 cases) ---
$charset = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.'
for ($t = 1; $t -le 300; $t++) {
    $n = Get-Random -Minimum 1 -Maximum 31
    $r = Get-Random -Minimum 1 -Maximum 31
    $sb = ''
    for ($i = 0; $i -lt $n; $i++) { $sb += $charset[(Get-Random -Maximum $charset.Length)] }
    Set-Content -Path in.txt -Value "$sb $r" -Encoding ascii
    $o1 = (cmd /c "zigzag_c.exe < in.txt").Trim()
    $o2 = (cmd /c "zigzag_cpp.exe < in.txt").Trim()
    $o3 = (cmd /c "brute_c.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if (-not ($o1 -eq $o2 -and $o2 -eq $o3)) {
        Write-Output "MISMATCH t=$t s=$sb r=$r c=$o1 cpp=$o2 brute=$o3"
        $fail = $true
        break
    }
}

if ($fail) { Write-Output 'VERIFY FAIL'; exit 1 } else { Write-Output 'VERIFY PASS: 3 samples + 300 random vs brute (ad-hoc)' }
