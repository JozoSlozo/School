#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int ZigZag(char *string, int start){
    char temp[50];
    int left = 0;
    int right = strlen(string)-1;
    int tempi = 0;
    if (start > right)
    {
        strcpy(string, "");
        return 0;
    }
    
    for (int i = 0; i < strlen(string); i++)
    {
        if (i % 2 == 0 || i == 0)
        {
            temp[i] = string[right];
            right--;
        }
        else{
            temp[i] = string[left];
            left++;
        }
        tempi = i;
        
    }
    temp[tempi+1] = '\0';
    char temp2[50];
    for (int i = 0; i < strlen(temp)-start; i++)
    {
        temp2[i] = temp[i+start];
    }
    temp2[strlen(temp)-start] = '\0';
    strcpy(string, temp2);
    return 0;
}
int main(){
    char zigzag[50];
    fgets(zigzag, sizeof(zigzag), stdin);
    int startNum = atoi(zigzag+7);

    char line[50];
    line[0] = 'a';
    while (1==1)
    {
        fgets(line, sizeof(line), stdin);
        if(line[0] == '\n'){
            break;    
        }
        line[strcspn(line, "\n")] = '\0';
        ZigZag(line, startNum);
        puts(line);
    }
    
    return 0;
}