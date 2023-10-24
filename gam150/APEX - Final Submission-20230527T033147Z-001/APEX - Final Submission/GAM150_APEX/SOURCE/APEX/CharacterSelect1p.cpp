/************************************************************************
*	File name : CharacterSelect1p.cpp
*	Project name : APEX
*	Author	    Primary author : Jookyung Lee
*			        Secondary author : Junseok Yang
*			        Others : Haewon Shon, Wonju Cho
*			        
*			        Functions for 1p Character Selection
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "CommonLevel.h"
#include "CharacterSelect1p.h"

void CharacterSelect1p::Initialize()
{
    // Set position of the camera
    camera.position.Set(0, 0, 0);

    character_Select.sprite.LoadImage("texture/character_choice/character_select.png", m_renderer);
    character_Select.transform.SetScale(m_width, m_height / 2);
    character_Select.transform.position.Set(0.f, 30.f, 0.f);
    AddObject(&character_Select);

    mainFont = TTF_OpenFont("font/JaykopDot.ttf", 64);

    CreateAndRegisterHudText(&text_Junseok, "Junseok", "Junseok", { 128,0,255,255 });
    text_Junseok.transform.position.Set(-480.f, 230.f, 1.f);

    CreateAndRegisterHudText(&text_Jookyung, "Jookyung", "Jookyung", { 0,0,250,255 });
    text_Jookyung.transform.position.Set(-160.f, 230.f, 1.f);

    CreateAndRegisterHudText(&text_Wonju, "Wonju"   , "Wonju", { 100,100,100,255 });
    text_Wonju.transform.position.Set(160.f, 230.f, 1.f);

    CreateAndRegisterHudText(&text_Haewon, "Haewon", "Haewon", { 30,30,30,255 });
    text_Haewon.transform.position.Set(480.f, 230.f, 1.f);

    SelectText(&chp1, "1P Character Select", "1P Character Select", { 0,0,0,255 });
    chp1.transform.position.Set(0.f, 300.f, 1.f);

    SelectText(&howToSelect, "A, D to select and H to choose", "howToSelect", { 0,0,0,255 });
    howToSelect.transform.position.Set(0.f, -250.f, 1.f);

    character_pass_sound.SetName("character_pass");
    character_pass_sound.sound.LoadSound("sound/menu_move.wav");
    character_choice_sound.SetName("character_choice");
    character_choice_sound.sound.LoadSound("sound/character_choice.wav");
    character_back.SetName("character_back");
    character_back.sound.LoadSound("sound/character.wav");
    character_back.sound.Play();
}

void CharacterSelect1p::Update(float dt)
{
    CreateBorder();
    /******************* State ******************/

    // Move to level1 by pressing 'C' key
    if (m_input->IsTriggered(SDL_SCANCODE_H))
    {
        character_choice_sound.sound.Play();

        m_game->Change(LV_CharacterSelect2p);
    }

    // Must be one of the last functions called at the end of State Update
    Render(dt);
}

void CharacterSelect1p::Close()
{
    // Wrap up state
    ClearBaseState();

    character_back.sound.Free();
    character_pass_sound.sound.Free();
    character_choice_sound.sound.Free();
    RemoveObject(&character_back);
    RemoveObject(&character_pass_sound);
    RemoveObject(&character_choice_sound);
}

void CharacterSelect1p::CreateBorder()
{
    switch (name1p)
    {
    case CharacterName1p::JUNSEOK_1P:
        junseokBorder.sprite.Free();
        RemoveObject(&jookyungBorder);
        RemoveObject(&wonjuBorder);
        RemoveObject(&haewonBorder);
        junseokBorder.sprite.LoadImage("texture/character_choice/junseokBorder.png", m_renderer);
        junseokBorder.transform.SetScale(240, 480);
        junseokBorder.transform.position.Set(-480.f, 40.f, 1.f);
        AddObject(&junseokBorder);
        m_game->p1Character = 1;
        if (m_input->IsTriggered(SDL_SCANCODE_D))
        {
            character_pass_sound.sound.Play();
            name1p = JOOKYUNG_1P;
        }
        if (m_input->IsTriggered(SDL_SCANCODE_A))
        {
            character_pass_sound.sound.Play();
            name1p = HAEWON_1P;
        }
        break;

    case CharacterName1p::JOOKYUNG_1P:
        jookyungBorder.sprite.Free();
        RemoveObject(&junseokBorder);
        RemoveObject(&wonjuBorder);
        RemoveObject(&haewonBorder);
        jookyungBorder.sprite.LoadImage("texture/character_choice/jookyungBorder.png", m_renderer);
        jookyungBorder.transform.SetScale(240, 480);
        jookyungBorder.transform.position.Set(-160.f, 40.f, 1.f);
        AddObject(&jookyungBorder);
        m_game->p1Character = 2;
        if (m_input->IsTriggered(SDL_SCANCODE_D))
        {
            character_pass_sound.sound.Play();
            name1p = WONJU_1P;
        }
        if (m_input->IsTriggered(SDL_SCANCODE_A))
        {
            character_pass_sound.sound.Play();
            name1p = JUNSEOK_1P;
        }
        break;

    case CharacterName1p::WONJU_1P:
        wonjuBorder.sprite.Free();
        RemoveObject(&junseokBorder);
        RemoveObject(&jookyungBorder);
        RemoveObject(&haewonBorder);
        wonjuBorder.sprite.LoadImage("texture/character_choice/wonjuBorder.png", m_renderer);
        wonjuBorder.transform.SetScale(240, 480);
        wonjuBorder.transform.position.Set(160.f, 40.f, 1.f);
        AddObject(&wonjuBorder);
        m_game->p1Character = 3;
        if (m_input->IsTriggered(SDL_SCANCODE_D))
        {
            character_pass_sound.sound.Play();
            name1p = HAEWON_1P;
        }
        if (m_input->IsTriggered(SDL_SCANCODE_A))
        {
            character_pass_sound.sound.Play();
            name1p = JOOKYUNG_1P;
        }
        break;

    case CharacterName1p::HAEWON_1P:
        haewonBorder.sprite.Free();
        RemoveObject(&junseokBorder);
        RemoveObject(&wonjuBorder);
        RemoveObject(&jookyungBorder);
        haewonBorder.sprite.LoadImage("texture/character_choice/haewonBorder.png", m_renderer);
        haewonBorder.transform.SetScale(240, 480);
        haewonBorder.transform.position.Set(480.f, 40.f, 1.f);
        AddObject(&haewonBorder);
        m_game->p1Character = 4;
        if (m_input->IsTriggered(SDL_SCANCODE_D))
        {
            character_pass_sound.sound.Play();
            name1p = JUNSEOK_1P;
        }
        if (m_input->IsTriggered(SDL_SCANCODE_A))
        {
            character_pass_sound.sound.Play();
            name1p = WONJU_1P;
        }
        break;
    }
}

void CharacterSelect1p::CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id, SDL_Color color)
{
    // Set the object's name
    textObject->SetName(id);

    // Set the scale of the object
    textObject->transform.SetScale(128, 50);

    // Set the text to render out
    textObject->text.SetText(State::m_renderer, textContents, mainFont);

    // Set the colors r,g,b,a (0~255)
    textObject->text.color = color;

    // Set either if the object to be hud or not
    textObject->text.isHud = true;

    // Register the object to the state
    AddObject(textObject);
}

void CharacterSelect1p::SelectText(Object *textObject, const char *textContents, const char *id, SDL_Color color)
{
    // Set the object's name
    textObject->SetName(id);

    // Set the scale of the object
    textObject->transform.SetScale(550, 50);

    // Set the text to render out
    textObject->text.SetText(State::m_renderer, textContents, mainFont);

    // Set the colors r,g,b,a (0~255)
    textObject->text.color = color;

    // Set either if the object to be hud or not
    textObject->text.isHud = true;

    // Register the object to the state
    AddObject(textObject);
}