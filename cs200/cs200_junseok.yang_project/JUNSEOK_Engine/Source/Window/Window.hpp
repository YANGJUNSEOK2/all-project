/************************************************************************
*	File name : Window.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<glew.h>
#include<string>
#include <iostream>
#include "../FPS/FPS.h"
#include "../Error/Error.h"

struct Color;

enum WindowFlags { HIDDEN = 0X1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();

    void Init();

    void Change_Window_Type();

    int Get_Screen_Height() const;

    int Get_Screen_Width() const;

    void Change_Window_Color(const Color& ChangeColor);

    void Set_Window_Vsync();

    void Show_FPS_Inwindow(float FPS);

    void Swapbufferwindow() const;

    void Set_Screen_Width_Height(int Width, int Height);

    void ResizeWindow(int windowWidth, int windowHeight);

    void Show_WindowIcon();

    SDL_Window* Get_Window() { return gWindow; }

    void show_focus(int flags);

    bool show_demo_window = true;
    bool show_another_window = false;

private:
    SDL_Window* gWindow = nullptr;
    SDL_GLContext p_glContext;


    SDL_Surface *image;

    FPS m_Fps;
    SDL_Rect j;

    int SCREEN_WIDTH = 1024;
    int SCREEN_HEIGHT = 640;
    bool Is_window_fullscreen = false;
    bool Is_window_vsync = false;
};