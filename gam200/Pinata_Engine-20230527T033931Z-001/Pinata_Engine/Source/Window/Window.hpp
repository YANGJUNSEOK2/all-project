#pragma once
#include<SDL.h>
#include <SDL_image.h>
#include<glew.h>
#include<string>
#include <iostream>
#include "../Error/Error.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_sdl_gl3.h"

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

    void Set_Window_Vsync();

    void Show_FPS_Inwindow(float FPS);

    void Swapbufferwindow() const;

    void Set_Screen_Width_Height(int Width, int Height);

    SDL_Window* Get_Window() { return gWindow; }

    bool show_demo_window = true;
    bool show_another_window = false;

    void Show_WindowIcon();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
private:
    SDL_Window* gWindow = nullptr;
    SDL_GLContext p_glContext;
    SDL_Surface *image;

    int SCREEN_WIDTH = 1440;
    int SCREEN_HEIGHT = 900;
    bool Is_window_fullscreen = false;
    bool Is_window_vsync = false;
};