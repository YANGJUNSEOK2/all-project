/******************************************************************************/
/*!
\file   PauseState.h
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\par    GAM150 demo
\par	v0
\date   2018/03/28

Conaining examples how to use engine
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"

class PauseState : public State
{
	friend class Game;

public:
    enum PauseImage {BACK_TO_THE_GAME, TOGGLE_FULLSCREEN, EXIT};
    PauseImage pauseImageStatus;
protected:

	PauseState() : State() {};
	~PauseState() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;

private:
    void PauseSelect();
    void PauseImageChange();

	// Objects
	Object	pauseImage, beep;
};

