%{
#include <stdio.h>
#include <stdlib.h>
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
^[\/\/].*             printf("comment");
[+]                   printf("plus");
[\/]                  printf("div");
[-]                   printf("minus");
[*]                   printf("mult");
[=]                   printf("assign");
%%

int main() {
    extern FILE *yyin, *yyout; 
    yyin = fopen("example.ac", "r"); 
    yylex();
    return 0; 
}
