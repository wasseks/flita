#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void printgraph(char *file_source, FILE *input, FILE *output, char **matrix, int mode) {
    input = fopen(file_source, "r");
    output = fopen("matrix.gv", "w");
    char c = ' ';
    int i = 0, j = 0; // add
    int edges = 0;
    while(!feof(input)) {
        if (c != ' ' && c != '\n') {
            matrix[i][j] = c;
            j++;
        } else if (c == '\n') {
            i++;
            j = 0;
        }
        c = fgetc(input);
    }

    fprintf(output, "graph G {\n" );
    for(int a = 0; a < j; a++)
        fprintf(output, "%d\n", a+1);
    for(int a = 0; a < j; a++)
        for(int b = 0; b < j; b++)
            if(matrix[a][b] != '0' && matrix[b][a] != '0') {
                fprintf(output, "\t%d -- %d [label=\"%c\"];\n", a + 1, b + 1, matrix[a][b]);   
                matrix[a][b] = '0';
                edges++;
            }
    
    fprintf(output, "}");

    fclose(input);
    fclose(output);
    if (mode == 1)
        system("dot matrix.gv -Tpng -o firstgraph.png");
    else 
        system("dot matrix.gv -Tpng -o secondgraph.png");
}

int main(int argc, char **argv) {
    FILE *input, *output;
    if (argc != 3)
        return 0;
    char first_matrix[MAX][MAX], second_matrix[MAX][MAX];
    char *tmp = first_matrix;
    printgraph(argv[1], input, output, &tmp, 1);
    printgraph(argv[2], input, output, &second_matrix, 2);
    return 0;
}