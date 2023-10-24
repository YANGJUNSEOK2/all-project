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
#include "CommonLevel.h"

void MainMenu::Initialize()
{
    camera.position.Set(0, 0, 0);

    mainMenu.sprite.LoadImage("texture/mainmenu/main_menu_start.png", m_renderer);
    mainMenu.transform.SetScale(m_width, m_height);

    mainMenu.transform.position.Set(0.f, 0.f, 0.f);
    AddObject(&mainMenu);

    backgroundMusic.SetName("background");
    backgroundMusic.sound.LoadSound("sound/menu_background.wav");
    backgroundMusic.sound.Play();
    AddObject(&backgroundMusic);

    move.SetName("movesound");
    move.sound.LoadSound("sound/menu_move.wav");
    AddObject(&move);

    select.SetName("selectsound");
    select.sound.LoadSound("sound/menu_select.wav");
    AddObject(&select);
}

void MainMenu::Update(float dt)
{
	/******************* State ******************/
    if (m_input->IsTriggered(SDL_SCANCODE_RETURN) || m_input->IsTriggered(SDL_SCANCODE_SPACE))
    {
        select.sound.Play();
        switch (menuImageStatus)
        {
        case MainMenuImage::START_MENU:
            m_game->Change(LV_CharacterSelect1p);
            break;
        case MainMenuImage::CREDIT_MENU:
            m_game->Change(LV_Credit);
            break;
        case MainMenuImage::EXIT_MENU:
            m_game->Quit();
            break;
        }
    }
    MenuSelect();
	CharacterUI();

	// Must be one of the last functions called at the end of State Update
	Render(dt);
}

void MainMenu::Close()
{
	// Wrap up state
	ClearBaseState();
}

void MainMenu::MenuSelect()
{
    if(m_input->IsTriggered(SDL_SCANCODE_UP))
    {
        move.sound.Play();
        switch(menuImageStatus)
        {
        case MainMenuImage::START_MENU:
            menuImageStatus = MainMenuImage::EXIT_MENU;
            break;
        case MainMenuImage::CREDIT_MENU:
            menuImageStatus = MainMenuImage::START_MENU;
            break;
        case MainMenuImage::EXIT_MENU:
            menuImageStatus = MainMenuImage::CREDIT_MENU;
            break;
        }
        MenuImageChange();
    }
    if (m_input->IsTriggered(SDL_SCANCODE_DOWN))
    {
        move.sound.Play();
        switch (menuImageStatus)
        {
        case MainMenuImage::START_MENU:
            menuImageStatus = MainMenuImage::CREDIT_MENU;
            break;
        case MainMenuImage::CREDIT_MENU:
            menuImageStatus = MainMenuImage::EXIT_MENU;
            break;
        case MainMenuImage::EXIT_MENU:
            menuImageStatus = MainMenuImage::START_MENU;
            break;
        }
        MenuImageChange();
    }
}

void MainMenu::MenuImageChange()
{
    mainMenu.sprite.Free();
    switch (menuImageStatus)
    {
    case MainMenuImage::START_MENU:
        mainMenu.sprite.LoadImage("texture/mainmenu/main_menu_start.png", m_renderer);
        break;
    case MainMenuImage::CREDIT_MENU:
        mainMenu.sprite.LoadImage("texture/mainmenu/main_menu_credit.png", m_renderer);
        break;
    case MainMenuImage::EXIT_MENU:
        mainMenu.sprite.LoadImage("texture/mainmenu/main_menu_exit.png", m_renderer);
        break;
    }
}

void MainMenu::CharacterUI()
{
	// haewon
	RemoveObject(&haewon);
	haewon.sprite.LoadImage("texture/mainmenu/haewon.png", m_renderer);
	haewon.transform.SetScale(230, 250);
	haewon.transform.position.Set(-500,100,0);
	AddObject(&haewon);
	
	// wonju
	RemoveObject(&wonju);
	wonju.sprite.LoadImage("texture/mainmenu/wonju.png", m_renderer);
	wonju.transform.SetScale(230, 250);
	wonju.transform.position.Set(-500,-100,0);
	AddObject(&wonju);
	
	// jookyung
	RemoveObject(&jookyung);
	jookyung.sprite.LoadImage("texture/mainmenu/jookyung.png", m_renderer);
	jookyung.transform.SetScale(230, 250);
	jookyung.transform.position.Set(500,100,0);
	AddObject(&jookyung);
	
	// junseok
	RemoveObject(&junseok);
	junseok.sprite.LoadImage("texture/mainmenu/junseok.png", m_renderer);
	junseok.transform.SetScale(230, 250);
	junseok.transform.position.Set(500,-100,0);
	AddObject(&junseok);
}