#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    double** arr;
    int rows;
    int cols;
} Matrix;

Matrix createSpaceMatrix(int rows, int cols){
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    mat.arr = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) { mat.arr[i] = (double*)malloc(cols * sizeof(double));}
    return mat;
}

void freeMatrix(Matrix mat){
    for (int i = 0; i < mat.rows; i++) {
        free(mat.arr[i]);
    }
    free(mat.arr);
}

Matrix transposeMatrix(Matrix mat){
    Matrix transposed = createSpaceMatrix(mat.cols,mat.rows);
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) { transposed.arr[j][i] = mat.arr[i][j];}
    }
    return transposed;
}

void printMatrix(Matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%.0f", mat.arr[i][j]);
        }
        printf("\n");
    }
}

Matrix multiplyMatrices(Matrix matA, Matrix matB) {
    // ex: matrixA * matrixB order matters so matrixA = mat1
    Matrix multiplied = createSpaceMatrix(matA.rows, matB.cols);

    for (int i = 0; i < matA.rows; i++) {
        for (int j = 0; j < matB.cols; j++) {
            multiplied.arr[i][j] = 0;
            for (int k = 0; k < matA.cols; k++) {multiplied.arr[i][j] += matA.arr[i][k] * matB.arr[k][j];}
        }
    }

    return multiplied;
}

Matrix inverseMatrix(Matrix mat){
    Matrix mirror = createSpaceMatrix(mat.rows,mat.cols);
    //rows and cols should be the same anyway
    for (int i = 0; i < mirror.rows; i++) {
        for (int j = 0; j < mirror.cols; j++) {
            mirror.arr[i][j] = 0;
            if(i == j){
                mirror.arr[i][j] +=1;
            }
        }
    }

    int n = mat.rows;
    for (int i = 0; i < n; i++) {
        // Get pivot value
        double pivot = mat.arr[i][i];
        //For all the values in pivot row divide by pivot in order to make 1(even if already 1)
        for (int j = 0; j < n; j++) {
            mat.arr[i][j] /= pivot;
            mirror.arr[i][j] /= pivot;
        }
        // below pivot = 0
        for (int k = i + 1; k < n; k++) {

        double num1 = mat.arr[k][i];

            for (int j = 0; j < n; j++) {
                mat.arr[k][j] -= num1 * mat.arr[i][j];

                mirror.arr[k][j] -= num1 * mirror.arr[i][j];
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        // above pivot = 0
        for (int k = i - 1; k >= 0; k--) {
        double num2 = mat.arr[k][i];

            for (int j = 0; j < n; j++) {
            
            mat.arr[k][j] -= num2 * mat.arr[i][j];
            mirror.arr[k][j] -= num2 * mirror.arr[i][j];
            }
        }
    }
    return mirror;
}


int main(int argc, char *argv[]){
    if (argc < 3) {
        return EXIT_FAILURE;
    }

    FILE *trainInput = fopen(argv[1], "r");
    if (trainInput == NULL) {
        return EXIT_FAILURE;
    }
    char filetype[10];
    int trainAttributes;
    int trainHouses;

    if (fscanf(trainInput, "%s", filetype) != 1) {
        fclose(trainInput);
        return EXIT_FAILURE;
    }

    if (fscanf(trainInput, "%d", &trainAttributes) != 1) {
        fclose(trainInput);
        return EXIT_FAILURE;
    }

    if (fscanf(trainInput, "%d", &trainHouses) != 1) {
        fclose(trainInput);
        return EXIT_FAILURE;
    }
    //printf("Label: %s\n", filetype);
    //printf("dataAttributes: %d\n", trainAttributes);
    //printf("dataHouses: %d\n", trainHouses);
    
    Matrix train = createSpaceMatrix(trainHouses,trainAttributes + 1);
    Matrix price = createSpaceMatrix(trainHouses,1);

    //make 2 arrayys
    //make houses and attributes training array which is trainHouses x (trainAttributes + 1) first column is all 1
    //make house price array which is a trainHouses x 1 array which = last column of file
    for (int i = 0; i < trainHouses; i++) {
        train.arr[i][0] = 1.0; 
        for (int j = 1; j <= trainAttributes; j++) {
            if (j < trainAttributes + 1) {
                fscanf(trainInput, "%lf", &train.arr[i][j]);
            }
        }
        fscanf(trainInput, "%lf", &price.arr[i][0]);
    }

    //printMatrix(train);

    //print price array
    //printMatrix(price);
    

    fclose(trainInput);

    FILE *dataInput = fopen(argv[2], "r");
    if (dataInput == NULL) {
        return EXIT_FAILURE;
    }
    //create data matrix
    
    char filechoice[10];
    int dataAttributes;
    int dataHouses;

    if (fscanf(dataInput, "%s", filechoice) != 1) {
        fclose(dataInput);
        return EXIT_FAILURE;
    }

    if (fscanf(dataInput, "%d", &dataAttributes) != 1) {
        fclose(dataInput);
        return EXIT_FAILURE;
    }

    if (fscanf(dataInput, "%d", &dataHouses) != 1) {
        fclose(dataInput);
        return EXIT_FAILURE;
    }

    // Printing file beggginging vals
    //printf("Label: %s\n", filechoice);
    //printf("dataAttributes: %d\n", dataAttributes);
    //printf("dataHouses: %d\n", dataHouses);
    
    Matrix data = createSpaceMatrix(dataHouses,dataAttributes + 1);

    for (int i = 0; i < dataHouses; i++) {
        for (int j = 0; j < dataAttributes + 1; j++) {
            if (j == 0) {
                data.arr[i][j] = 1.0;  
            } else {
                fscanf(dataInput, "%lf", &data.arr[i][j]);
            }
        }
    }
    //printMatrix(data); 

    fclose(dataInput);

    Matrix weight = multiplyMatrices(multiplyMatrices(inverseMatrix(multiplyMatrices(transposeMatrix(train),train)),transposeMatrix(train)),price);
    //printMatrix(weight);

    Matrix final = multiplyMatrices(data,weight);
    printMatrix(final);


    freeMatrix(weight);
    freeMatrix(final);
    freeMatrix(train);
    freeMatrix(price);
    freeMatrix(data);
    

return EXIT_SUCCESS; 
}