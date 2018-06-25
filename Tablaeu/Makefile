clean:
	rm -rf *.o *.so out
all:
	clang++ -c Rover.cpp -o Rover.o -std=c++11
	clang++ -shared Rover.o -o libRover.so
	clang++ -c main.cpp -o main.o -std=c++11
	clang++ main.o ./libRover.so -lm -o out
