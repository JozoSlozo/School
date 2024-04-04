#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char a[10];

    fgets(a, sizeof(a), stdin);

    int n = atoi(a);
    char radky[n][50];
    int staremezery = 0;
    int novemezery = 0;

    for (int i = 0; i < n; i++) {
        fgets(radky[i], sizeof(radky[i]), stdin);
    }

    for (int i = 0; i < n; i++) {
        char normalizovanyradek[50];
        int kontrolovanyindex = 0;
        int index = 0;
        int delka = strlen(radky[i]);


        while (radky[i][kontrolovanyindex] == ' ') {
            kontrolovanyindex = kontrolovanyindex + 1;
            staremezery = staremezery + 1;
        }

        while (kontrolovanyindex < delka) {
            while (radky[i][kontrolovanyindex] != ' ' && radky[i][kontrolovanyindex] != '\0') {
                normalizovanyradek[index] = radky[i][kontrolovanyindex];
                index++;
                kontrolovanyindex++;
            }
            if (radky[i][kontrolovanyindex] == ' ') {
                normalizovanyradek[index] = ' ';
                index++;
                kontrolovanyindex++;
                staremezery++;
                novemezery++;
                while (radky[i][kontrolovanyindex] == ' ') {
                    kontrolovanyindex++;
                    staremezery = staremezery + 1;
                }
            }
        }
        while(radky[i][kontrolovanyindex] == ' '){
            staremezery++;
        }
        kontrolovanyindex = 0;
        index = 0;

        while(kontrolovanyindex < delka){
            int delkaslova = 0;
            int velkepismeno = 0;            
                while(normalizovanyradek[kontrolovanyindex] != ' ' && radky[i][kontrolovanyindex] != '\0'){
                    if(islower(normalizovanyradek[kontrolovanyindex])){
                        velkepismeno = 1;
                    }
                    delkaslova++;
                    kontrolovanyindex++;
                }
                if(velkepismeno == 1){
                    toupper(normalizovanyradek[(kontrolovanyindex - delkaslova)]);
                    for(int k; k < delkaslova; k++){
                        normalizovanyradek[(kontrolovanyindex - (delkaslova + 1) + k)] = tolower(normalizovanyradek[(kontrolovanyindex - (delkaslova + 1) + k)]);
                    }
                    break;
                }else if(velkepismeno == 0){
                    for(int k = 0; k < delkaslova; k++){
                        normalizovanyradek[(kontrolovanyindex - (delkaslova + 1) + k)] = toupper(normalizovanyradek[(kontrolovanyindex - (delkaslova) + k)]);
                    }
                    break;
                }
                
        }


        normalizovanyradek[index] = '\0';
        printf("%s", normalizovanyradek);
        printf("spaces: %i -> %i \n", staremezery, novemezery - 1);
        staremezery = 0;
        novemezery = 0;
    }

    for (int i = 0; i < n; i++) {
        printf("%s", radky[i]);
    }

    return 0;
}