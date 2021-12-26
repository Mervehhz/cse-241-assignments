# the compiler : gcc for c program, define as g++ program for c++

CC = g++

# compiler flags:
# -g adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings

CFLAGS = -g -Wall -Wextra -pedantic -std=c++11
BIN = a.out
SOURCE = driver.cpp hexGame.cpp hexVector.cpp hexArray1D.cpp
HEADER = hexGame.h hexAdapter.h hexVector.h hexArray1D.h

# the build target executable :

TARGET : all

all: $(HEADER) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) && ./a.out

clean:
	rm all