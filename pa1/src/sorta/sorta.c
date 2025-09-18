#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//make selection sort class
void swap(char *arr[],int i,int j){
    char *t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

int main(int argc, char *argv[]){
if (argc <= 1) {
    return EXIT_FAILURE;
}
int num = argc - 1;



char **string = argv + 1;
for (int i = 0;i < num - 1;i++){
    for(int j = 0;j < num - i -1;j++){
        if(strcmp(string[j],string[j+1]) > 0) {
            //char *t = string[j];
            //string[j] = string[j + 1];
            //string[j + 1] = t;
            swap(string,j,j+1);
        }
    }
}

//Print All out
for (int i = 0; i < num; ++i) {
        printf("%s\n", string[i]);

}




return EXIT_SUCCESS;
}

