#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Stock
{
    char* name;
    int index;
    float valStart;
    float valEnd;
    int sold;
} Stock;

char* changeInt(int num) {
    char *str = (char*)malloc((int)((ceil(log10(num))+1) * sizeof(char)));
    sprintf(str, "%d", num);

    char *temp = (char *)malloc(((strlen(str) + (strlen(str) / 3)) + 1) * sizeof(char));
    int o = 0;

    for (int i = 0; i < ((int)strlen(str)); i++) {
        if ((int)(strlen(str) - i) % 3 == 0 && i != 0) {
            temp[o++] = '_';
        }
        temp[o++] = str[i];
    }
    temp[o] = '\0';
    free(str);
    return temp;
}

int main(int argc, char** argv) {
    if (argc < 3)
    {
        printf("Wrong parameters\n");
        return 1;
    }

    char *mainStock = argv[1];
    int numLines = atoi(argv[2]);

    Stock topStock = {NULL, 0, 0, 0, 0};
    Stock *stockArr = (Stock*) malloc(sizeof(Stock)*numLines);

    for (int i = 0; i < numLines; i++)
    {
        char line[101];
        char *splitLine[5];

        fgets(line, sizeof(line), stdin);

        char* token = strtok(line, ",");
        for (int a = 0; a < 5; a++)//splits line by commas into splitLine
        {
            splitLine[a] = token;
            token = strtok(NULL, ",");
        }

        stockArr[i].index = atoi(splitLine[0]);
        stockArr[i].name = (char*)malloc(sizeof(char)*strlen(splitLine[1])+1);
        strcpy(stockArr[i].name, splitLine[1]);
        stockArr[i].valStart = atof(splitLine[2]);
        stockArr[i].valEnd = atof(splitLine[3]);
        stockArr[i].sold = atoi(splitLine[4]);
        
        if (strcmp(mainStock, stockArr[i].name) == 0 && stockArr[i].sold > topStock.sold)//finds best selling stock
        {
            topStock = stockArr[i];
        }
    }
    printf("<html>\n<body>\n");
    if (topStock.sold == 0)
    {
        printf("<div>\nTicker %s was not found\n</div>\n", mainStock);
    }
    else{
        printf("<div>\n<h1>%s: highest volume</h1>\n<div>Day: %d</div>\n<div>Start price: %.2f</div>\n<div>End price: %.2f</div>\n<div>Volume: %s</div>\n</div>\n", topStock.name, topStock.index, topStock.valStart, topStock.valEnd, changeInt(topStock.sold));
    }
    printf("<table>\n<thead>\n<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n</thead>\n<tbody>\n");
    for (int i = numLines-1; i >= 0; i--)
    {
        if (strcmp(stockArr[i].name, mainStock) == 0)
        {
            char *temp = changeInt(stockArr[i].sold);
            printf("<tr>\n\t<td><b>%d</b></td>\n\t<td><b>%s</b></td>\n\t<td><b>%.2f</b></td>\n\t<td><b>%.2f</b></td>\n\t<td><b>%.2f</b></td>\n\t<td><b>%s</b></td>\n</tr>\n",
            stockArr[i].index, stockArr[i].name, stockArr[i].valStart, stockArr[i].valEnd, stockArr[i].valEnd - stockArr[i].valStart, temp);
            free(temp);
        }else{
            char *temp = changeInt(stockArr[i].sold);
            printf("<tr>\n\t<td>%d</td>\n\t<td>%s</td>\n\t<td>%.2f</td>\n\t<td>%.2f</td>\n\t<td>%.2f</td>\n\t<td>%s</td>\n</tr>\n",
            stockArr[i].index, stockArr[i].name, stockArr[i].valStart, stockArr[i].valEnd, stockArr[i].valEnd - stockArr[i].valStart, temp);
            free(temp);
        }
        free(stockArr[i].name);
    }
    printf("</tbody>\n</table>\n</body>\n</html>\n");
    free(stockArr);
    return 0;
}