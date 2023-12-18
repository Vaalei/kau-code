a.out: main.o funktioner.o
	gcc main.o funktioner.o -o a.out
main.o: main.c main.h
	gcc -c main.c
funktioner.o: funktioner.c funktioner.h
	gcc -c funktioner.c
clean:
	rm -f *.o
	rm -f a.out