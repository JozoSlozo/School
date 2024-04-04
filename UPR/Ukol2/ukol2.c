#include <stdio.h>
int obrazec_0(int sirka, int vyska){
    for (int v = 0; v < vyska; v++){
        for(int s = 0; s < sirka; s++){
            printf("x");
        }
        printf("\n");
    }
    return 0;
}
int obrazec_1(int sirka, int vyska){
    for (int v = 0; v < vyska; v++){
        for(int s = 0; s < sirka; s++){
            if(v == 0 || s == 0 || s == sirka - 1 || v == vyska - 1){
                printf("x");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
int obrazec_2(int sirka, int vyska){
    for (int v = 0; v < vyska; v++){
        for(int s = 0; s < sirka; s++){
            if(v == 0 || s == 0 || s == sirka - 1 || v == vyska - 1){
                printf("x");
            }
            else{
                printf("%d", ((s-1) + (v-1) * (sirka-2)) % 10);
            }
        }
        printf("\n");
    }
    return 0;
}
int obrazec_3(int delka){
    for (int v = 0; v < delka; v++){
        for (int s = 0; s < delka; s++){
            if(s == v){
                printf("x");
                break;
            }
            else{
                printf(" ");
            }
        }  
        printf("\n"); 
    }
    return 0;
}
int obrazec_6(int sirka, int vyska){
   for (int v = 0; v < vyska; v++){
        for(int s = 0; s < sirka; s++){
            if(v == 0){
                printf("x"); 
            }
            else if (s == sirka / 2)
            {
                printf("x");
                break; 
            }
            
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0; 
}
int obrazec_9(int sirka, int vyska){
    for (int v = 0; v < vyska; v++){
        for(int s = 0; s < sirka; s++){
            if(v == 0 || s == 0 || s == sirka - 1 || v == vyska - 1){
                printf("x");
            }
            else{
                printf("%d", ((v - 1) + (s - 1) * (vyska - 2)) % 10);
            }
        }
        printf("\n");
    }
    return 0;
}
int main(){
    int obrazec, a, b = 0;
    scanf("%d%d%d", &obrazec, &a, &b);
    switch (obrazec)
    {
    case 0:
        obrazec_0(a, b);
        break;
    case 1:
        obrazec_1(a, b);
        break;
    case 2:
        obrazec_2(a, b);
        break;
    case 3:
        obrazec_3(a);
        break;
    case 6:
        obrazec_6(a, b);
        break;
    case 9:
        obrazec_9(a, b);
        break;
    default:
        printf("Neznamy obrazec\n");
        break;
    }
}