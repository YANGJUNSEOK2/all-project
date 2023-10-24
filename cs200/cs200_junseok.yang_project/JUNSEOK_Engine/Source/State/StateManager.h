/************************************************************************
*	File name : StateManager.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include <iostream>
#include "SDL.h"
#include "../Main/Engine.h"
#include "../FPS/FPS.h"
#include "../IO_Manager/MouseInput.h"
#include "../IO_Manager/Input.hpp"
#include "../Camera/Camera.hpp"
#include "../Camera/CameraSet.h"
#include "../Camera/CameraView.h"
#include "../Camera/Transtorm.h"
#include "../Shader/Shader.hpp"
#include "../Sprite/SpriteBatch/SpriteBatch.hpp"
#include "../Texture/Texture.hpp"
#include "../Mesh/MeshDraw.hpp"

class GameState
{
public:
	virtual void Init(Engine* game) = 0;
	virtual void Close(Engine* game) = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	void HandleEvents(Engine* game);
	void FrameDelay(FPS* fpslimiter,float &m_fps);

	virtual void Update(Engine* game) = 0;
	virtual void Draw(Engine* game) = 0;

	static void ChangeState(Engine* game, GameState* state) {
		game->ChangeState(state, game);
	}
private:
	

protected:
	GameState() = default;
};