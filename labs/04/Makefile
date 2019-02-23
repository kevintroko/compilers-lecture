all:
	python3 code_generator.py > example.ac
	lex compiler.l
	gcc lex.yy.c -o compiler -ll
	./compiler

clean:
	rm -rf *.c
	rm -rf compiler

