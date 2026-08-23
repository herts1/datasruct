CC       = gcc
CXX      = g++
CFLAGS   = -O2 -static -std=c11
CXXFLAGS = -O2 -static -std=c++17

all: comb_c.exe comb_cpp.exe bfs_c.exe

comb_c.exe: driver.c letterCombinations.c
	$(CC) $(CFLAGS) -o $@ driver.c letterCombinations.c

comb_cpp.exe: driver.cpp
	$(CXX) $(CXXFLAGS) -o $@ driver.cpp

bfs_c.exe: bfs.c
	$(CC) $(CFLAGS) -o $@ bfs.c

# canonical test entry: compile + 3 samples + 200 random (3 impls + property checks)
test:
	powershell -NoProfile -ExecutionPolicy Bypass -File verify.ps1

clean:
	del /Q *.exe

.PHONY: all test clean
