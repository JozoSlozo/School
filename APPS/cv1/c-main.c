//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <stdint.h>


void set_x_y();
void set_char_arr();
void change_char();
void set_long_arr();

int32_t g_int_x;
int64_t g_int_y;
char g_char_arr[ 5 ] = "....";
char g_char_str[] = "Mam rad C++";
long g_long_arr[ 2 ];

int main()
{
    set_x_y();
    printf("%d \n", g_int_x);
    printf("%ld \n", g_int_y);
    set_char_arr();
    puts(g_char_arr);
    change_char();
    puts(g_char_str);
    set_long_arr();
    printf("[%ld, %ld]\n", g_long_arr[0], g_long_arr[1]);
}