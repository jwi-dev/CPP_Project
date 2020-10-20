a : test.o logging.o logfile.o logtime.o
	g++ -o a test.o logging.o logfile.o logtime.o

main.o : main.cpp
	g++ -c main.c -std=c++1y

logging.o : logging.cpp
	g++ -c logging.cpp -std=c++1y

logfile.o : logfile.cpp
	g++ -c logfile.cpp -std=c++1y

logtime.o : logtime.cpp
	g++ -c logtime.cpp -std=c++1y

clean :
	rm *.o
	rm a
