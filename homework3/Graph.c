#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main() {
    FILE *input, *output;
    input = fopen("input.txt" , "r");
    output = fopen("matrix.gv", "w");
    int i = 0, j = 0;
    char Matrix[MAX][MAX], c = ' ';   
    int edges = 0;

    while(!feof(input)) {
        if (c != ' ' && c != '\n') {
            Matrix[i][j] = c;
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
            if(Matrix[a][b] != '0' && Matrix[b][a] != '0') {
                fprintf(output, "\t%d -- %d [label=\"%c\"];\n", a + 1, b + 1, Matrix[a][b]);   
                Matrix[a][b] = '0';
                edges++;
            }
    
    if (edges >= ((j - 1) * (j - 2) / 2)) {
    	printf("connected graph\n");
        fprintf(output, "0 [label = \"connected graph\"]\n");
    }
    else {
    	printf("disconnected graph\n");
        fprintf(output, "0 [label = \"disconnected graph\"]\n");
    }
    fprintf(output, "}");

    fclose(input);
    fclose(output);
    system("dot matrix.gv -Tpng -o graph.png");
    return 0;
}