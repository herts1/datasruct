# Ad-hoc verification for LC0017 (compile + samples + 200 random, 3 impls cross-check)
# ASCII only - PS 5.1 mis-decodes UTF-8 Chinese bytes in .ps1 files.
$ErrorActionPreference = 'Stop'

gcc -O2 -static -std=c11 -o comb_c.exe driver.c letterCombinations.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc C'; exit 1 }
g++ -O2 -static -std=c++17 -o comb_cpp.exe driver.cpp
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: g++ C++'; exit 1 }
gcc -O2 -static -std=c11 -o bfs_c.exe bfs.c
if ($LASTEXITCODE -ne 0) { Write-Output 'VERIFY FAIL: gcc bfs'; exit 1 }

function Get-SortedLines($raw) {
    if ($null -eq $raw) { return @() }
    return @($raw) | Sort-Object -Unique
}

# property check: count = product of letter counts, each combo length = n,
# each char belongs to its digit's mapping, no duplicates
function Test-Valid($lines, $digits) {
    $n = $digits.Length
    $map = @('abc','def','ghi','jkl','mno','pqrs','tuv','wxyz')
    $total = 1
    foreach ($ch in $digits.ToCharArray()) { $total *= $map[([int]$ch - 50)].Length }
    if ($lines.Count -ne $total) { return $false }
    foreach ($ln in $lines) {
        if ($ln.Length -ne $n) { return $false }
        for ($i = 0; $i -lt $n; $i++) {
            if (-not $map[([int]$digits[$i] - 50)].Contains($ln[$i])) { return $false }
        }
    }
    return $true
}

$fail = $false

# --- official samples ---
$samples = @(
    @('23', 'ad|ae|af|bd|be|bf|cd|ce|cf'),
    @('2', 'a|b|c'),
    @('7', 'p|q|r|s')
)
foreach ($case in $samples) {
    $dig = $case[0]; $exp = $case[1]
    Set-Content in.txt $dig -Encoding ascii
    $l1 = Get-SortedLines (cmd /c "comb_c.exe < in.txt" 2>&1)
    $l2 = Get-SortedLines (cmd /c "comb_cpp.exe < in.txt" 2>&1)
    $l3 = Get-SortedLines (cmd /c "bfs_c.exe < in.txt" 2>&1)
    Remove-Item in.txt -ErrorAction SilentlyContinue
    $expLines = @($exp -split '\|') | Sort-Object -Unique
    if (($l1 -join '|') -eq ($expLines -join '|') -and ($l1 -join '|') -eq ($l2 -join '|') -and ($l1 -join '|') -eq ($l3 -join '|')) {
        Write-Output "PASS: digits=$dig -> $($l1.Count) combos"
    } else {
        Write-Output "FAIL: digits=$dig c=[$($l1 -join '|')] cpp=[$($l2 -join '|')] bfs=[$($l3 -join '|')]"
        $fail = $true
    }
}

# --- random cross-check (200 cases, digits 1..4 chars from 2..9) ---
for ($t = 1; $t -le 200; $t++) {
    $n = Get-Random -Minimum 1 -Maximum 5
    $dig = -join (1..$n | ForEach-Object { [char](50 + (Get-Random -Maximum 8)) })  # '2'..'9'
    Set-Content -Path in.txt -Value $dig -Encoding ascii
    $l1 = Get-SortedLines (cmd /c "comb_c.exe < in.txt" 2>&1)
    $l2 = Get-SortedLines (cmd /c "comb_cpp.exe < in.txt" 2>&1)
    $l3 = Get-SortedLines (cmd /c "bfs_c.exe < in.txt" 2>&1)
    Remove-Item in.txt -ErrorAction SilentlyContinue
    $same = (($l1 -join '|') -eq ($l2 -join '|')) -and (($l2 -join '|') -eq ($l3 -join '|'))
    if (-not $same -or -not (Test-Valid $l1 $dig)) {
        Write-Output "MISMATCH t=$t digits=$dig"
        Write-Output "  c=$($l1.Count) cpp=$($l2.Count) bfs=$($l3.Count) valid=$(Test-Valid $l1 $dig)"
        $fail = $true
        break
    }
}

if ($fail) { Write-Output 'VERIFY FAIL'; exit 1 } else { Write-Output 'VERIFY PASS: 3 samples + 200 random (3 impls + property checks) (ad-hoc)' }
