# Ad-hoc verification for LC0015 (compile + cases + 200 random vs brute)
# ASCII only - PS 5.1 mis-decodes UTF-8 Chinese bytes in .ps1 files.
$ErrorActionPreference = 'Stop'

gcc -O2 -static -std=c11 -o threesum_c.exe threesum.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc C'; exit 1 }
g++ -O2 -static -std=c++17 -o threesum_cpp.exe threesum.cpp
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: g++ C++'; exit 1 }
gcc -O2 -static -std=c11 -o brute_c.exe brute.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc brute'; exit 1 }
gcc -O2 -static -std=c11 -o threeSum_test.exe driver.c threeSum_solution.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc leetcode-format'; exit 1 }

function Get-SortedLines($raw) {
    if ($null -eq $raw) { return @() }
    return @($raw) | Sort-Object -Unique
}

$fail = $false

# --- official samples + edge cases ---
# format: input string, expected sorted-unique lines (joined by |)
$cases = @(
    @('6 -1 0 1 2 -1 -4', '-1 -1 2|-1 0 1'),
    @('3 0 1 1', ''),
    @('3 0 0 0', '0 0 0'),
    @('3 -100000 100000 0', '-100000 0 100000'),
    @('5 -2 -2 0 2 2', '-2 0 2'),
    @('4 1 2 -3 0', '-3 1 2'),
    @('6 -4 -1 -1 0 1 2', '-1 -1 2|-1 0 1')
)
foreach ($case in $cases) {
    $inp = $case[0]; $expRaw = $case[1]
    Set-Content in.txt $inp -Encoding ascii
    $l1 = Get-SortedLines (cmd /c "threesum_c.exe < in.txt" 2>&1)
    $l2 = Get-SortedLines (cmd /c "threesum_cpp.exe < in.txt" 2>&1)
    $l3 = Get-SortedLines (cmd /c "threeSum_test.exe < in.txt" 2>&1)
    Remove-Item in.txt -ErrorAction SilentlyContinue
    # expected lines go through the same Sort-Object pipeline for identical ordering
    $expLines = @($expRaw -split '\|' | Where-Object { $_ -ne '' }) | Sort-Object -Unique
    if (($l1 -join '|') -eq ($expLines -join '|') -and ($l2 -join '|') -eq ($expLines -join '|') -and ($l3 -join '|') -eq ($expLines -join '|')) {
        Write-Output "PASS: [$inp] -> $($l1 -join '|')"
    } else {
        Write-Output "FAIL: [$inp] c=[$($l1 -join '|')] cpp=[$($l2 -join '|')] lc=[$($l3 -join '|')] exp=[$($expLines -join '|')]"
        $fail = $true
    }
}

# --- random cross-check vs brute (200 cases, n=3..15, values -10..10) ---
for ($t = 1; $t -le 200; $t++) {
    $n = Get-Random -Minimum 3 -Maximum 16
    $arr = for ($i = 0; $i -lt $n; $i++) { Get-Random -Minimum -10 -Maximum 11 }
    $inp = "$n " + ($arr -join ' ')
    Set-Content -Path in.txt -Value $inp -Encoding ascii
    $l1 = Get-SortedLines (cmd /c "threesum_c.exe < in.txt" 2>&1)
    $l2 = Get-SortedLines (cmd /c "threesum_cpp.exe < in.txt" 2>&1)
    $l3 = Get-SortedLines (cmd /c "threeSum_test.exe < in.txt" 2>&1)
    $l4 = Get-SortedLines (cmd /c "brute_c.exe < in.txt" 2>&1)
    Remove-Item in.txt -ErrorAction SilentlyContinue
    if (-not (($l1 -join '|') -eq ($l2 -join '|') -and ($l2 -join '|') -eq ($l3 -join '|') -and ($l3 -join '|') -eq ($l4 -join '|'))) {
        Write-Output "MISMATCH t=$t [$inp]"
        Write-Output "  c:    $($l1 -join ';')"
        Write-Output "  cpp:  $($l2 -join ';')"
        Write-Output "  lc:   $($l3 -join ';')"
        Write-Output "  brute:$($l4 -join ';')"
        $fail = $true
        break
    }
}

if ($fail) { Write-Output 'VERIFY FAIL'; exit 1 } else { Write-Output 'VERIFY PASS: 7 cases + 200 random vs brute (ad-hoc)' }
