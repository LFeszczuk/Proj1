CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

__start__: sortowanie
	./sortowanie

sortowanie: main.o algorytmy.o 
	g++ -Wall -pedantic -std=c++0x -o sortowanie main.o algorytmy.o
	 


main.o:  main.cpp algorytmy.hh
	g++ -c ${CXXFLAGS} -o  main.o main.cpp

algorytmy.o: algorytmy.cpp algorytmy.hh
	g++ -c ${CXXFLAGS} -o algorytmy.o algorytmy.cpp


clean:
	rm -f *.o sortowanie