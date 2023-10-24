/************************************************************************
*	File name : Tutorial.h
*	Project name : APEX
*	Author	    Primary author : Wonju cho
*	        			Secondary author : Junseok Yang
*	        			Others : Haewon Shon, Jookyung Lee
*
*	        			header for Tutorial.cpp
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"
#include "CustomBaseObject.h"
#include "Player.h"

const int T_platformCount = 2;

class TutorialLevel : public State
{
	friend class Game;
protected:
	TutorialLevel() : State() {};
	~TutorialLevel() override {};

	void Initialize() override;

	void Update(float dt) override;

	void Close() override;

private:
	void GeneratePlatform(float posX, float posY, float sizeX, float sizeY, int platformNumber);
	void Print();
	void AttackEffect(Player& player, float dt);
	void SelectText(Object *textObject, const char *textContents, const char *id, SDL_Color color);
	void Create_UI();
    void CreateCommonUI();
    void CreateScoreUI();
	void CheckSetTrap();
	void CheckTrapCollision();
    void CheckRespawn();
    void TrapCooldownAnimation(float dt);

	float tutorial_p1 = 0, tutorial_p2 = 0;
	int	  w_moveCheck = 0, a_moveCheck = 0, s_moveCheck = 0, d_moveCheck = 0,
		  right_moveCheck = 0, left_moveCheck= 0 , up_moveCheck = 0, down_moveCheck = 0,
		  p1_attackCheck = 0, p2_attackCheck = 0,
		  p1_trapCheck = 0, p2_trapCheck = 0,
		  pauseCheck = 0;

	Object  key_h, numpad2,	key_j, numpad3;
    Object p1_movekey, p2_movekey;
    Object move_text, attack_text, trap_text, next_text;
    Object shoes_explain, strong_explain, superarmor_explain;
    Object shoes, strong, superarmor;
	
	Player player1, player2;

    /* Common UI */
    Object p1, p2;
    Object p1_trapImage, p2_trapImage;
    Object p1_trapcooldown_ui, p2_trapcooldown_ui;
    Object p1_respawnText, p2_respawnText;
    Object p1_score_1, p1_score_2, p2_score_1, p2_score_2;
    Object tutorialSound, tutorialBeeb, trap;
    Object hitsound;

    float playTime = 0.f;
	CustomBaseObject platform[T_platformCount];
};