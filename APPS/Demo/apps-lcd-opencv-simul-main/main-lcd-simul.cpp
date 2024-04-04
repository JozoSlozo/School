// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 09/2019
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         OpenCV simulator of LCD
//
// **************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#include "lcd_lib.h"
#include "font8x8.h"

//#include "graph_struct.hpp"
//#include "graph_class.hpp"

int main()
{
    lcd_init();                     // LCD initialization

    uint16_t l_color_red = 0xF800;
    uint16_t l_color_green = 0x07E0;
    uint16_t l_color_blue = 0x001F;
    uint16_t l_color_white = 0xFFFF;

    // simple animation display four color square using LCD_put_pixel function
    int l_limit = 200;
    for (int b = 0; b < count; b++)
    {
        /* code */
    }
    
    for (int a = 1; a < 31; a++)
    {
        for ( int ofs = 0; ofs < 8; ofs++ ) // square offset in x and y axis
        {
            for (int i = 0; i < 8; i++)
            {
                int temp = static_cast<int>(font8x8[32+a][ofs]) & 0x01 << i;
                if (temp != 0)
                {
                    lcd_put_pixel(i+10*a, ofs+20, l_color_white);
                }

            }

        }
    }
    
    

    cv::imshow( LCD_NAME, g_canvas );   // refresh content of "LCD"
    cv::waitKey( 0 );                   // wait for key 
}


