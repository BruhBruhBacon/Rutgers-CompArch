#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define initSize 100

struct Stack {
    char *info;
    int head;
    int capacity;
};

void initStack(struct Stack *stack,int cap);

void printAll(struct Stack *stack);
char matchBracket(char close);
char pop(struct Stack *stack);
int checkEmpty(struct Stack *stack);
void push(struct Stack *stack, char c);
char peek(struct Stack *stack);

int main(int argc,char *argv[]){
    if(argc <= 1){
        return EXIT_FAILURE;
    }
    char *brackets = argv[1];
    
    struct Stack stackyy;
    initStack(&stackyy,initSize);

    //char *brackets = {"(foo)"};

    /*for (int i = 0; i < strlen(brackets); ++i) {
        char c = brackets[i];
        printf("%c", brackets[i]);}printf("\n");
    initStack(&stackyy,6);   */

    for (int i = 0; i < strlen(brackets); i++) {
        if(brackets[i] == '{' || brackets[i] == '['||brackets[i] == '(' ){
            //printf("%c",brackets[i]);
            push(&stackyy, brackets[i]); 
        }
        else if(brackets[i] == '}' || brackets[i] == ']'||brackets[i] == ')'){
            if(checkEmpty(&stackyy) || (peek(&stackyy) != matchBracket(brackets[i]))){
                //printf("FINAL");
                //printf("%c",brackets[i]);
                printf("%d: %c\n",i,brackets[i]);
                printAll(&stackyy);
                return EXIT_FAILURE;
            }
            else{
                pop(&stackyy);
                //printf("%c",brackets[i]);
                //pop(&stackyy);
                //printf("%c",brackets[i]);
                //pop(&stackyy);
                //printf("%c",brackets[i]);
                //printf("%c",brackets[i]);
            }

        }
        
    }
    if(!checkEmpty(&stackyy)){
        printf("open: ");
        while(!checkEmpty(&stackyy)){
            char popped = pop(&stackyy);
            char opp = matchBracket(popped);
            putchar(opp);
        }
        return EXIT_FAILURE;
    }
    printAll(&stackyy);
    return EXIT_SUCCESS;


return 0;
}

char matchBracket(char b){
    if(b == '}'){
        return '{';
    }
    if(b == ']'){
        return '[';
    }
    if(b == ')'){
        return '(';
    }

    if(b == '{'){
        return '}';
    }

    if(b == '['){
        return ']';
    }

    if(b == '('){
        return ')';
    }
    return '\0';
}

void initStack(struct Stack* st, int cap){
    st->info = (char *)malloc(cap * sizeof(char));
    if (st->info == NULL) {
        printf("Error: Memory allocation for stack failed\n");
        exit(EXIT_FAILURE);
    }
        st->head = -1;
        st->capacity = cap;
}

void push(struct Stack* st,char limiter){
    //Check to see if stack is full even though it should never be
    //Not sure if works properly
    if(st->head == st->capacity - 1) {
        st->capacity *= 2;
        st->info = (char *)malloc(st->capacity * sizeof(char));
    }
    st->head++;
    st->info[st->head] = limiter;
}

char pop(struct Stack* st){
    
    if (checkEmpty(st)){
        return '\0';
    }
    char poppy = st->info[st->head];
    st->head--;
    return poppy;
    //printf("pop class");
    //printf("%c\n",popped);
}

int checkEmpty(struct Stack* st){
    return st->head == -1;
}

void printAll(struct Stack* st){
    free(st->info);
}

char peek(struct Stack* st){
    //Return null if empty
    if(checkEmpty(st)){
        return '0';
    }
    return st->info[st->head];
    
}


