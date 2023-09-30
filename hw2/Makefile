all: default

default: page_rank.cpp main.cpp
	gcc-13 -std=c++11 -fopenmp -g -O3 -o pr main.cpp page_rank.cpp common/graph.cpp
clean:
	rm -rf pr *~ *.*~
