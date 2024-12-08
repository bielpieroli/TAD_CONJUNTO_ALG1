all: set.o lista.o arvoreAVL.o
	gcc set.o lista.o arvoreAVL.o main.c -o main -std=c99 -Wall -Werror -lm
run: clean all
	valgrind ./main
set.o:
	gcc -c set.c -o set.o
lista.o:
	gcc -c lista.c -o lista.o
arvoreAVL.o:
	gcc -c arvoreAVL.c -o arvoreAVL.o
clean:
	rm -f *.o main conjunto.zip
zip:
	zip -r conjunto.zip *