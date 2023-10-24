/************************************************************************
*	File name : Level2.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include "StateManager.h"
#include "../Texture/ScreenShot.hpp"
#include "../Font/Font.hpp"

class Level2 : public GameState
{
public:
    Level2() = default;
	void Init(Engine* game) override;
	void Close(Engine* game) override;

	void Pause() override;
	void Resume() override;

	void Update(Engine* game) override;
	void Draw(Engine* game) override;

	// Implement Singleton Pattern
	static Level2* Instance()
	{
		return &m_Level2;
	}
	~Level2() = default;



private:

    Image image;
    ScreenShot screenShot;

    SpriteBatch T;

    SpriteBatch m_sprite;
    Font m_Font;

    SpriteBatch black;

    SpriteBatch AniFace;
    SpriteBatch AniDora;

	static Level2 m_Level2;

    CameraView view;

	FPS m_fpslimiter;
	float m_MaxFPS = 0;
	float m_FPS = 0;

    int currentTextVersion{};
};
