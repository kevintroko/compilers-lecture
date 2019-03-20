#include <stdio.h>
#include <string.h>
#define bufSize 1024
#define PLUS "plus"
#define MINUS "minus"
#define MULT "mult"
#define DIV "div"
#define PRINT "print"
#define ASSIGN "assign"
#define EMPTY "empty"
#define FLOATDCL "floatdcl"
#define INTDCL "intDcl"
#define ID "id"
#define INUM "inum"
#define FNUM "fnum"

int PROG();
int DCLS();
int DCL();
int STMTS();
int STMT();
int EXPR();
int VAL();

char *next;

int test(){
    char *test;
    char* tok;
    test = "float id";
    printf("*test++: %d\n", *test);
    printf("*test++: %d\n", *test);
    printf("*test  : %d\n", *test++);
    printf("*test++: %d\n", *test);
    return 0;
}

int term(char* tok) {
    printf("next: %s\n", next);
    printf("%s ", tok);
    printf("%d\n", *next++ == tok);
    return *next == tok;
}

// PROG  -> Dcls Stmts $
int PROG1() { return DCLS() && STMTS();} 
int PROG() {
    printf("PROG->");
    char *save=next;
    return (next = save, PROG1());
}

// Dcls  -> Dcl Dcls | empty
int DCLS1() { return DCL() && DCLS();}
int DCLS2() { return term(EMPTY);}
int DCLS() {
    printf("DCLS->");
    char *save = next;
    return (next = save, DCLS1()) ||
           (next = save, DCLS2()); }

// Dcl   -> floatdcl id | intDcl id
int DCL1() { return term(FLOATDCL) && term(ID); }
int DCL2() { return term(INTDCL) && term(ID); }
int DCL() {
    printf("DCL->");
    char *save = next;
    return (next = save, DCL1()) ||
           (next = save, DCL2()); }

// Stmts -> Stmt Stmts | empty
int STMTS1() { return STMT() && STMTS();}
int STMTS2() { return term(EMPTY);}
int STMTS() {
    printf("STMTS->");
    char *save = next;
    return (next = save, STMTS1()) ||
           (next = save, STMTS2()); }

// Stmt  -> id assign Val Expr | print id
int STMT1() { return term(ID) && term(ASSIGN) && VAL() && EXPR();}
int STMT2() { return term(PRINT) && term(ID);}
int STMT() {
    printf("STMT->");
    char *save = next;
    return (next = save, STMT1()) ||
           (next = save, STMT2()); }

// Expr  -> plus Val Expr | minus Val Expr | empty
int EXPR1() { return term(PLUS)  && VAL() && EXPR(); }
int EXPR2() { return term(MINUS) && VAL() && EXPR(); }
int EXPR3() { return term(EMPTY); }
int EXPR() {
    printf("EXPR->");
    char *save = next;
    return (next = save, EXPR1()) ||
           (next = save, EXPR2()) ||
           (next = save, EXPR3());
}

// Val   ->  id | inum | fnum
int VAL1(){return term(ID);}
int VAL2(){return term(INUM);}
int VAL3(){return term(FNUM);}
int VAL() {
    printf("VAL->");
    char *save = next;
    return (next = save, VAL1()) ||
           (next = save, VAL2()) ||
           (next = save, VAL3());
}

char *source;
int cursor;
int counter;

int main(int argc, char *argv[]) {
    FILE *fp;
    char buf[bufSize];
    int line = 0;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error while opening the file.\n");
    } else {
        printf("Read file: %s\n------------------------\n", argv[1]);
    }
    next = "floatdcl id";
    PROG();

    // while (fgets(buf, sizeof(buf), fp) != NULL) {
    //     line++;
    //     size_t lineLength = strlen(buf);
    //     buf[lineLength] = '\0';
    //     printf("line %d: %s", num, buf);
    // }
    fclose(fp);
    return 0;
}
