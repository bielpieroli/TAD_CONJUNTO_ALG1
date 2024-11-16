all: set.o lista.o arvoreAVL.o
	gcc set.o lista.o arvoreAVL.o main.c -o main -std=c99 -Wall -Werror -lm
run:
	./main
set.o:
	gcc -c set.c -o set.o
lista.o:
	gcc -c lista.c -o lista.o
arvoreAVL.o:
	gcc -c arvoreAVL.c -o arvoreAVL.o
clean:
	rm *.o main caixa.zip
zip:
	zip -r caixa.zip *