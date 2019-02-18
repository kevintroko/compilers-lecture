all:
	python3 code_generator.py > example.ac
	gcc lex.c -o lex
	./lex example.ac
clear:
	rm -rf lex