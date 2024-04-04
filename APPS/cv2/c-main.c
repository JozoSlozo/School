//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>


int data_x = 0b10101010; //global
int count = 0; //global
int result_num = 0; //global
int iterations = 6; //global
char text[] = "rxtXzXX"; //global
char from = 'X'; //global
char replace_to = 'e'; //global
void fibb();
void count_ones();
void replace_char();


int main()
{
    count_ones();
    printf("Ones %d\n",count);
    count  = 0;
    data_x = 0b111110101010;
    count_ones();
    printf("Ones %d\n",count);

    
    
    fibb();        
    printf("7th fibbonaci: %d\n", result_num);

    replace_char();        
    printf(
      "string: %s\n", 
      text
    );

}

