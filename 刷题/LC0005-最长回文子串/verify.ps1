# Ad-hoc verification for LC0005 (compile + samples + random cross-check vs brute)
# Usage: run from this directory:  powershell -ExecutionPolicy Bypass -File verify.ps1
$ErrorActionPreference = 'Stop'

gcc -O2 -static -std=c11 -o longestPalindrome_c.exe longestPalindrome.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc C'; exit 1 }
g++ -O2 -static -std=c++17 -o longestPalindrome_cpp.exe longestPalindrome.cpp
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: g++ C++'; exit 1 }
gcc -O2 -static -std=c11 -o brute_c.exe brute.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc brute'; exit 1 }

function Is-Pal([string]$t) {
    $arr = $t.ToCharArray()
    [Array]::Reverse($arr)
    return $t -eq (-join $arr)
}

$fail = $false

# --- official samples ---
foreach ($case in @(@('babad', 3), @('cbbd', 2))) {
    $s = $case[0]; $expectLen = $case[1]
    Set-Content in.txt $s -Encoding ascii
    $o1 = (cmd /c "longestPalindrome_c.exe < in.txt").Trim()
    $o2 = (cmd /c "longestPalindrome_cpp.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if ($o1.Length -eq $expectLen -and $o2.Length -eq $expectLen -and (Is-Pal $o1) -and (Is-Pal $o2)) {
        Write-Output "PASS: sample $s -> '$o1' (len $expectLen)"
    } else {
        Write-Output "FAIL: sample $s c=$o1 cpp=$o2"; $fail = $true
    }
}

# --- random cross-check vs brute (200 cases, n<=20) ---
for ($t = 1; $t -le 200; $t++) {
    $n = Get-Random -Minimum 1 -Maximum 21
    $chars = for ($i = 0; $i -lt $n; $i++) { [char](97 + (Get-Random -Maximum 26)) }
    $s = -join $chars
    Set-Content -Path in.txt -Value $s -Encoding ascii
    $o1 = (cmd /c "longestPalindrome_c.exe < in.txt").Trim()
    $o2 = (cmd /c "longestPalindrome_cpp.exe < in.txt").Trim()
    $o3 = (cmd /c "brute_c.exe < in.txt").Trim()
    Remove-Item in.txt -ErrorAction SilentlyContinue

    $lenOk = ($o1.Length -eq $o2.Length) -and ($o2.Length -eq $o3.Length)
    $palOk = (Is-Pal $o1) -and (Is-Pal $o2) -and (Is-Pal $o3)
    $subOk = $s.Contains($o1) -and $s.Contains($o2) -and $s.Contains($o3)
    if (-not ($lenOk -and $palOk -and $subOk)) {
        Write-Output "MISMATCH t=$t s=$s c=$o1 cpp=$o2 brute=$o3"
        $fail = $true
        break
    }
}

if ($fail) { Write-Output 'VERIFY FAIL'; exit 1 } else { Write-Output 'VERIFY PASS: samples + 200 random cases vs brute (ad-hoc)' }
