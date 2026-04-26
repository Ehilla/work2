.PHONY: all run clear
	
SOURCE_LIST = stack.cpp

all: 
#	g++ -ltest -lstdc++ -c vector.cpp -g
	g++ -c $(SOURCE_LIST) -g
	g++ stack.o -o main -L . -lStackTest

clean:
	rm *.o main 

run:
	./main
