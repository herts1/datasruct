# Ad-hoc verification for LC0008 (compile + 5 samples + edge cases + 300 random vs brute)
# Usage: run from this directory:  powershell -ExecutionPolicy Bypass -File verify.ps1
$ErrorActionPreference = 'Stop'

gcc -O2 -static -std=c11 -o myatoi_c.exe myatoi.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc C'; exit 1 }
g++ -O2 -static -std=c++17 -o myatoi_cpp.exe myatoi.cpp
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: g++ C++'; exit 1 }
gcc -O2 -static -std=c11 -o brute_c.exe brute.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc brute'; exit 1 }

$fail = $false

# --- official samples ---
$samples = @(
    @('42', '42'),
    @(' -042', '-42'),
    @('1337c0d3', '1337'),
    @('0-1', '0'),
    @('words and 987', '0')
)
foreach ($case in $samples) {
    $s = $case[0]; $exp = $case[1]
    Set-Content in.txt $s -Encoding ascii
    $o1 = (cmd /c "myatoi_c.exe < in.txt").Trim()
    $o2 = (cmd /c "myatoi_cpp.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if ($o1 -eq $exp -and $o2 -eq $exp) { Write-Output "PASS: sample '$s' -> $o1" }
    else { Write-Output "FAIL: sample '$s' c=$o1 cpp=$o2 exp=$exp"; $fail = $true }
}

# --- edge cases (overflow boundaries, empty, signs, leading zeros, long digits) ---
$edges = @(
    @('2147483647', '2147483647'),
    @('-2147483648', '-2147483648'),
    @('2147483648', '2147483647'),
    @('-2147483649', '-2147483648'),
    @('', '0'),
    @('+', '0'),
    @('-', '0'),
    @('   ', '0'),
    @('+5', '5'),
    @('00000000000000000000000042', '42'),
    @('3.14', '3'),
    @('  -123abc', '-123'),
    @('99999999999999999999999999999999999999999999999999', '2147483647'),
    @('-99999999999999999999999999999999999999999999999999', '-2147483648')
)
foreach ($case in $edges) {
    $s = $case[0]; $exp = $case[1]
    Set-Content in.txt $s -Encoding ascii
    $o1 = (cmd /c "myatoi_c.exe < in.txt").Trim()
    $o2 = (cmd /c "myatoi_cpp.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if ($o1 -eq $exp -and $o2 -eq $exp) { Write-Output "PASS: edge '$s' -> $o1" }
    else { Write-Output "FAIL: edge '$s' c=$o1 cpp=$o2 exp=$exp"; $fail = $true }
}

# --- random cross-check vs brute (300 cases, chars incl space/+/-/. and letters) ---
$charset = ' abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-.'
for ($t = 1; $t -le 300; $t++) {
    $n = Get-Random -Minimum 0 -Maximum 31
    $sb = ''
    for ($i = 0; $i -lt $n; $i++) { $sb += $charset[(Get-Random -Maximum $charset.Length)] }
    Set-Content -Path in.txt -Value $sb -Encoding ascii
    $o1 = (cmd /c "myatoi_c.exe < in.txt").Trim()
    $o2 = (cmd /c "myatoi_cpp.exe < in.txt").Trim()
    $o3 = (cmd /c "brute_c.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if (-not ($o1 -eq $o2 -and $o2 -eq $o3)) {
        Write-Output "MISMATCH t=$t s='$sb' c=$o1 cpp=$o2 brute=$o3"
        $fail = $true
        break
    }
}

if ($fail) { Write-Output 'VERIFY FAIL'; exit 1 } else { Write-Output 'VERIFY PASS: 5 samples + 14 edges + 300 random vs brute (ad-hoc)' }
