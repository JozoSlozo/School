#include <stdio.h>
#include <stdlib.h>
int ArrayAlloc(char** array, int len){
    *array = (char*) malloc(len * sizeof(char));
    return 0;
}
int InitArray(char* array, int len){
    for (int i = 0; i < len; i++){
        array[i] = '.';
    }
    return 0;   
}
typedef struct Zelva{
    int posRows;
    int posCols;
    int dir[2];
    int active;
}Zelva;
int ActivateZelva(Zelva *zelvy){
    for (int i = 0; i < 3; i++){
        if (zelvy[i].active == 0){
            zelvy[i].active = 1;
            return 0;
        }
    }
    return 0;
}
int SpinRight(Zelva *zelvy){
    for (int i = 0; i < 3; i++){
        if (zelvy[i].active == 1){
            int temp[2] = {zelvy[i].dir[0], zelvy[i].dir[1]};
            zelvy[i].dir[0] = temp[1];
            zelvy[i].dir[1] = -temp[0];
        }
    }
    return 0;
}
int SpinLeft(Zelva *zelvy){
    for (int i = 0; i < 3; i++){
        if (zelvy[i].active == 1){ 
            int temp[2] = {zelvy[i].dir[0], zelvy[i].dir[1]};
            zelvy[i].dir[0] = -temp[1];
            zelvy[i].dir[1] = temp[0];
        }
    }
    return 0;
}
int MakeMove(Zelva *zelvy, int rows, int cols){
    for (int i = 0; i < 3; i++){
        if (zelvy[i].active == 1){
            zelvy[i].posCols = ((zelvy[i].posCols + zelvy[i].dir[1]) % cols + cols) % cols;
            zelvy[i].posRows = ((zelvy[i].posRows + zelvy[i].dir[0]) % rows + rows) % rows;
        }
    }
    return 0;
}
int ZelvaDraw(Zelva *zelvy, char* canvas, int cols){
    for (int i = 0; i < 3; i++){
        if (zelvy[i].active == 1){
            int pos = zelvy[i].posCols + zelvy[i].posRows * cols;
            if (canvas[pos] == 'o'){
                canvas[pos] = '.';
            }
            else{
                canvas[pos] = 'o';
            }
        }
    }
    return 0;
}
int main() 
{
    int rows = 0;
    int cols = 0;

    scanf("%d", &rows);
    scanf("%d", &cols);

    char* canvas;
    ArrayAlloc(&canvas, rows*cols);
    InitArray(canvas, rows*cols);

    Zelva zelva = {0,0,{0,1},0};
    Zelva zelvy[3] = {zelva, zelva, zelva};
    ActivateZelva(zelvy);
    
    char input = ' ';

    while (input != 'x')
    {
        scanf("%c", &input);

        switch (input)
        {
        case 'r':
            SpinRight(zelvy);
            break;
        case 'l':
            SpinLeft(zelvy);
            break;
        case 'm':
            MakeMove(zelvy, rows, cols);
            break;
        case 'o':
            ZelvaDraw(zelvy, canvas, cols);
            break;
        case 'f':
            ActivateZelva(zelvy);
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", canvas[i * cols + j]);
        }
        printf("\n");
    }
    
    free(canvas);
    return 0;
}