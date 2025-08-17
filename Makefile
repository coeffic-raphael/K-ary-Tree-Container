# racoeffic@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -I.
GUIFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = main.cpp Complex.cpp test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: clean test run 

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) main.o Complex.o -o main $(GUIFLAGS)

run: main
	./main

test: test_main
	./test_main

test_main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) Complex.o test.o -o test_main

valgrind: main
	valgrind $(VALGRIND_FLAGS) ./main

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o main test_main

.PHONY: all clean valgrind test
