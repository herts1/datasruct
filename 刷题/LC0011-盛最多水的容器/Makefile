CC       = gcc
CXX      = g++
CFLAGS   = -O2 -static -std=c11
CXXFLAGS = -O2 -static -std=c++17

all: maxarea_c.exe maxarea_cpp.exe brute_c.exe

maxarea_c.exe: maxarea.c
	$(CC) $(CFLAGS) -o $@ $<

maxarea_cpp.exe: maxarea.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

brute_c.exe: brute.c
	$(CC) $(CFLAGS) -o $@ $<

# canonical test entry: compile + 9 cases + 300 random vs brute
test:
	powershell -NoProfile -ExecutionPolicy Bypass -File verify.ps1

clean:
	del /Q *.exe

.PHONY: all test clean
