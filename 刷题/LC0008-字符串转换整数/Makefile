CC       = gcc
CXX      = g++
CFLAGS   = -O2 -static -std=c11
CXXFLAGS = -O2 -static -std=c++17

all: myatoi_c.exe myatoi_cpp.exe brute_c.exe

myatoi_c.exe: myatoi.c
	$(CC) $(CFLAGS) -o $@ $<

myatoi_cpp.exe: myatoi.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

brute_c.exe: brute.c
	$(CC) $(CFLAGS) -o $@ $<

# canonical test entry: compile + 5 samples + 14 edge cases + 300 random vs brute
test:
	powershell -NoProfile -ExecutionPolicy Bypass -File verify.ps1

clean:
	del /Q *.exe

.PHONY: all test clean
