/************************************************************************
*	File name : Window.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "Window.hpp"
#include "../Vertex/Vertex.hpp"
#include <cstdarg>
#include "../Camera/Camera.hpp"

GameWindow::GameWindow()
{
}

GameWindow::~GameWindow()
{
}

void GameWindow::Init()
{
    //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Set texture filtering to linear
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //Create window
    gWindow = SDL_CreateWindow("Team Pinata", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE/*| SDL_WINDOW_BORDERLESS*/);

    Show_WindowIcon();

    p_glContext = SDL_GL_CreateContext(gWindow);
    if (p_glContext == nullptr)
    {
        FindError("SDL_GLContext could not be created!");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        FindError("Could not init glew!");
    }

    std::printf("***  OpenGL version %s  ***", glGetString(GL_VERSION));
    //Change_Window_Color({ 255, 105, 180, 255 });
    //glClearColor(1.0,0.674,0.658,1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Vsync OFF
    SDL_GL_SetSwapInterval(0);

    show_demo_window = true;
    show_another_window = false;

}

void GameWindow::Change_Window_Type()
{
    Is_window_fullscreen = !Is_window_fullscreen;
    if (Is_window_fullscreen)
    {
        int i = SDL_GetWindowDisplayIndex(gWindow);
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_SetWindowFullscreen(gWindow, 0);
    }
    else
    {
        int i = SDL_GetWindowDisplayIndex(gWindow);
        SDL_GetDisplayBounds(i, &j);
        int NEW_SCREEN_WIDTH = j.w;
        int NEW_SCREEN_HEIGHT = j.h;
        glViewport(0, 0, NEW_SCREEN_WIDTH, NEW_SCREEN_HEIGHT);
        SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
}

int GameWindow::Get_Screen_Height() const
{
    return SCREEN_HEIGHT;
}


int GameWindow::Get_Screen_Width() const
{
    return SCREEN_WIDTH;
}

void GameWindow::Change_Window_Color(const Color& ChangeColor)
{
    GLclampf R = (1 / 255.0f)*(ChangeColor.r);
    GLclampf G = (1 / 255.0f)*(ChangeColor.g);
    GLclampf B = (1 / 255.0f)*(ChangeColor.b);
    GLclampf A = (1 / 255.0f)*(ChangeColor.a);
    glClearColor(R,G,B,A);
}

void GameWindow::Set_Window_Vsync()
{
    if (!Is_window_vsync)
    {
        std::cout << "vsync on \n";
        SDL_GL_SetSwapInterval(1);
        Is_window_vsync = true;
    }
    else
    {
        std::cout << "vsync off \n";
        SDL_GL_SetSwapInterval(0);
        Is_window_vsync = false;
    }
}


void GameWindow::Show_FPS_Inwindow(float FPS)
{
    std::string title = "Team Pinata (fps:";
    title += std::to_string(static_cast<int>(FPS));
    title += ")";
    SDL_SetWindowTitle(gWindow, title.c_str());
}

void GameWindow::Swapbufferwindow() const
{
    SDL_GL_SwapWindow(gWindow);
}

void GameWindow::Set_Screen_Width_Height(int Width, int Height)
{
    SCREEN_WIDTH = Width;
    SCREEN_HEIGHT = Height;
}

void GameWindow::ResizeWindow(int windowWidth, int windowHeight)
{
    SDL_GetWindowSize(this->gWindow, &windowWidth, &windowHeight);
}

void GameWindow::Show_WindowIcon()
{
    image = IMG_Load("Texture/icon.png");

    SDL_SetWindowIcon(gWindow, image);

    SDL_FreeSurface(image);
}


void GameWindow::show_focus(int flags) { 

    printf("\nFLAGS ENABLED: ( %d )\n", flags);
    printf("=======================\n");

    if (flags & SDL_WINDOW_MOUSE_FOCUS)        printf("SDL_WINDOW_MOUSE_FOCUS CHECK!!\n");
}