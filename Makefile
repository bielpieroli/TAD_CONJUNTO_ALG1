all: set.o LLRBT.o arvoreAVL.o
	gcc set.o LLRBT.o arvoreAVL.o main.c -o main.exe -std=c99 -Wall -Werror -lm
run: clean all
	valgrind ./main.exe
teste: clean all
	./testar.sh main.exe
set.o:
	gcc -c set.c -o set.o
LLRBT.o:
	gcc -c LLRBT.c -o LLRBT.o
arvoreAVL.o:
	gcc -c arvoreAVL.c -o arvoreAVL.o
clean:
	rm -f *.o main conjunto.zip
	rm -f Testes/*.gerado
	rm -f Testes/*.valgrind
zip:
	zip -r conjunto.zip *