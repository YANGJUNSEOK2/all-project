/************************************************************************
*	File name : Engine.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include <vector>
#include "../Error/Error.h"
#include "../Shader/Shader.hpp"
#include "../Camera/Camera.hpp"
#include "../IO_Manager/MouseInput.h"
#include "../Window/Window.hpp"
#include "../Mesh/MeshDraw.hpp"
#include "../IO_Manager/Input.hpp"
#include "../Camera/Transtorm.h"

class GameState;

class Engine
{
public:
    Engine() : isRunning(true), rotate(0.0f), zoom(1.0f), position{ 0.0f,0.0f }, cameraMatrix{1.0}, is_click(false), m_glContext(nullptr){ }
	//Starts up SDL and creates window
	void Init(Engine* game);

    //void InitCamera();

	void ChangeState(GameState* state, Engine* game);

	void PushState(GameState* state, Engine* game);

	void PopState(Engine* game);

	//Frees media and shuts down SDL

	void HandleEvents(Engine* game);

	void Update();

	void Draw();

	void Close(Engine* game);

	bool Running() { return isRunning; }

	void Quit() { isRunning = false; }

	void Update_Shaders();

    Shader &getShader() { return m_ColorProgram; }
	//void setShader(Shader shader) { m_ColorProgram = shader; }

    Camera &getCamera() { return m_Camera; }
	void setCamera(Camera camera) { m_Camera = camera; }

    MouseInput& getMouse() { return m_mouse; }
    Inputs& getInputs() { return m_Inputs; }

    MeshDraw &getMesh() { return m_Mesh; }
    //void setMesh(Mesh mesh) { m_Mesh = mesh; }
	/*WINDOW SETTINGS!!!!*/

    GameWindow& getWindow() { return gameWindow; }
	void setWindow(GameWindow window) { gameWindow = window; }

    Matrix3<float> getCameraMatrix() { return m_Camera.GetCameraOrtho(); }
    void setCameraMatrix(Matrix3<float> p_CameraMatrix) { m_Camera.GetCameraOrtho() = p_CameraMatrix; }

    Transform& getTransform() { return m_Transform; }
    void setTransform(Transform p_Transform) { m_Transform = p_Transform; }

    bool &getIsClick() { return is_click; }
    void setIsClick(bool p_IsClick) { is_click = p_IsClick; }

	void InitShader();

private:
    GameWindow gameWindow;

	bool isRunning;
	std::vector<GameState*> states;

	//The window we'll be rendering to
	SDL_Window* gWindow = nullptr;

    Camera m_Camera;

    MouseInput m_mouse;

    Inputs m_Inputs;

    SDL_GLContext m_glContext;

    Shader m_ColorProgram;

    MeshDraw m_Mesh;

    Transform m_Transform;


    float rotate = 0.0f;
    float zoom = 1.0f;
    Vector2<float> position = { 0.0f,0.0f };

    Matrix3<float> cameraMatrix;

    bool is_click = false;
protected:

};