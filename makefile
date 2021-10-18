CC=gcc
CFLAGS= -I -g -lstdc++ -std=c++11

P1: main.cpp scanner.cpp scanner.hpp character.hpp token.hpp
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o main
	rm -f *.gch
	rm P1
