%{
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
%}

%%
([1-9][0-9]*)|0       printf("inum");           
[0]+[0-9]+            printf("inum syntax error");
[0-9]+?(\.[0-9]+)     printf("fnum");
[a-eg-hj-oq-z]        printf("id");
f                     printf("floatdcl");
[a-z]+[a-z]+          printf("syntax error");
i                     printf("intdcl");
p                     printf("print");
^[\/\/].*             printf("COMMENT");
[+]                   printf("plus");
[\/]                  printf("div");
[-]                   printf("minus");
[=]                   printf("assign");
              
%%


int main() {

    extern FILE *yyin, *yyout; 
    clock_t t; 
    t = clock(); 
    yyin = fopen("example.ac", "r"); 
    yylex(); 
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("Compiler.l took %f seconds to execute \n", time_taken); 
    return 0; 
}

// https://www.overleaf.com/read/zjrgftwygcfp