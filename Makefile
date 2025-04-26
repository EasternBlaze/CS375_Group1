all: test

test: main.o testGen.o bruteforce.o kmp.o rabin_karp.o
	gcc main.o testGen.o bruteforce.o kmp.o rabin_karp.o -o test

main.o: main.c
	gcc -c main.c

testGen.o: testGen.c
	gcc -c testGen.c

bruteforce.o: bruteforce.c
	gcc -c bruteforce.c

kmp.o: kmp.c
	gcc -c kmp.c

rabin_karp.o: rabin_karp.c
	gcc -c rabin_karp.c

clean:
	rm -f *.o test test.txt
