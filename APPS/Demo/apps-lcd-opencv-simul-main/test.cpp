#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#include "font8x8.h"

int main()
{
    uint16_t l_color_red = 0xF800;
    uint16_t l_color_green = 0x07E0;
    uint16_t l_color_blue = 0x001F;
    uint16_t l_color_white = 0xFFFF;

    // simple animation display four color square using LCD_put_pixel function
    int l_limit = 200;
    for ( int ofs = 0; ofs < 8; ofs++ ) // square offset in x and y axis
    {
        for (int i = 0; i < 8; i++)
        {
            int temp = static_cast<int>(font8x8[100][ofs]) & 0x01 << i;
            if (temp != 0)
            {
                /* code */
            }
            
        }
        
    }
}