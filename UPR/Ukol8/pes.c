#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* selectSubstring(int start, int end, char* string){
    char *startS = &string[start];
    char *endS = &string[end];

    char *substr = (char *)calloc(1, endS - startS + 1);
    memcpy(substr, startS, end - start);
    return substr;
}

int main()
{
    char *c = "the string";
    for (int i = 0; i < (strlen(c)-2); i++)
    {
        char pes[3];
        for (int a = 0; a < 3; a++)
        {
            pes[a] = c[i+a];
        }
        printf("%s\n", pes);
    }
    
    return 0;
}