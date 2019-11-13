all: main.o
	gcc -o test_stat main.o

main.o: main.c
	gcc -c main.c

run:
	./test_stat

clean:
	rm *.o
	rm *~

memcheck:
	valgrind --leak-check:yes ./test_stat
