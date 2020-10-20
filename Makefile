a.out : sample.o logging.o
	g++ -o a sample.o logging.o

sample.o : sample.cpp
	g++ -c sample.cpp -std=c++1y

logging.o : logging.cpp
	g++ -c logging.cpp -std=c++1y

clean :
	rm *.o
	rm a