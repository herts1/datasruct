CC       = gcc
CXX      = g++
CFLAGS   = -O2 -static -std=c11
CXXFLAGS = -O2 -static -std=c++17

all: regexmatch_c.exe regexmatch_cpp.exe brute_c.exe

regexmatch_c.exe: regexmatch.c
	$(CC) $(CFLAGS) -o $@ $<

regexmatch_cpp.exe: regexmatch.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

brute_c.exe: brute.c
	$(CC) $(CFLAGS) -o $@ $<

# canonical test entry: compile + 17 cases + 300 random vs brute
test:
	powershell -NoProfile -ExecutionPolicy Bypass -File verify.ps1

clean:
	del /Q *.exe

.PHONY: all test clean
