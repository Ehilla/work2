.PHONY: all run clear
	
SOURCE_LIST = table.cpp

all: 
#	g++ -ltest -lstdc++ -c vector.cpp -g
	g++ -c $(SOURCE_LIST) -g
	g++ table.o -o main -L . -lHashTest

clean:
	rm *.o main 

run:
	./main
