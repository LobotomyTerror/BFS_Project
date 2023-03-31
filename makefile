CXX = clang++
CXXFLAGS = -c -g -Wall -std=c++17

PROGRAM = main2

CPPFILES = main2.cpp

build:
	$(CXX) $(CXXFLAGS) $(CPPFILES)
	$(CXX) -o $(PROGRAM) *.o
run:
	./$(PROGRAM)
clean:
	rm -f $(PROGRAM) *.o
test:
	./$(PROGRAM) test