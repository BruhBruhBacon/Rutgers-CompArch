#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc <= 1) {
        return EXIT_FAILURE;
    } 
char *p = argv[1];
char letter;
    while((letter = *p++) != '\0'){
        if((letter >= 'A' && letter <= 'Z' )|| (letter >= 'a' && letter <= 'z')){
            if((letter > 'M' && letter <='Z') ||(letter > 'm' && letter <= 'z')){
                putchar(letter - 13);
            }
            else{
                putchar(letter + 13);
            }
        }
        else{
            putchar(letter);
        }
        
    }
return EXIT_SUCCESS; 
}