/************************************************************************
*	File name : Player.h
*	Project name : APEX
*	Author	    Primary author : Haewon Shon
*			        Secondary author : Jookyung Lee
*			        Others : Junseok Yang, Wonju Cho
*
*			        header for Player.cpp
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "CustomBaseObject.h"
#include <engine/State.h>

struct Controller
{
    SDL_Scancode left;
    SDL_Scancode right;
    SDL_Scancode jump;
    SDL_Scancode attack;
    SDL_Scancode jump_down;
};

class  Player
{
public:
    enum Status { LEFT_STAND, RIGHT_STAND, LEFT_WALK, RIGHT_WALK, LEFT_ATTACK, RIGHT_ATTACK, WIN };
    enum Direction { LEFT, RIGHT };

    struct CharacterStatus
    {
        float knockbackDefault;
        float attackDefault;
        float speed;
        float reach;
        float power;
    };
    CharacterStatus junseok = { 0.7f, 0.5f, 1400.f, 200.f, 50.f };
    CharacterStatus jookyung = { 0.7f, 0.5f, 1400.f, 200.f, 50.f };
    CharacterStatus wonju = { 0.7f, 0.5f, 1400.f, 200.f, 50.f };
    CharacterStatus haewon = { 0.7f, 0.5f, 1400.f, 200.f, 50.f };

    /* Getters & Setters */
    void SetKnockBackDelay(float delay) { knockbackDelay = delay; }
    void SetStance(float stance) { characterStatus.knockbackDefault = stance; }
    void SetPower(float input_power) { characterStatus.power = input_power; }
    void SetWin() { status = Player::Status::WIN; }
    void SetSpeed(float value) { characterStatus.speed = value; }
    void SetIsStickSide(bool value) { isStickSide = value; }
    void SetItemDuration(float value) { itemDuration = value; }
    void SetItemName(std::string name) { itemName = std::move(name); }
    void SetRespawnTime(float time) { respawnTime = time; }
    bool GetIsStickSide() { return isStickSide; }
    float GetItemDuration() { return itemDuration; }
    CharacterStatus GetCharacterStatus() { return characterStatus; }
    int GetCharacter() { return character; }
    std::string GetItemName() { return itemName; }
    float GetRespawnTime() { return respawnTime; }
    

    /* Player Moving */
    void Jump();
    void DownJump();
    void Attack();
    void SetPlayerMovingAndStatus(float dt);
    void CreatePlayerObject(Player* other, b2Vec2 startingPos, int id, int playerNum);
    void PlayerMovement(float dt);
    void SetCollisionMoving();

    /* Animation */
    void AnimationUpdate(float dt);
    char* GetLeftEffectFileName() { return leftEffectFile; }
    char* GetRightEffectFileName() { return rightEffectFile; }

    /* Status */
    void AddSpeed(float value);
    void AddPower(float value);
    void AddStance(float value);

    /* Others */
    void AllocateBody(b2World* world);
    CustomBaseObject& GetObject() { return object; }
    Direction GetDirection() { return characterDirection; }

    /* effects */
    Object effect;
    bool isAttack = false;
    float effectLifeTime = 0.f;
    Object itemEffect;

    /* trap */
    CustomBaseObject trap;
    float trapCoolDown = 0.f;

private:
    /* times for status */
    float knockbackDelay = 0.f;
    float jumpTime = 0.f;
    float downDelay = 0.f;
    float attackDelay = 0.f;
    float respawnTime = 0.f;

    /* default */
    CharacterStatus characterStatus;
    Controller controller;
    bool isStickSide = false;

    /* image file name */
    char* leftStandFile = nullptr;
    char* rightStandFile = nullptr;
    char* leftWalkFile = nullptr;
    char* rightWalkFile = nullptr;
    char* leftAttackFile = nullptr;
    char* rightAttackFile = nullptr;
    char* winFile = nullptr;
    char* leftEffectFile = nullptr;
    char* rightEffectFile = nullptr;

    /* Status */
    Direction characterDirection;
    Status prevStatus;
    Status status;
    Player* opponent;
    float itemDuration = 0.f;
    std::string itemName = std::move("none");

    int character = 1;
    CustomBaseObject object;
};
