CC=g++
FLAGS= -Wall 
HPP=*.hpp
EXEC=RayTracer
MAIN=RayTracer1.2.cpp
default: main.o

run: main.o
	./RayTracer
	-rm RayTracer
main.o: $(MAIN)
	$(CC) $(FLAGS) $(HPP) $(MAIN) -o $(EXEC)
