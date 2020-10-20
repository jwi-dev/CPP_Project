a : test.o logging.o logfile.o logtime.o
	g++ -o a test.o logging.o logfile.o logtime.o

main.o : main.cpp
	g++ -c main.c

logging.o : logging.cpp
	g++ -c logging.cpp

logfile.o : logfile.cpp
	g++ -c logfile.cpp

logtime.o : logtime.cpp
	g++ -c logtime.cpp

clean :
	rm *.o
	rm a
