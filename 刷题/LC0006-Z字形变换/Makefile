CC       = gcc
CXX      = g++
CFLAGS   = -O2 -static -std=c11
CXXFLAGS = -O2 -static -std=c++17

all: zigzag_c.exe zigzag_cpp.exe brute_c.exe

zigzag_c.exe: zigzag.c
	$(CC) $(CFLAGS) -o $@ $<

zigzag_cpp.exe: zigzag.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

brute_c.exe: brute.c
	$(CC) $(CFLAGS) -o $@ $<

# canonical test entry: compile + 3 samples + 300 random cases vs brute
test:
	powershell -NoProfile -ExecutionPolicy Bypass -File verify.ps1

clean:
	del /Q *.exe

.PHONY: all test clean
