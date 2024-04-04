#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int ShAnOr(int input, int shift, int and, int or){
    return (input >> shift) & and | or;
}

int main(){
    char input[10];
    printf("Zadej Unicode: U+");
    scanf("%s", input);
    int inputDec = (int)strtol(input, NULL, 16);

    if (!(inputDec >= 0 && inputDec <= 0x1FFFFF)){
        printf("Nevalidní vstup\n");
        return 1;
    }
    
    //utf-8
    if (inputDec <= 0x007F){
        printf("UTF-8\t0x%02X\n", inputDec);
    }
    else if(inputDec <= 0x07FF){
        printf("UTF-8\t0x%02X 0x%02X\n", ShAnOr(inputDec, 6, 31, 192), ShAnOr(inputDec, 0, 63, 128));
    }
    else if(inputDec <= 0xFFFF){
        printf("UTF-8\t0x%02X 0x%02X 0x%02X\n", ShAnOr(inputDec, 12, 15, 224), ShAnOr(inputDec, 6, 63, 128), ShAnOr(inputDec, 0, 63, 128));
    }
    else if(inputDec <= 0x1FFFFF){
        printf("UTF-8\t0x%02X 0x%02X 0x%02X 0x%02X\n", ShAnOr(inputDec, 18, 7, 240), ShAnOr(inputDec, 12, 63, 128), ShAnOr(inputDec, 6, 63, 128), ShAnOr(inputDec, 0, 63, 128));
    }
    else{
        printf("UTF-8 převod selhal\n");
    }
    
    //utf-16
    if (inputDec <= 0x00FFFF){
        printf("UTF-16\t0x%04X\n", inputDec);
    }
    else if (inputDec <= 0x1FFFFF){
        printf("UTF-16\t0x%04X 0x%04X\n", ShAnOr(inputDec, 10, 0x3FF, 0xD800), ShAnOr(inputDec, 0, 0x3FF, 0xDC00));
    }
    else{
        printf("UTF-16 převod selhal\n");
    }
    
    //utf-32
    printf("UTF-32\t0x%08X\n", inputDec);

    return 0;
}