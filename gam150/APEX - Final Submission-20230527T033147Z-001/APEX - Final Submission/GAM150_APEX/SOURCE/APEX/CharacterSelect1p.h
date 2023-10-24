/************************************************************************
*	File name : CharacterSelect1p.h
*	Project name : APEX
*	Author	    Primary author : Jookyung Lee
*			        Secondary author : Junseok Yang
*			        Others : Haewon Shon, Wonju Cho
*			        
*			        Header for CharacterSelect1p.cpp
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"
#include "CustomBaseObject.h"

enum CharacterName1p
{
    JUNSEOK_1P,
    JOOKYUNG_1P,
    WONJU_1P,
    HAEWON_1P
};

class CharacterSelect1p : public State
{
    friend class Game;

public:
    CharacterName1p name1p = JUNSEOK_1P;

protected:
    CharacterSelect1p() : State() {};
    ~CharacterSelect1p() override {};

    // Derived initialize function
    void Initialize() override;
    // Derived Update function
    void Update(float dt) override;
    // Derived Close function
    void Close() override;

private:
    Object character_Select;
    Object text_Haewon, text_Jookyung, text_Wonju, text_Junseok;
    Object chp1, howToSelect;
    Object haewonBorder, jookyungBorder, wonjuBorder, junseokBorder;
    Object character_pass_sound, character_choice_sound,character_back;

    void CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id, SDL_Color color);
    void SelectText(Object *textObject, const char *textContents, const char *id, SDL_Color color);
    void CreateBorder();
};