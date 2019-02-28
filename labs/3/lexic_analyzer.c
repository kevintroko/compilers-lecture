/*
-- Author --
Kevin Oswaldo Cabrera Navarro - A01227157

-- Code at --
https://github.com/kevintroko/compilers-lecture/tree/master/labs/03
*/

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <time.h>

#define RE_NUM "^([1-9]+)[0-9]*$"
#define RE_NUM_FLOAT "^[1-9]+.[0-9]+"
#define RE_ID "[a-e|g-h|j-o|q-z]"
#define RE_PRINT "[p]"
#define RE_FLOAT "[f]"
#define RE_INT "[i]"
#define RE_ASS "[=]"
#define RE_PLUS "[+]"
#define RE_MULT "[*]"
#define RE_DIV "[/]"
#define RE_SUB "[-]"
#define RE_COMMENT "^[//]"

char *readFile(char *file_name);
int match(const char *string, const char *pattern);

int main(int argc, char *argv[]) {
    clock_t t;
    t = clock();
    readFile(argv[1]);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Compiler.l took %f seconds to execute \n", time_taken);
    return 0;
}

char *readFile(char *file_name) {
    // FILE handle
    char ch;
    FILE *fp;
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char str[100];

    regex_t regex;
    int reti;
    char msgbuf[100];
    
    while ((ch = fgetc(fp)) != EOF) {
        if (ch==47 && (ch= fgetc(fp) == 47) ) {
            while(ch!=10){
                ch = fgetc(fp);
            }
        } else if (match(&ch, "^[1-9]+") == 1) {
            while(ch!=32 && ch!=10) {
                str[count] = ch; 
                ch = fgetc(fp);
                count++;
            }
            if(match(str, RE_NUM)==1) {
                printf("inum ");
            } else if (match(str, RE_NUM_FLOAT)==1) {
                printf("fnum ");
            }
            memset(str, 0, strlen(str));
            count=0;
        } else  if (match(&ch, RE_ID)==1){
            printf("id ");
        } else  if (match(&ch, RE_PRINT) == 1) {
            printf("print ");
        } else if (match(&ch, RE_FLOAT) == 1) {
            printf("floatdcl ");
        } else if (match(&ch, RE_INT) == 1) {
            printf("intdcl ");
        } else if (match(&ch, RE_PLUS) == 1) {
            printf("sum ");
        } else if (match(&ch, RE_MULT) == 1) {
            printf("mult ");
        } else if (match(&ch, RE_ASS) == 1) {
            printf("assign ");
        } else if (match(&ch, RE_SUB) == 1) {
            printf("substraction ");
        } else if (match(&ch, RE_DIV) == 1) {
            printf("division ");
        } 
    }

    fclose(fp);
    return 0;
}

int match(const char *string, const char *pattern) {
    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return 0;
    int status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
    if (status != 0)
        return 0;
    return 1;

}

/*
    extern FILE *yyin, *yyout; 
    clock_t t; 
    t = clock(); 
    yyin = fopen("example.ac", "r"); 
    yylex(); 
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("Compiler.l took %f seconds to execute \n", time_taken); 
    return 0; 
*/