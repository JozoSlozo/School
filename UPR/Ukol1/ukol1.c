#include <stdio.h>
int main() { 
    int penize = 9420;
    int bankovky[] = {5000, 2000, 1000, 500, 200, 100};
    for(int i = 0; i < 6; i++){
        printf("Bankovka %d: %dx\n",bankovky[i] , penize / bankovky[i]);
        penize = penize % bankovky[i];
    }
    return 0;
}