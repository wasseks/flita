#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#define MAX 10000

void unity(int **final_matrix, int **first_matrix, int **second_matrix);
void generation(int **matrix);
void freematrix(int **matrix);

int main() {
    clock_t t;
    int **first_matrix, **second_matrix, **unity_matrix;
    int i;
    first_matrix = (int**)malloc(MAX * sizeof(int*));
    for (i = 0; i < MAX; ++i)
        first_matrix[i] = (int*)malloc(MAX * sizeof(int));
    second_matrix = (int**)malloc(MAX * sizeof(int*));
    for (i = 0; i < MAX; ++i)
        second_matrix[i] = (int*)malloc(MAX * sizeof(int));
    unity_matrix = (int**)malloc(MAX * sizeof(int*));
    for (i = 0; i < MAX; ++i)
        unity_matrix[i] = (int*)malloc(MAX * sizeof(int));
    generation(first_matrix);
    generation(second_matrix);  
    t = clock();
    unity(unity_matrix, first_matrix, second_matrix);
    t = clock() - t;
    freematrix(first_matrix), freematrix(second_matrix), freematrix(unity_matrix);
    printf("It took me %d clicks (%f seconds).\n", (int)t, ((double)t)/CLOCKS_PER_SEC);
    return 0;
}

void unity(int **final_matrix, int **first_matrix, int **second_matrix) {
    register int a, b;
    for (a = 0; a < MAX; ++a)
        for (b = a; b < MAX; ++b) 
            if (first_matrix[a][b] == second_matrix[a][b]) 
                final_matrix[a][b] = final_matrix[b][a] = first_matrix[a][b];
            else 
                final_matrix[a][b] = final_matrix[b][a] = 0;
}

void generation(int **matrix) {
    register int i, j;
    for(i = 0; i < MAX; ++i)
        for(j = i; j < MAX; ++j)
            if (i == j) 
                matrix[i][j] = matrix[j][i] = 0;
            else
                matrix[i][j] = matrix[j][i] = rand() % 2;
}

void freematrix(int **matrix) {
    register int i;
    for (i = 0; i < MAX; ++i)  
        free(matrix[i]);   
    free(matrix);
}