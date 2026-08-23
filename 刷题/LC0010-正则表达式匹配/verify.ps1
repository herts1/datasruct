# Ad-hoc verification for LC0010 (compile + 17 cases + 300 random vs brute)
# NOTE: keep this file 100% ASCII. PS 5.1 reads .ps1 as ANSI/GBK; mis-decoded
# UTF-8 Chinese bytes silently corrupted the $m assignment line (t=1 empty $pb bug).
$ErrorActionPreference = 'Stop'

gcc -O2 -static -std=c11 -o regexmatch_c.exe regexmatch.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc C'; exit 1 }
g++ -O2 -static -std=c++17 -o regexmatch_cpp.exe regexmatch.cpp
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: g++ C++'; exit 1 }
gcc -O2 -static -std=c11 -o brute_c.exe brute.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc brute'; exit 1 }

$fail = $false

# --- official samples + classic cases ---
$cases = @(
    @('aa', 'a', 0),
    @('aa', 'a*', 1),
    @('ab', '.*', 1),
    @('aab', 'c*a*b', 1),
    @('mississippi', 'mis*is*p*.', 0),
    @('aaa', 'a*a', 1),
    @('aaa', 'ab*a*c*a', 1),
    @('a', 'ab*', 1),
    @('bbbba', '.*a*a', 1),
    @('ab', '.*c', 0),
    @('a', 'a.', 0),
    @('aa', 'a', 0),
    @('ab', 'a*', 0),
    @('a', '.', 1),
    @('abc', 'a.c', 1),
    @('abc', 'a..', 1),
    @('abc', 'a...', 0)
)
foreach ($case in $cases) {
    $s = $case[0]; $p = $case[1]; $exp = $case[2]
    Set-Content in.txt "$s $p" -Encoding ascii
    $o1 = (cmd /c "regexmatch_c.exe < in.txt").Trim()
    $o2 = (cmd /c "regexmatch_cpp.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if ($o1 -eq "$exp" -and $o2 -eq "$exp") { Write-Output "PASS: '$s' vs '$p' -> $o1" }
    else { Write-Output "FAIL: '$s' vs '$p' c=$o1 cpp=$o2 exp=$exp"; $fail = $true }
}

# --- random cross-check vs brute (300 cases) ---
$alphabet = 'abcdefghijklmnopqrstuvwxyz'
for ($t = 1; $t -le 300; $t++) {
    $n = Get-Random -Minimum 1 -Maximum 11
    $sb = ''
    for ($i = 0; $i -lt $n; $i++) { $sb += $alphabet[(Get-Random -Maximum 26)] }

    # generate valid pattern: letter / '.' / x* ('*' always follows a char)
    $m = Get-Random -Minimum 1 -Maximum 11
    $pb = ''
    while ($pb.Length -lt $m) {
        $r = Get-Random -Maximum 100
        if ($r -lt 70) { $pb += $alphabet[(Get-Random -Maximum 26)] }
        elseif ($r -lt 85) { $pb += '.' }
        else { $pb += $alphabet[(Get-Random -Maximum 26)]; $pb += '*' }
    }
    $pb = $pb.Substring(0, [Math]::Min($m, $pb.Length))

    Set-Content -Path in.txt -Value "$sb $pb" -Encoding ascii
    $o1 = cmd /c "regexmatch_c.exe < in.txt" 2>&1
    if ($null -eq $o1) { Write-Output "EMPTY t=$t s='$sb' p='$pb'"; $fail = $true; break }
    $o1 = "$o1".Trim()
    $o2 = (cmd /c "regexmatch_cpp.exe < in.txt").Trim()
    $o3 = (cmd /c "brute_c.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if (-not ($o1 -eq $o2 -and $o2 -eq $o3)) {
        Write-Output "MISMATCH t=$t s='$sb' p='$pb' c=$o1 cpp=$o2 brute=$o3"
        $fail = $true
        break
    }
}

if ($fail) { Write-Output 'VERIFY FAIL'; exit 1 } else { Write-Output 'VERIFY PASS: 17 cases + 300 random vs brute (ad-hoc)' }
