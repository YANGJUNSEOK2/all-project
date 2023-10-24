#include "Window.hpp"

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
    gWindow = SDL_CreateWindow("Team Pinata", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL /*| SDL_WINDOW_BORDERLESS*/);

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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Vsync OFF
    SDL_GL_SetSwapInterval(0);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSdlGL3_Init(gWindow);
    ImGui::StyleColorsDark();
    show_demo_window = true;
    show_another_window = false;

}

void GameWindow::Change_Window_Type()
{
    if (Is_window_fullscreen == true)
    {
        SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
        Is_window_fullscreen = false;
    }
    else
    {
        SDL_SetWindowFullscreen(gWindow, 0);
        SDL_SetWindowSize(gWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
        Is_window_fullscreen = true;
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

void GameWindow::Show_WindowIcon()
{
    image = IMG_Load("Texture/icon/icon.png");

    SDL_SetWindowIcon(gWindow, image);

    SDL_FreeSurface(image);
}
