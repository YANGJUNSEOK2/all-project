/*
 * junseok yang
 * Lab1 - LineRasterizer
 * CS200
 * Fall 2018
 */

#include <CS200/Image.hpp>
#include <cstdlib>

using namespace CS200;

const Color BLACK{ 0x000000FF };
const Color WHITE{ 0xFFFFFFFF };
const Color JAGUAR_BLACK{ 0x1F0322FF };
const Color DISCO_PURPLE{ 0x8a1c7cFF };
const Color CABARET_RED{ 0xda4167FF };
const Color BATTLESHIP_GRAY{ 0x899d78FF };

const int WIDTH = 256;
const int HEIGHT = 256;
const Color BEAUTY_BUSH_PINK{ 0xf0bcd4FF };
Image gImage{ WIDTH, HEIGHT, BEAUTY_BUSH_PINK };


void SETPIXEL(int column, int row, Color intensity) { gImage.SetPixel(column, row, intensity); }

void DrawLine(int x0, int y0, int x1, int y1, Color intensity);

int main(void)
{
    DrawLine(10, 50, 246, 206, BLACK);
    gImage.SaveToPNG("test0.png");

    gImage.Clear(BEAUTY_BUSH_PINK);
    DrawLine(246, 206, 10, 50, BLACK);
    gImage.SaveToPNG("test1.png");

    gImage.Clear(BEAUTY_BUSH_PINK);
    DrawLine(50, 10, 206, 246, BLACK);
    gImage.SaveToPNG("test2.png");

    gImage.Clear(BEAUTY_BUSH_PINK);
    DrawLine(206, 246, 50, 10, BLACK);
    gImage.SaveToPNG("test3.png");

    gImage.Clear(BEAUTY_BUSH_PINK);
    DrawLine(50, 246, 206, 10, BLACK);
    gImage.SaveToPNG("test4.png");

    gImage.Clear(BEAUTY_BUSH_PINK);
    DrawLine(206, 10, 50, 246, BLACK);
    gImage.SaveToPNG("test5.png");

    gImage.Clear(BEAUTY_BUSH_PINK);
    DrawLine(10, 206, 246, 50, BLACK);
    gImage.SaveToPNG("test6.png");

    gImage.Clear(BEAUTY_BUSH_PINK);
    DrawLine(246, 50, 10, 206, BLACK);
    gImage.SaveToPNG("test7.png");

    gImage.Clear(BEAUTY_BUSH_PINK);
    DrawLine(10, 128, 246, 128, BLACK);
    gImage.SaveToPNG("test8.png");

    gImage.Clear(BEAUTY_BUSH_PINK);
    DrawLine(128, 10, 128, 248, BLACK);
    gImage.SaveToPNG("test9.png");

    return 0;
}

void DrawLine(int x0, int y0, int x1, int y1, Color intensity)
{
    //todo
    int dx_Size = x1 - x0;
    int dy_Size = y1 - y0; //make the size dx,dy

    int dx_Abs = abs(dx_Size);
    int dy_Abs = abs(dy_Size);//abs size dx,dy

    int p_X = 2 * dy_Abs - dx_Abs;//x start point
    int p_Y = 2 * dx_Abs - dy_Abs;//y start point

    int temp_x0 = x0, temp_x1 = x1, temp_y0 = y0, temp_y1 = y1;//tmp

    if(dy_Abs > dx_Abs)//the slope is greater than 1
    {
        if (dy_Size >= 0)//dy is positive ,dy=0
        {
            temp_x0 = x0;
            temp_y0 = y0;
            temp_y1 = y1;
        }
        else//dy is negative
        {
            temp_x0 = x1;
            temp_y0 = y1;
            temp_y1 = y0;
        }
        SETPIXEL(temp_x0, temp_y0, intensity);

        for (int i = 0; temp_y0 <= temp_y1; i++)
        {
            temp_y0 = temp_y0 + 1;
            if (p_Y <= 0)
            {
                p_Y = p_Y + 2 * dx_Abs;
            }//if p_Y <= 0 start point size up
            else
            {
                if ((dx_Size < 0 && dy_Size < 0) || (dx_Size > 0 && dy_Size > 0))
                {
                    temp_x0 = temp_x0 + 1;
                }//up
                else
                {
                    temp_x0 = temp_x0 - 1;
                }//down
                p_Y = p_Y + 2 * (dx_Abs - dy_Abs);//start point change
            }
            SETPIXEL(temp_x0, temp_y0, intensity);
        }
    }
    else if (dy_Abs <= dx_Abs)//the slope is smaller than 1 , = 1
    {
        if (dx_Size >= 0)//dx is positive, dx = 0
        {
            temp_x0 = x0;
            temp_y0 = y0;
            temp_x1 = x1;
        }
        else//dx is negative
        {
            temp_x0 = x1;
            temp_y0 = y1;
            temp_x1 = x0;
        }
        SETPIXEL(temp_x0, temp_y0, intensity);

        for (int i = 0; temp_x0 < temp_x1; i++)
        {
            temp_x0 = temp_x0 + 1;
            if (p_X < 0)
            {
                p_X = p_X + 2 * dy_Abs;
            }//if p_X < 0 start point size up
            else
            {
                if ((dx_Size < 0 && dy_Size < 0) || (dx_Size > 0 && dy_Size > 0))
                {
                    temp_y0 = temp_y0 + 1;
                }//up
                else
                {
                    temp_y0 = temp_y0 - 1;
                }//down
                p_X = p_X + 2 * (dy_Abs - dx_Abs);//start point change
            }
            SETPIXEL(temp_x0, temp_y0, intensity);
        }
    }
}