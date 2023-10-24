/************************************************************************
*	File name : MainMenu.cpp
*	Project name : APEX
*	Author      Primary author : Wonju Cho
*			         Secondary author : Jookyung Lee
*			         Others : Haewon Shon, Junseok Yang
*
*			         Functions for Main Menu
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"

enum MainMenuImage
{
    START_MENU,
    CREDIT_MENU,
    EXIT_MENU
};

class MainMenu : public State
{
	friend class Game;

protected:

	MainMenu() : State() {};
	~MainMenu() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;

private:
    void MenuSelect();
    void MenuImageChange();
	void CharacterUI();

    MainMenuImage menuImageStatus = MainMenuImage::START_MENU;
    Object mainMenu;
	Object haewon, wonju, jookyung, junseok;
    Object backgroundMusic, move, select;
};

