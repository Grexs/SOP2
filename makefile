all:
	g++ -pthread -Wall -Werror main.cpp
run: main.cpp
	./a.out 10 11 3 7
