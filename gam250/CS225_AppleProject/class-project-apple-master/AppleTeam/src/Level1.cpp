/************************************************************************
*	File name : Level1.cpp
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Level1 Scene. 8x8 board and can put blocks using mouse but cannot get scores
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Level1.h"
#include "Common.h"
#include <SFML/Graphics.hpp>
#include "Engine.h"

bool Level1::Init() noexcept
{
    
    *i++;
    return true;
}

void Level1::Update([[maybe_unused]]double delta_time) noexcept
{
    mTri.Update();
    sf::Vector2i getmousePos = sf::Mouse::getPosition(Engine::WindowIns().Getwindow());
    Vector2 mousePos = Vector2{ getmousePos.x, getmousePos.y };
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        Engine::LoggerIns().LogDebug("MousePosX : ");
        Engine::LoggerIns().LogDebug(mousePos.x);
        Engine::LoggerIns().LogDebug("MousePosY : ");
        Engine::LoggerIns().LogDebug(getmousePos.y);
        if (lvBoard.IsMousePosOnBoard(mousePos) == true)
        {
            Vector2 cellIndex = lvBoard.MousePosToCellLoction(mousePos);
            Engine::LoggerIns().LogDebug("cellIndxX : ");
            Engine::LoggerIns().LogDebug(cellIndex.x);
            Engine::LoggerIns().LogDebug("cellIndxY : ");
            Engine::LoggerIns().LogDebug(cellIndex.y);
            if (lvBoard.Isput(cellIndex, mTri.GetType()) == true)
            {
                lvBoard.SetCellType(cellIndex, mTri.GetType(), isBlue);
                Engine::LoggerIns().LogEvent("Can put");
                mTri.TurnOver();
                isBlue = !isBlue;
            }
            else
            {
                lvBoard.DebugBoardPosition();
                Engine::LoggerIns().LogEvent("cannot put");
                lvBoard.UpdateCharacter();
            }
        }
    }
    
    if (Engine::InputManagerIns().IsKeyReleased(InputManager::KeyboardMapping::F2))
    {
        Engine::SceneManagerIns().SetNextScene(LevelNum::Splash);
    }
    else if (Engine::InputManagerIns().IsKeyDown(InputManager::KeyboardMapping::_1))
    {
        mTri.SetType(TriominoInfo::Type::LEFTDOWN);
    }
    else if (Engine::InputManagerIns().IsKeyDown(InputManager::KeyboardMapping::_2))
    {
        mTri.SetType(TriominoInfo::Type::LEFTUP);
    }
    else if (Engine::InputManagerIns().IsKeyDown(InputManager::KeyboardMapping::_3))
    {
        mTri.SetType(TriominoInfo::Type::RIGHTDOWN);
    }
    else if (Engine::InputManagerIns().IsKeyDown(InputManager::KeyboardMapping::_4))
    {
        mTri.SetType(TriominoInfo::Type::RIGHTUP);
    }
    else if (Engine::InputManagerIns().IsKeyDown(InputManager::KeyboardMapping::_5))
    {
        mTri.SetType(TriominoInfo::Type::HORIZONTAL);
    }
    else if (Engine::InputManagerIns().IsKeyDown(InputManager::KeyboardMapping::_6))
    {
        mTri.SetType(TriominoInfo::Type::VERTICAL);
    }
}

void Level1::Draw() noexcept
{
    Engine::WindowIns().Getwindow().clear(sf::Color::Black);
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Engine::WindowIns().Getwindow().draw(lvBoard.GetCell(r, c).GetCellSprite());
        }
    }
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            Engine::WindowIns().Getwindow().draw(mTri.GetCell(r, c).GetCellSprite());
        }
    }
    Engine::WindowIns().Getwindow().display();
}

void Level1::ShutDown() noexcept
{

}

void Level1::SetNextScene() noexcept
{

}

std::string Level1::GetName() const noexcept
{
    return levelName;
}