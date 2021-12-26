# the compiler : gcc for c program, define as g++ program for c++

CC = g++

# compiler flags:
# -g adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings

CFLAGS = -g -Wall -Wextra -pedantic -std=c++11
BIN = a.out
SOURCE = hexGame.cpp testProg.cpp
HEADER = hexGame.h

# the build target executable :

TARGET : all

all: $(HEADER) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) && ./a.out

clean:
	rm all
