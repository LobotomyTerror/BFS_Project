all: bfs

bfs: main.o
	clang++ main.o -o bfs

main.o: main.cpp Graph.hpp
	clang++ -c main.cpp
	
clean:
	rm *.o
