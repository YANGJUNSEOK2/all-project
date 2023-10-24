/************************************************************************
*	File name : CharacterSelect2p.h
*	Project name : APEX
*	Author	    Primary author : Jookyung Lee
*			        Secondary author : Junseok Yang
*			        Others : Haewon Shon, Wonju Cho
*
*			        header for CharacterSelect2p.h
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"

enum CharacterName2p
{
    JUNSEOK_2P,
    JOOKYUNG_2P,
    WONJU_2P,
    HAEWON_2P
};

class CharacterSelect2p : public State
{
    friend class Game;

public:
    CharacterName2p name2p = JUNSEOK_2P;

protected:
    CharacterSelect2p() : State() {};
    ~CharacterSelect2p() override {};

    // Derived initialize function
    void Initialize() override;
    // Derived Update function
    void Update(float dt) override;
    // Derived Close function
    void Close() override;

private:
    Object character_Select;
    Object text_Haewon, text_Jookyung, text_Wonju, text_Junseok;
    Object chp2, howToSelect;
    Object haewonBorder, jookyungBorder, wonjuBorder, junseokBorder;
    Object character_pass_sound, character_choice_sound,character_back;

    void CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id, SDL_Color color);
    void NumberText(Object *textObject, const char *textContents, const char *id, SDL_Color color);
    void SelectText(Object *textObject, const char *textContents, const char *id, SDL_Color color);
    void CreateBorder();
};