P = array
F = -g -Wall -std=c++0x
C = g++

all: 
	$C $F -o $P test_array.cpp

self-test: 
	$C $F -o $P self_test.cpp

clean:
	rm *.o $P

