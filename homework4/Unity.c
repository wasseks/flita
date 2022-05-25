#include <stdio.h>
#include <stdlib.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX 25

void initialization(int matrix[][MAX]);
void copy(int final_matrix[][MAX], int ini_matrix[][MAX]);
void get_matrix(char *file_source, FILE *input, int matrix[][MAX], int *vertices);
void print_graph(char **argv, int matrix[][MAX], int *vertices, int mode);

int main(int argc, char **argv) {
    if (argc < 3)
        return 0;
    int first_matrix[MAX][MAX], second_matrix[MAX][MAX], unity_matrix[MAX][MAX];
    int first_vc = 0, second_vc = 0, final_vc = 0;
    initialization(first_matrix);
    initialization(second_matrix); 
    initialization(unity_matrix); 
    print_graph(argv, first_matrix, &first_vc, 1);
    print_graph(argv, second_matrix, &second_vc, 2);
    final_vc = MIN(first_vc, second_vc);
    for (int a = 0; a < MAX; a++)
        for (int b = 0; b < MAX; b++) 
            if ((first_matrix[a][b] == second_matrix[a][b]) != 0)
                unity_matrix[a][b] = first_matrix[a][b];
    print_graph(argv, second_matrix, &final_vc, 3);
    return 0;
}

void get_matrix(char *file_source, FILE *input, int matrix[][MAX], int *vertices) {
    input = fopen(file_source, "r");
    char c = ' ';
    int i = 0, j = 0;
    int edges = 0;
    while(!feof(input)) {
        if (c != ' ' && c != '\n') {
            matrix[i][j] = c - '0';
            j++;
        } else if (c == '\n') {
            i++;
            j = 0;
        }
        c = fgetc(input);
    }
    (*vertices) = j;
    fclose(input);
}

void print_graph(char **argv, int matrix[][MAX], int *vertices, int mode) {
    FILE *input, *output;
    int a, b; 
    int edges = 0;
    int ini_matrix[MAX][MAX];
    if (matrix[0][0] == -1) {
        get_matrix(argv[mode], input, ini_matrix, vertices);
        copy(matrix, ini_matrix);
    } else 
        copy(ini_matrix, matrix);

    output = fopen("matrix.gv", "w");
    fprintf(output, "graph G {\n" );
    for(a = 0; a < (*vertices); a++)
        fprintf(output, "%d\n", a+1);
    for(a = 0; a < (*vertices); a++)
        for(b = 0; b < (*vertices); b++)
            if((ini_matrix[a][b] != 0) && (ini_matrix[b][a] != 0)) {
                fprintf(output, "\t%d -- %d [label=\"%d\"];\n", a + 1, b + 1, ini_matrix[a][b]);   
                ini_matrix[a][b] = 0;
                edges++;
            }
    fprintf(output, "}");
    
    fclose(output);
    if (mode == 1)
        system("dot matrix.gv -Tpng -o firstgraph.png");
    else if (mode == 2)
        system("dot matrix.gv -Tpng -o secondgraph.png");
    else 
        system("dot matrix.gv -Tpng -o finalgraph.png");
}

void initialization(int matrix[][MAX]) {
    register int i, j;
    for(i = 0; i < MAX; i++)
        for(j = 0; j < MAX; j++)
            matrix[i][j] = 0;
    matrix[0][0] = -1;
}

void copy(int final_matrix[][MAX], int ini_matrix[][MAX]) {
    register int i, j;
    for(i = 0; i < MAX; i++)
        for(j = 0; j < MAX; j++)
            final_matrix[i][j] = ini_matrix[i][j];
}