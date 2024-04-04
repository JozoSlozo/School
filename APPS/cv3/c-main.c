//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

int strcat(char * str, char to_find, int * count);

int str2int(char * a, int*b);

int main()
{
    char string[] = "Ahoj svete! EeEe";
    char to_find = 'e';
    int count;
    int first = strcat(string, to_find, &count);
    printf("count: %d, first: %d\n", count, first);
    
    char buff[255]="55";
    int num = 0;
    str2int(buff, &num);
    puts(buff);
}
