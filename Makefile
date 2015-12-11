P = array
F = -g -Wall -std=c++0x -Wfatal-errors
C = clang++

all: 
	$C $F -o $P test_Array.cpp

self-test: 
	$C $F -o $P self_test.cpp

clean:
	rm *.o $P

