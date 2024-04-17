#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
using namespace std;
#include "lcd_lib.h"
#include "font8x8.h"

uint16_t l_color_red = 0xF800;
uint16_t l_color_green = 0x07E0;
uint16_t l_color_blue = 0x001F;
uint16_t l_color_white = 0xFFFF;

struct point
{
    int x;
    int y;
};


class Text
{
private:
    string textValue;
    int startx;
    int starty;
    vector<point> textPoints;
public:
    Text(string text, int startX, int startY);
    void draw();
    void destroy();
    void changeColor(uint16_t color);
};

Text::Text(string t, int sx, int sy)
{
    this->textValue = t;
    this->startx = sx;
    this->starty = sy;
}
void Text::draw(){
    int len = this->textValue.length();
    for (int a = 0; a < len; a++)
    {
        int character = this->textValue[a];
        for ( int x = 0; x < 8; x++ ) // square offset in x and y axis
        {
            for (int y = 0; y < 8; y++)
            {
                int temp = static_cast<int>(font8x8[character][x]) & 0x01 << y;
                if (temp != 0)
                {
                    point temp;
                    temp.x = (y+10*a)+this->startx;
                    temp.y = x+this->starty;
                    lcd_put_pixel(temp.x, temp.y, l_color_white);
                    textPoints.push_back(temp);
                }
            }

        }
    }
}
void Text::destroy(){
    this->changeColor(0);
}
void Text::changeColor(uint16_t c){
    for (point p : this->textPoints)
    {
        lcd_put_pixel(p.x, p.y, c);
    }
}

class Circle
{
private:
    int centerx;
    int centery;
    int radius;
    int width;
    vector<point> circlePoints;
public:
    Circle(int centerX, int centerY, int radius, int width);
    void draw();
    void destroy();
    void changeColor(uint16_t color);
};

Circle::Circle(int cx, int cy, int r, int w)
{
    this->centerx = cx;
    this->centery = cy;
    this->radius = r;
    this->width = w;
}
void Circle::draw(){
	for ( int32_t x = this->centerx-this->radius-10; x < this->centerx+this->radius+10; x++ )
	{
		for ( int32_t y = this->centery-this->radius-10; y < this->centery+this->radius+10; y++ )
		{
			int CircleFunc = ((x - this->centerx) * (x - this->centerx)) + ((y - this->centery)*(y - this->centery)) ;
			if(CircleFunc >= this->radius*this->radius-this->width && CircleFunc <= this->radius*this->radius+this->width){
				lcd_put_pixel(x, y, l_color_red);
                point temp;
                temp.x = x;
                temp.y = y;
                circlePoints.push_back(temp);
			}
		}
	}
}
void Circle::destroy(){
	this->changeColor(0);
}
void Circle::changeColor(uint16_t c){
	for (point p : circlePoints)
    {
        lcd_put_pixel(p.x, p.y, c);
    }
}

int main()
{
    lcd_init();// LCD initialization
    
    Text *t = new Text("pes", 100, 100);
    t->draw();
    t->changeColor(l_color_green);
    
    Circle *c = new Circle(100, 100, 50, 50);
    c->draw();
    c->destroy();
    cv::imshow( LCD_NAME, g_canvas );   // refresh content of "LCD"
    cv::waitKey( 0 );                   // wait for key 
}


