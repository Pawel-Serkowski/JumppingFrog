all: main

main: main.cpp
	clang++ -o main main.cpp -lncurses