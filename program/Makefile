all: compil clean start

compil: tarjan.o generator.o
	g++ tarjan.o generator.o -o out 
	
tarjan.o: tarjan.cpp 
	g++ -c tarjan.cpp

generator.o: generator.cpp
	g++ -c generator.cpp

start:
	./out >> out.txt

clean: 
	rm -rf *.o 
