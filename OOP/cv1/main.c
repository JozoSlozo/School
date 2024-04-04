#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n = 10;
char* polen;
int delka = 0;

int printfor(int x){
    for (int i = 0; i < x; i++)
    {
        printf("%d", x);
    }
}

int printwhile(int x){
    int i = 0;
    while (i < x)
    {
        printf("%d", x);
        i++;
    }   
}

int printdowhile(int x){
    int i = 0;
    do
    {
        printf("%d", x);
        i++;
    } while (i < x);
}

int getNumLen(int x){
    int i = 0;
    while (x != 0)
    {
        x = x / 10;
        i++;
    }
    return i;
}  

int assignn(){
    for (int i = 0; i < n; i++)
    {
        delka += i*getNumLen(i);
    }
    polen = (char*)malloc(sizeof(char) * delka);

    int o = 0;

    for (int i = 0; i < n; i++)
    {
        for (int l = 0; l < i; l++)
        {
            polen[o] = i+'0';
            o++;
        }
    }
}

int nastavnulaprvni(){
    char *temp = (char*)malloc(sizeof(char) * delka);
    strcpy(temp, polen);
    temp[0] = '0';
    for (int i = 1; i < delka; i++)
    {
        if(polen[i-1] != polen[i]){
            temp[i] = '0';
        }
    }
    strcpy(polen, temp);
    free(temp);
}
int nastavnulaposledni(){
    int temp = 0;
    for (int i = 0; i < delka; i++)
    {
        if (polen[i] != polen[i+1])
        {
            polen[i] = '0';
        }
    }
    return temp;
}
int main(){
    assignn();
    nastavnulaposledni();
    puts(polen);
    free(polen);
}