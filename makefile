rwmain: main.o readerwriter.o
	gcc -pthread readerwriter.o main.o -o rwmain
main.o: main.c readerwriter.h
	gcc -c main.c
readerwriter.o: readerwriter.c readerwriter.h
	gcc -c readerwriter.c
clean:
	rm *.o rwmain
