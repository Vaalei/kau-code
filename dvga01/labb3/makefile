a.out: main.o file.o
	gcc main.o file.o -o a.out
main.o: main.c main.h
	gcc -c main.c
file.o: file.c file.h
	gcc -c file.c
clean:
	rm -f *.o
	rm -f a.out