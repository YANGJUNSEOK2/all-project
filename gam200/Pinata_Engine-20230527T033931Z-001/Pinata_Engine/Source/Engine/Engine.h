#pragma once
#include <vector>
#include "../Error/Error.h"
#include "../Window/Window.hpp"
#include "../Shader/Shader.hpp"
#include "../Camera/Camera.hpp"
#include "../IO_Manager/MouseInput.h"
#include "../IO_Manager/KeyboardInput.h"
#include "..//Sprite/SpriteBatch/SpriteBatch.hpp"
#include "../Window/Window.hpp"
#include "../FPS/DeltaTime.hpp"

class GameState;
class SpriteBatch;
class Window;

class Engine
{
public:
	Engine() : isRunning(true) { }

	//Starts up SDL and creates window
	void Init(Engine* game);

	void ChangeState(GameState* state, Engine* game);

	void PushState(GameState* state, Engine* game);

	void PopState(Engine* game);

	//Frees media and shuts down SDL

	void HandleEvents(Engine* game);

	void Update();

    void TimeUpdate(float delta_time_seconds);

	void Draw();

	void Close(Engine* game);

	bool Running() { return isRunning; }

	void Quit() { isRunning = false; }

	void Update_Shaders();
	

    Shader &getShader() { return m_ColorProgram; }
	void setShader(Shader shader) { m_ColorProgram = shader; }

    Camera &getCamera() { return m_Camera; }
	void setCamera(Camera camera) { m_Camera = camera; }

    MouseInput& getMouse() { return m_mouse; }
    KeyboardInput& get_keyboard_input() { return m_Input; }

	std::vector<SpriteBatch*> get_objects() { return Objects; }

	/*WINDOW SETTINGS!!!!*/

	GameWindow& Window() { return gameWindow; }
	void setWindow(GameWindow window) { gameWindow = window; }
	
	//void Change_Window_Type();

	//int Get_Screen_Width()const;
	//int Get_Screen_Height()const;

	//void Swapbufferwindow() const
	//{
	//	SDL_GL_SwapWindow(gWindow);
	//}

    //void Set_Window_Vsync();

	void InitShader();

    //void Show_FPS_Inwindow(float FPS);

	/*WINDOW SETTINGS!!!!*/

	/* Object settings*/
	void Adding_Objects_To_ObjectsFactory(SpriteBatch* obj);
	void Cleanup_Objects();
	
private:

	bool isRunning;
	std::vector<GameState*> states;

    GameWindow gameWindow;

	//The window we'll be rendering to
	//SDL_Window* gWindow = nullptr;

	////The window renderer
	//SDL_Renderer* gRenderer = nullptr;

	////Current displayed texture
	//SDL_Texture* gTexture = nullptr;
    Camera m_Camera;

    KeyboardInput m_Input;

    MouseInput m_mouse;

    //SDL_GLContext p_glContext;

    Shader m_ColorProgram;
	
	std::vector<SpriteBatch*> Objects;

    DeltaTime timer{};

    float seconds = 0;
    int   frameCount = 0;

    std::wstring fpsText{};
    float        fpsElapsedTime = 0;
    int          fpsFrames = 0;
};