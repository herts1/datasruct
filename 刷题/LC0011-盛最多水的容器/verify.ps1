# Ad-hoc verification for LC0011 (compile + sample + edges + 300 random vs brute)
# ASCII only - PS 5.1 mis-decodes UTF-8 Chinese bytes in .ps1 files.
$ErrorActionPreference = 'Stop'

gcc -O2 -static -std=c11 -o maxarea_c.exe maxarea.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc C'; exit 1 }
g++ -O2 -static -std=c++17 -o maxarea_cpp.exe maxarea.cpp
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: g++ C++'; exit 1 }
gcc -O2 -static -std=c11 -o brute_c.exe brute.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc brute'; exit 1 }

$fail = $false

# --- official sample + edge cases ---
$cases = @(
    @('9 1 8 6 2 5 4 8 3 7', '49'),
    @('2 1 1', '1'),
    @('2 1 2', '1'),
    @('2 2 1', '1'),
    @('3 1 2 3', '2'),
    @('4 3 1 2 4', '9'),
    @('1 5', '0'),
    @('5 1 100 1 1 1', '4'),
    @('6 4 3 2 1 4', '16')
)
foreach ($case in $cases) {
    $inp = $case[0]; $exp = $case[1]
    Set-Content in.txt $inp -Encoding ascii
    $o1 = (cmd /c "maxarea_c.exe < in.txt").Trim()
    $o2 = (cmd /c "maxarea_cpp.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if ($o1 -eq $exp -and $o2 -eq $exp) { Write-Output "PASS: [$inp] -> $o1" }
    else { Write-Output "FAIL: [$inp] c=$o1 cpp=$o2 exp=$exp"; $fail = $true }
}

# --- random cross-check vs brute (300 cases) ---
for ($t = 1; $t -le 300; $t++) {
    $n = Get-Random -Minimum 1 -Maximum 51
    $arr = for ($i = 0; $i -lt $n; $i++) { Get-Random -Minimum 1 -Maximum 101 }
    $inp = "$n " + ($arr -join ' ')
    Set-Content -Path in.txt -Value $inp -Encoding ascii
    $o1 = (cmd /c "maxarea_c.exe < in.txt").Trim()
    $o2 = (cmd /c "maxarea_cpp.exe < in.txt").Trim()
    $o3 = (cmd /c "brute_c.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if (-not ($o1 -eq $o2 -and $o2 -eq $o3)) {
        Write-Output "MISMATCH t=$t [$inp] c=$o1 cpp=$o2 brute=$o3"
        $fail = $true
        break
    }
}

if ($fail) { Write-Output 'VERIFY FAIL'; exit 1 } else { Write-Output 'VERIFY PASS: 9 cases + 300 random vs brute (ad-hoc)' }
