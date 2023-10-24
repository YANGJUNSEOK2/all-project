/******************************************************************************/
/*!
\file   Game.h
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\par    GAM150 demo
\par	v0
\date   2018/03/11

Game will only handle the changes of the game states (Level switching)
ie. Main Menu, Levels, Pause, etc.
No game play logic should be added here.
*/
/******************************************************************************/

#pragma once

// Level headers
#include "MainMenu.h"
#include "PauseState.h"
#include "Credit.h"
#include "CharacterSelect1p.h"
#include "CharacterSelect2p.h"
#include "Tutorial.h"
#include "Domination.h"
#include "CoinCollect.h"
#include "Ending.h"
#include "ModeSelect.h"
#include "digipenLogo.h"
#include "TeamLogo.h"

//This is the list of levels the game has. When adding a new level(state)
//add it to this list. They are tagged with LV_ to enable better autocomplete 
typedef enum
{
    LV_DigipenLogo = 0,
    LV_TeamLogo,
    LV_MainMenu,
    LV_CharacterSelect1p,
    LV_CharacterSelect2p,
    LV_Tutorial,
    LV_ModeSelect,
    LV_Domination,
    LV_CoinCollect,
    LV_Ending,
    LV_Credit,
	LV_Pause,
	//etc.

	LV_NUM_LEVELS
}Level_ID;

class StateManager;

class Game
{
	friend class Application;

	StateManager *m_stateManager = nullptr;

public:

	Game();
	~Game();

	void	RegisterState(State* state);
	void	SetFirstState(State* state);
	State*	GetCurrentState();

	void	Quit();
	void	Change(unsigned stateId);

	bool	Initialize();
	void	Update(float dt);
	void	Close();

	void	RegisterPauseState(State *state);
	void	Pause();
	void	Resume();
	void	Restart();
	bool	IsQuit();

    /* Data for Game */
    int p1Character = 1;
    int p2Character = 1;
    int p1WinCount = 0;
    int p2WinCount = 0;
    int roundCount = 1;

private:

	// All the level(state) declarations are here
    DigipenLogo digipenLogo;
    TeamLogo teamLogo;
	MainMenu	mainMenu;
    CharacterSelect1p characterSelect1p;
    CharacterSelect2p characterSelect2p;
    TutorialLevel tutorialLevel;
    ModeSelectLevel modeSelectLevel;
    DominationLevel dominationLevel;
    CoinCollectLevel coinCollectLevel;
    Ending ending;
	PauseState	pauseLevel;
    Credit credit;

public:
	
	static constexpr int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;
	int	m_width = 0, m_height = 0;

	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

};