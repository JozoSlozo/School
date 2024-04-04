#include <stdio.h>
#include <stdlib.h>

int GetHistogram(int** histogramReturn, int* histogramLen, int* mReturn){
    int n, m, range;
    range = 8;

    scanf("%d", &n);
    scanf("%d", &m);

    int *histogram;
    histogram = (int*) malloc((range+2) * sizeof(int));
    for (int i = 0; i < (range+2); i++){histogram[i] = 0;}
    
    for (int i = 0; i < n; i++)
    {
        int num;
        scanf("%d", &num);

        if(num >= m && num <= m+range){
            histogram[num - m] = histogram[num - m] + 1;
        }
        else{
            histogram[range+1] = histogram[range+1] + 1;
        }
    }
    *mReturn = m;
    *histogramLen = range+2;
    *histogramReturn = histogram;

    return 0;
}

int GetNumLen(int num){
    int num_len = 0;
    do
    {
        num_len++;
        num = num / 10;
    } while (num != 0);
    return num_len;
}
int PrintHastag(int times){
    
    for (int a = 0; a < times; a++)
    {
        if (a == 0){printf(" ");}
        printf("#");
    }
    printf("\n");
    return 0;
}
int HastagOrSpace(int a, int b){
    if (a >= b)
    {
        printf("#");
    }
    else{
        printf(" ");
    }
    return 0;
}

int main(){
    char ch;
    scanf("%c", &ch);
    
    int* histogram;
    int m, len;

    switch (ch)
    {
    case 'h':
        GetHistogram(&histogram, &len, &m);
        int lastNumLen = GetNumLen(m+len-2);
        for (int i = 0; i < len-1; i++)
        {
            if(GetNumLen(m+i) < lastNumLen){
                printf(" ");
            }
            printf("%d", m+i);
            PrintHastag(histogram[i]);
        }
        if(histogram[len-1] != 0){
            printf("invalid:");
            PrintHastag(histogram[len-1]);
        }
        free(histogram);
        break;
    case 'v':
        GetHistogram(&histogram, &len, &m);
        for (int line = 0; line < len; line++)
        {
            int empty = 1;
            for (int i = 0; i < len; i++)
            {
                if(histogram[i] > len-line-1){
                    empty = 0;
                }
            }
            
            if(empty == 0){
                HastagOrSpace(histogram[len-1], len-line);
                for (int column = 0; column < len-1; column++)
                {
                    HastagOrSpace(histogram[column], len-line);
                }
                printf("\n");
            }
        }
        printf("i");
        for (int lastLine = 0; lastLine < len-1; lastLine++)
        {
            printf("%d", m+lastLine);
        }
        printf("\n");
        free(histogram);
        break;
    default:
        printf("Neplatny mod vykresleni\n");
        return 1;
    }

    return 0;
}