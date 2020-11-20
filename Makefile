l.out: main.o
	gcc -o l.out main.o
main.o: main.c
	gcc -c main.c
run: l.out
	./l.out