all: clean assembler.o interpreter.o
	gcc assembler.o interpreter.o pretzel.c -o pretzel

test: clean assembler.o interpreter.o
	gcc assembler.o interpreter.o test.c -o test
	./test

assembler.o:
	gcc -c assembler.c -o assembler.o

interpreter.o:
	gcc -c interpreter.c -o interpreter.o

clean:
	rm -f assembler.o interpreter.o pretzel test
