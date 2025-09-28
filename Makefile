all: my3proc

my3proc: main3.c
	gcc -std=c99 main3.c -o my3proc

clean:
	rm -f my3proc
