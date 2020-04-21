COMPILER=g++
CFLAGS=-std=c++11 -O2 -Werror -static
FILES=main.cpp retrieve.cpp download.cpp
OUTPUTFILE=whazzup

all:
	$(COMPILER) $(CFLAGS) $(FILES) -o ./$(OUTPUTFILE)
