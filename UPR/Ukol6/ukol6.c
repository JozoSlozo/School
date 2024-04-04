#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void GetStats(const char *string, int *lowerCase, int *upperCase, int *spaces) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (islower(string[i])) {
            (*lowerCase)++;
        } else if (isupper(string[i])) {
            (*upperCase)++;
        } else if (isspace(string[i])) {
            (*spaces)++;
        }
    }
}

void NormalizeString(char *string) {
    char temp[50];
    int tempI = 0;
    int state = 2; // 0 - first upper, 1 - all upper, x - all lower
    int firstWord = 0; // 0 - is first word, 1 - isn't

    for (int i = 0; string[i] != '\0'; i++) {
        if (isalpha(string[i])) {
            if (i == 0 || string[i - 1] == ' ') {//if first character of word
                if (firstWord != 0) {
                    temp[tempI] = ' ';//puts space before the word, ingores first word
                    tempI++;
                }
                
                for (int a = i; isalpha(string[a]); a++) {//checks the word for upper or lower characters
                    if (isupper(string[a])) {
                        state = 0;
                        break;
                    } else {
                        state = 1;
                    }
                }
                firstWord = 1;
            }
            if (state == 0) {
                temp[tempI] = toupper(string[i]);
                state = 2;
            } else if (state == 1) {
                temp[tempI] = toupper(string[i]);
            } else {
                temp[tempI] = tolower(string[i]);
            }
            if (tempI == 0 || temp[tempI] != temp[tempI - 1]) {//if characters are repeating it skips them
                tempI++;
            }
        }
    }
    temp[tempI] = '\0';
    strcpy(string, temp);
}

int main() {
    char numN[50];
    fgets(numN, sizeof(numN), stdin);

    for (int n = 0; n < atoi(numN); n++) {
        char line[51];
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';
        
        int oldLowerCase = 0;
        int oldUpperCase = 0;
        int oldSpaces = 0;

        int newLowerCase = 0;
        int newUpperCase = 0;
        int newSpaces = 0;

        GetStats(line, &oldLowerCase, &oldUpperCase, &oldSpaces);
        NormalizeString(line);
        GetStats(line, &newLowerCase, &newUpperCase, &newSpaces);

        puts(line);
        printf("lowercase: %d -> %d\nuppercase: %d -> %d\nspaces: %d -> %d\n", oldLowerCase, newLowerCase, oldUpperCase, newUpperCase, oldSpaces, newSpaces);
        if (atoi(numN) - 1 != n) {
            printf("\n");
        }
    }
    return 0;
}