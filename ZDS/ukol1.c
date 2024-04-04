#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int prevedDoSoustavy(int cislo, int soustava, char *prevedene){

    char prevedeneCislo[9] = "\0\0\0\0\0\0\0\0\0";
    char cislaSoustavy[16] = "0123456789ABCDEF";

    for (int i = 0; cislo != 0; i++)
    {
        prevedeneCislo[i] = cislaSoustavy[cislo%soustava];
        cislo  /= soustava;
    }

    int tempI = 0;
    for (int i = strlen(prevedeneCislo)-1; i >= 0; i--)
    {
        prevedene[tempI] = prevedeneCislo[i];
        tempI++;
    }

    return 0;
}

int main(){
    int cislo, soustava;
    char prevedene[8];

    printf("Zadejte číslo 0-255: ");
    scanf("%d", &cislo);
    if (cislo > 255 || cislo < 0)
    {
        printf("Neplatné číslo\n");
        return 1;
    }

    printf("Zadejte soustavu 2-16: ");
    scanf("%d", &soustava);
    if (soustava > 16 || soustava < 2)
    {
        printf("Neplatné soustava\n");
        return 1;
    }

    prevedDoSoustavy(cislo, soustava, prevedene);
    printf("Převedené číslo: %s\n", prevedene);
    return 0;
}