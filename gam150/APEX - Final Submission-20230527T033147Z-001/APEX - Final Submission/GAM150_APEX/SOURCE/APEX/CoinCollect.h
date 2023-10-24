/************************************************************************
*	File name : CoinCollect.h
*	Project name : APEX
*	Author	    Primary author : Jookyung Lee
*			        Secondary author : Haewon Shon
*			        Others : Junseok Yang, Wonju cho
*
*			        header for CoinCollect.cpp
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"
#include "CustomBaseObject.h"
#include "Player.h"

const int maxPlatformCoinCollect = 14;
const int maxSpringCoinCollect = 4;

struct platformInfoCoinCollect
{
    b2Vec2 position = { 0.f, 0.f };
    float width = 0.f;
    float height = 0.f;
};

class CoinCollectLevel : public State
{
	friend class Game;

protected:
	CoinCollectLevel() : State() {};
	~CoinCollectLevel() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function-
	void Update(float dt) override;
	// Derived Close function
	void Close() override;

private:
    /* 
     * Common Functions
    */
    void GeneratePlatform(float posX, float posY, float sizeX, float sizeY, int platformNumber);
    void PrintCount();
    void Restart();
    void CheckRespawn();
    void AttackEffect(Player& player, float dt);
    void ItemEffect(Player& player, float dt);
    void IsPlayerStickToSide();
    void CreateCommonUI();
    void CreateScoreUI();

	/*
	 * Common - Items
    */
    void CheckSetTrap();
    void Item(float dt);
    void MakeNewItem();
    void Item2(float dt);
    void MakeNewItem2();
    bool IsItemOverlapped(b2Vec3 position);
    void CheckTrapCollision();
    void TrapCooldownAnimation(float dt);
    void Spring();
    void GenerateSpring(float posX, float posY, int springNumber);

    /*
     * CoinCollect
    */
	void CoinGenerate(float dt);
	void CoinCheck(float dt);
	void Score_UI();
	void UI_initialize();
	bool EndCheck();

    /* Common Variables */
    Player player1, player2;
    platformInfoCoinCollect* platformInfos;
    int platformCount;
    b2Vec2* springPosition;
    int springCount;
    bool isItemAvaliable = false;
    bool isItemAvaliable2 = false;
    bool isGameEnd = false;
    bool IsCountOn = false;
    float regenDelay = 8.f, regenDelay2 = 7.f;

    CustomBaseObject platform[maxPlatformCoinCollect];
    CustomBaseObject spring[maxSpringCoinCollect];
    CustomBaseObject item, item2;
    CustomBaseObject trap_p1, trap_p2;
    CustomBaseObject* trap;
    Object count;
    float playTime = 0.f;
   
    Object hit_sound, fail_sound, item_sound, background_sound, trap_sound, spring_sound, respawn_sound, coin_sound;
    /* Common UI */
    Object p1, p2;
    Object p1_trapImage, p2_trapImage;
    Object p1_trapcooldown_ui, p2_trapcooldown_ui;
    Object p1_respawnText, p2_respawnText;
    Object p1_score_1, p1_score_2, p2_score_1, p2_score_2;
    Object roundEndText;

    /* CoinCollect Level */
    float coinRegenDelay = 5.f;
	int p1Score = 0, p2Score = 0;
	CustomBaseObject coin;
	Object p1Score_UI, p2Score_UI, p1_scoretext, p2_scoretext;
    bool isCoinAvaliable = false;
};