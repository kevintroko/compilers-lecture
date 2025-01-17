/*
-- Author --
Kevin Oswaldo Cabrera Navarro - A01227157

-- Code at --
https://github.com/kevintroko/compilers-lecture/tree/master/labs/02

--- References ---
C program for implementation of stack (lines 15 to 50) from 
https://www.geeksforgeeks.org/stack-data-structure-introduction-program/ 
I hope is not a problem since the logic for the lexical analysis was 100% done by me :) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    int *array;
};
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack *createStack(unsigned capacity) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}
// Stack is full when top is equal to the last index
int isFull(struct Stack *stack) {
    return stack->top == stack->capacity - 1;
}
// Stack is empty when top is equal to -1
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}
// Function to add an item to stack.  It increases top by 1
void push(struct Stack *stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    //printf("%c pushed to stack\n", item);
}
// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack *stack) {
    if (isEmpty(stack))
        return 34404;
    return stack->array[stack->top--];
}

char *readFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int line,character, 
        dqline, dqcharacter,
        sqline, sqcharacter,
        comment = 0;
    struct Stack *stack = createStack(100);
    struct Stack *brackets = createStack(100);
    struct Stack *singleQuote = createStack(100);
    struct Stack *doubleQuote = createStack(100);
    // if 0 no error generated
    int errorCheck = 0;
    int c;
    if (file == NULL)
        return NULL;
    code = malloc(1000);
    while ((c = fgetc(file)) != EOF) {
        // printf("%d, %c\n",c,c);
        character++;
        switch(c){
            case 10: // break line
                character = 0;
                line ++;
                break;
            case 34: // "
                if (isEmpty(doubleQuote)) {
                    push(doubleQuote, c);
                    dqline = line;
                    dqcharacter = character;
                } else {
                   if (pop(doubleQuote)==34404){
                    printf("There is a missing error \" in this line: %d space: %d\n", line, character);
                    errorCheck=1;
                   }
                }
                break;
            case 39: // '
                if (isEmpty(singleQuote)) {
                    push(singleQuote, c);
                    sqline = line;
                    sqcharacter = character;
                } else {
                    if (pop(singleQuote) == 34404) {
                        printf("There is a missing error \' in this line: %d space: %d\n", line, character);
                        errorCheck=1;
                    }
                }
                break;
            case 40: // (
                push(stack, c);
                break;
            case 41: // )
                if (pop(stack) == 34404){
                    printf("There is a missing error ( in this line: %d space: %d\n", line, character);
                    errorCheck=1;
                }
                break;
            case 47: // comments /
                comment++;
                if(comment==2){
                    while((c = fgetc(file))!=10) {
                        code[n++] = (char)c;
                    }
                    comment=0;
                }
                break;
            case 123: // {
                push(brackets, c);
                break;
            case 125: // }
                if (pop(brackets) == 34404){
                    printf("There is a missing error { in this line: %d space: %d\n", line, character);
                    errorCheck=1;
                }
                break;
        }

        code[n++] = (char)c;
    }

    if(isEmpty(stack)!=1){
        printf("There is an extra ( in your code\n");
        errorCheck = 1;
    }

    if (isEmpty(brackets)!= 1){
        printf("There is an extra ( in your code\n");
        errorCheck = 1;        
    }

    if(isEmpty(doubleQuote)!=1){
        printf("There is a missing error \" in this line: %d space: %d\n", dqline, dqcharacter);
        errorCheck = 1;
    }

    if (isEmpty(singleQuote)!=1)
    {
        printf("There is a missing error \' in this line: %d space: %d\n", dqline, dqcharacter);
        errorCheck = 1;
    }

    if(errorCheck==0) {
        printf("There are no errors\n");
    }
    code[n] = '\0';
    return code;
}

int main(int argc, char *argv[]) {
    readFile(argv[1]);
    return 0;
}