#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *input, *output;
    input = fopen("input.txt" , "r");
    output = fopen("matrix.gv", "w");
    int i = 0, j = 0;
    char Matrix[100][100], c;   

    while(!feof(input)) {
        fscanf(input, "%c", &c);
        if (c != ' ' && c != '\n') {
            Matrix[i][j] = c;
            j++;
            printf("%d\n", j);
        } else if (c == '\n') {
            i++;
            j = 0;
        }
    }
    printf("%d\n", j);
    printf("%d", i);

    fprintf(output, "graph G {\n" );
    for(int a = 0; a <= i; a++)
        for(int b = 0; b <= i; b++)
            if(Matrix[a][b] != '0' && Matrix[b][a] != '0') {
                fprintf(output, "\t%d -- %d [label=\"%c\"];\n", a + 1, b + 1, Matrix[a][b]);   
                Matrix[a][b] = '0';
            }
    fprintf(output, "}");
    
    fclose(input);
    fclose(output);
    system("dot matrix.gv -Tpng -o graph.png");
    system("graph.png");
    return 0;
}