#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char** argv) {
    char* inFile = "";
    char* outFile = "";
    int ignore = 0;
    char* needle = "";

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-o")) { //case: output
            if (!strcmp(outFile, "")) {
                if (argc - 1 != i) {
                    outFile = argv[i + 1];
                } else {
                    puts("Missing output path");
                    return 1;
                }
            } else {
                puts("Parameter -o provided multiple times");
                return 1;
            }
        } else if (!strcmp(argv[i], "-i")) { //case: ignore capital
            if (ignore == 1) {
                puts("Parameter -i provided multiple times");
                return 1;
            } else {
                ignore = 1;
            }
        } else if (strcmp(argv[i - 1], "-o") && !strcmp(inFile, "")) { //case: input
            inFile = argv[i];
        } else if (strcmp(argv[i - 1], "-o")) { //case: needle
            if (!strcmp(needle, "")) {
                needle = argv[i];
            } else {
                puts("Too many parameters provided");
                return 1;
            }
        }
    }
    if (!strcmp(inFile, "")) {
        puts("Input path not provided");
        return 1;
    }
    if (!strcmp(needle, "")) {
        puts("Needle not provided");
        return 1;
    }

    FILE* file = fopen(inFile, "r");
    FILE* file2 = NULL;
    if (strcmp(outFile, "")) {
        file2 = fopen(outFile, "w");
    }
    /*
    char line[101];
    while (1) {
        if (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';
            if ((ignore && strcasestr(line, needle)) || strstr(line, needle)) {
                if (strcmp(outFile, "")) {
                    fprintf(file2, "%s\n", line);
                } else {
                    puts(line);
                }
            }
        } else {
            break;
        }
    }
    fclose(file);
    */
    char line[101];
    while (1) {
        if (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';
            if ((ignore && strcasestr(line, needle)) || strstr(line, needle)) {
                if (strcmp(outFile, "")) {
                    fprintf(file2, "%s\n", line);
                } 
                else {
                    for (int i = 0; i < (strlen(line)-(strlen(needle)-1)); i++)
                    {
                        char* temp = (char*)malloc(strlen(needle)*sizeof(char));
                        for (int a = 0; a < 3; a++)
                        {
                            temp[a] = line[i+a];
                        }
                        if (!strcmp(temp, needle))
                        {
                            printf("\x1b[41;1m");
                            printf("%s", temp);
                            printf("\x1b[0m");
                            i += strlen(needle)-1;
                        }
                        else{
                            if (i == (strlen(line)-(strlen(needle)-1)-1))
                            {
                                printf("%s", temp);
                            }
                            else{
                                printf("%c", temp[0]);
                            }
                        }
                    }
                    printf("\n");
                }
            }
        } else {
            break;
        }
    }
    fclose(file);
}