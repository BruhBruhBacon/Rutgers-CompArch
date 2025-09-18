#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** createSpace(int size){

    int **mat = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        mat[i] = (int*)malloc(size * sizeof(int)); 
    }
    return mat;
}

void deleteSpace(int **mat, int size){
    for (int i = 0; i < size; i++) {
        free(mat[i]);
    }
    free(mat);
}

void multiply_matrices(int **expod, int **mat, int **holder, int dim) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {

        *(*(holder + i) + j) = 0;  // Using pointer arithmetic for accessing temp
        for (int z = 0; z < dim; ++z) {
            *(*(holder + i) + j) += *(*(expod + i) + z) * *(*(mat + z) + j);  // Pointer arithmetic for result and matrix
        }
        
    }
}
}


void print_matrix(int **matrix, int k) {
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            printf("%d", *(*(matrix + i) + j)); 
            if (j != k - 1) {                  // It is suppsoed to check for the last element in the row
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    int dim = 0; 
    if (fscanf(input, "%d", &dim) != 1) {
        //End it
        fclose(input);
        return EXIT_FAILURE;
    }

    int **expod = createSpace(dim);
    int **mat = createSpace(dim);

    int **tempy = createSpace(dim);
    


    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {

            fscanf(input, "%d", &mat[i][j]);
        }
    }

    int exp = 0; 
    if (exp < 0 || fscanf(input, "%d", &exp) != 1 ) {
        deleteSpace(mat, dim);
        deleteSpace(tempy, dim);
        deleteSpace(expod, dim);
        return EXIT_FAILURE;
    }
//can close npw
    fclose(input);

    if (exp == 0) {

        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if(i == j){
                    expod[i][j] = 1;
                }
                else{
                    expod[i][j] = 0;
                }
            }
        }

    }
    else if(exp == 1){
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                expod[i][j] = mat[i][j];
            }
        }
    }

    else {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                expod[i][j] = mat[i][j];

            }
        }
        for (int z = 1; z < exp; z++) {
            multiply_matrices(expod, mat, tempy, dim); 
            for (int i = 0; i < dim; i++) {
                for (int j = 0; j < dim; j++) {

                    expod[i][j] = tempy[i][j];

            }
        }
    }
}

    print_matrix(expod, dim);
    //Free up all the space before ending
    deleteSpace(mat, dim);
    deleteSpace(tempy, dim);
    deleteSpace(expod, dim);

    return EXIT_SUCCESS;
}