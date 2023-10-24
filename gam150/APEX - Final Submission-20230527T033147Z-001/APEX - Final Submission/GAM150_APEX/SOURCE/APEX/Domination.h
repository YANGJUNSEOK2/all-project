/************************************************************************
*	File name : Domination.h
*	Project name : APEX
*	Author	    Primary author : Jookyung Lee
*			        Secondary author : Haewon Shon
*			        Others : Junseok Yang, Wonju cho
*
*			        header for Domination.cpp
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"
#include "CustomBaseObject.h"
#include "Player.h"

const int maxPlatformDomination = 9;
const int maxSpringDomination = 6;

struct platformInfoDomination
{
    b2Vec2 position = { 0.f, 0.f };
    float width = 0.f;
    float height = 0.f;
};

class DominationLevel : public State
{
    friend class Game;
protected:

    DominationLevel() : State() {};
    ~DominationLevel() override {};

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
    * Domination
    */
    void GenerateDominatingPlatform(float posX, float posY, float sizeX, float sizeY);
    bool EndCheck();
    void DominatingPlatformAnimation();
    void CheckDominating(float dt);
    void UI_domination_gauge();
    void CreateDominationUI();
    void DominationUIUpdate(int dominator);

    /* Common variables */
    Player player1, player2;
    platformInfoDomination* platformInfos;
    int platformCount;
    b2Vec2* springPosition;
    int springCount;
    bool isItemAvaliable = false;
    bool isItemAvaliable2 = false;
    bool isGameEnd = false;
    bool IsCountOn = false;
    float regenDelay = 8.f, regenDelay2 = 7.f;

    Object hit_sound, fail_sound, item_sound, background_sound, trap_sound, spring_sound,respawn_sound;

    CustomBaseObject platform[maxPlatformDomination];
    CustomBaseObject spring[maxSpringDomination];
    CustomBaseObject item, item2;
    CustomBaseObject trap_p1, trap_p2;
    CustomBaseObject* trap;
    Object count;
    float playTime = 0.f;
    Object sound;

    /* Common UI */
    Object p1, p2;
    Object p1_trapImage, p2_trapImage;
    Object p1_trapcooldown_ui, p2_trapcooldown_ui;
    Object p1_respawnText, p2_respawnText;
    Object p1_score_1, p1_score_2, p2_score_1, p2_score_2;
    Object roundEndText;

    /* Domination Level */
    int prevPlatform = 3;
    int prevDominator = 0;
    platformInfoDomination dominationPlatformInfo;
    CustomBaseObject dominatingPlatform;
    float dominating_p1 = 0, dominating_p2 = 0;
    Object p1gauge, p2gauge;
    Object dominateBox_p1, dominateBox_p2, dominate_status_box;
    float whoHasPlatform = 0.f;
    char* gauge[101] = {
        "0","1" ,"2" ,"3" ,"4" ,"5" ,"6" ,"7" ,"8" ,"9" ,"10",
        "11","12","13","14","15","16","17","18","19","20",
        "21","22","23","24","25","26","27","28","29","30",
        "31","32","33","34","35","36","37","38","39","40",
        "41","42","43","44","45","46","47","48","49","50",
        "51","52","53","54","55","56","57","58","59","60",
        "61","62","63","64","65","66","67","68","69","70",
        "71","72","73","74","75","76","77","78","79","80",
        "81","82","83","84","85","86","87","88","89","90",
        "91","92","93","94","95","96","97","98","99","100"
    };
};