CC       = gcc
CXX      = g++
CFLAGS   = -O2 -static -std=c11
CXXFLAGS = -O2 -static -std=c++17

all: threesum_c.exe threesum_cpp.exe brute_c.exe threeSum_test.exe

threesum_c.exe: threesum.c
	$(CC) $(CFLAGS) -o $@ $<

threesum_cpp.exe: threesum.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

brute_c.exe: brute.c
	$(CC) $(CFLAGS) -o $@ $<

threeSum_test.exe: driver.c threeSum_solution.c
	$(CC) $(CFLAGS) -o $@ driver.c threeSum_solution.c

# canonical test entry: compile + 7 cases + 200 random vs brute
test:
	powershell -NoProfile -ExecutionPolicy Bypass -File verify.ps1

clean:
	del /Q *.exe

.PHONY: all test clean
