all:
	python3 code_generator.py > example.ac
	lex compiler.l
	gcc lex.yy.c -o compiler -ll
	./compiler > tokens.out
	python3 grammar_analyser.py
	gcc syntax-calc.c -o syntax-calc
	./syntax-calc tokens.txt

cfile:
	gcc syntax-calc.c -o syntax
	./syntax tokens.txt
clean:
	rm -rf syntax
	rm -rf compiler
	rm -rf syntax-calc

# // PROG  -> Dcls Stmts $
# // Dcls  -> Dcl Dcls | empty
# // Dcl   -> floatDcl id | intDcl id
# // Stmts -> Stmt Stmts | empty
# // Stmt  -> id assign Val Expr | print id
# // Expr  -> plus Val Expr | minus Val Expr | empty
# // Val   ->  id | inum | fnum