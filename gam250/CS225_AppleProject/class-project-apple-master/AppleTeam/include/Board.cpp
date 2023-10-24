/************************************************************************
*	File name : Board.cpp
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Sets of cells.
*   This have sprite, position, index and so on.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Board.h"
#include <iostream>
#include "Common.h"
#include "SFML/Graphics.hpp"
#include <MathLibrary.h>
#include <queue>

template<int WIDTH, int HEIGHT>
Board<WIDTH, HEIGHT>::Board() noexcept
{
    float halfWidth = WIDTH * 0.5f;
    float halfHeight = HEIGHT * 0.5f;
    Vector2 winCenter = Engine::WindowIns().GetSize();
    float halfWinX = winCenter.x * 0.5f;
    float halfWinY = winCenter.y * 0.5f;
    for (int r = 0; r < WIDTH; r++)
    {
        for (int c = 0; c < HEIGHT; c++)
        {
            mBoard[r][c].boardPos = { (r - halfWidth), (c - halfHeight) };
            mBoard[r][c].windowCenterPos = { halfWinX, halfWinY };
            mBoard[r][c].cellType = CellInfo::Type::NORMAL;
        }
    }
}

template<int WIDTH, int HEIGHT>
void Board<WIDTH, HEIGHT>::SetSprite(std::shared_ptr<sf::Sprite> a_Sprite) noexcept
{
    boardSprite = a_Sprite;
}

template<int WIDTH, int HEIGHT>
void Board<WIDTH, HEIGHT>::UpdateCellPosition() noexcept
{
    for (int r = 0; r < WIDTH; r++)
    {
        for (int c = 0; c < HEIGHT; c++)
        {
            mBoard[r][c].SetSprite(boardSprite);
            mBoard[r][c].UpdateSpritePos();
        }
    }
}
template<int WIDTH, int HEIGHT>
bool Board<WIDTH, HEIGHT>::Isput(Vector2 cellIndex, TriominoInfo::Type triType) const noexcept
{
    if (mBoard[cellIndex.x][cellIndex.y].cellType != CellInfo::Type::NORMAL)
    {
        return false;
    }
    if (triType == TriominoInfo::Type::LEFTUP)
    {
        if (cellIndex.y == 0 || cellIndex.x == 0)
        {
            return false;
        }
        Vector2 right = { GetRight(cellIndex.x), cellIndex.y };
        Vector2 down = { cellIndex.x, cellIndex.y - 1 };
        if (GetCellType(right) != CellInfo::Type::NORMAL || GetCellType(down) != CellInfo::Type::NORMAL)
        {
            return false;
        }
    }
    else if (triType == TriominoInfo::Type::LEFTDOWN)
    {
        if (cellIndex.y == HEIGHT - 1 || cellIndex.x == 0)
        {
            return false;
        }
        Vector2 right = { GetRight(cellIndex.x), cellIndex.y };
        
        Vector2 up = { cellIndex.x, cellIndex.y+1 };
        if (GetCellType(right) != CellInfo::Type::NORMAL || GetCellType(up) != CellInfo::Type::NORMAL)
        {
            return false;
        }
    }
    else if (triType == TriominoInfo::Type::RIGHTUP)
    {
        if (cellIndex.x == WIDTH - 1 || cellIndex.y == 0)
        {
            return false;
        }
        Vector2 left = { GetLeft(cellIndex.x), cellIndex.y };
        Vector2 down = { cellIndex.x, cellIndex.y - 1 };
        if (GetCellType(left) != CellInfo::Type::NORMAL || GetCellType(down) != CellInfo::Type::NORMAL)
        {
            return false;
        }
    }
    else if (triType == TriominoInfo::Type::RIGHTDOWN)
    {
        if (cellIndex.y == HEIGHT - 1 || cellIndex.x == WIDTH - 1)
        {
            return false;
        }
        Vector2 left = { GetLeft(cellIndex.x), cellIndex.y };
        Vector2 up = { cellIndex.x, cellIndex.y + 1 };
        if (GetCellType(left) != CellInfo::Type::NORMAL || GetCellType(up) != CellInfo::Type::NORMAL)
        {
            return false;
        }
    }
    else if (triType == TriominoInfo::Type::HORIZONTAL)
    {
        if (cellIndex.x == WIDTH - 1 || cellIndex.x == 0)
        {
            return false;
        }
        Vector2 left = { GetLeft(cellIndex.x), cellIndex.y };
        Vector2 right = { GetRight(cellIndex.x), cellIndex.y };
        if (GetCellType(left) != CellInfo::Type::NORMAL || GetCellType(right) != CellInfo::Type::NORMAL)
        {
            return false;
        }
    }
    else if (triType == TriominoInfo::Type::VERTICAL)
    {
        if (cellIndex.y == 0 || cellIndex.y == HEIGHT - 1)
        {
            return false;
        }
        Vector2 up = { cellIndex.x, cellIndex.y + 1 };
        Vector2 down = { cellIndex.x, cellIndex.y - 1 };
        if (GetCellType(up) != CellInfo::Type::NORMAL || GetCellType(down) != CellInfo::Type::NORMAL)
        {
            return false;
        }
    }
    return true;
}

template<int WIDTH, int HEIGHT>
void Board<WIDTH, HEIGHT>::SetCellType(Vector2 cellIndex, TriominoInfo::Type triType, bool isBlue) noexcept
{
    if (triType == TriominoInfo::Type::LEFTUP)
    {
        Vector2 right = { GetRight(cellIndex.x), cellIndex.y };
        Vector2 down = { cellIndex.x, cellIndex.y - 1 };
        if (isBlue == true)
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::BLUE;
            mBoard[right.x][right.y].cellType = CellInfo::Type::BLUE;
            mBoard[down.x][down.y].cellType = CellInfo::Type::BLUE;
            Engine::LoggerIns().LogEvent("isBlue");
        }
        else
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::RED;
            mBoard[right.x][right.y].cellType = CellInfo::Type::RED;
            mBoard[down.x][down.y].cellType = CellInfo::Type::RED;
            Engine::LoggerIns().LogEvent("isRed");
        }
    }
    else if (triType == TriominoInfo::Type::LEFTDOWN)
    {
        Vector2 right = { GetRight(cellIndex.x), cellIndex.y };
        Vector2 up = { cellIndex.x, cellIndex.y + 1 };
        if (isBlue == true)
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::BLUE;
            mBoard[right.x][right.y].cellType = CellInfo::Type::BLUE;
            mBoard[up.x][up.y].cellType = CellInfo::Type::BLUE;
            Engine::LoggerIns().LogEvent("isBlue");
        }
        else
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::RED;
            mBoard[right.x][right.y].cellType = CellInfo::Type::RED;
            mBoard[up.x][up.y].cellType = CellInfo::Type::RED;
            Engine::LoggerIns().LogEvent("isRed");
        }
    }
    else if (triType == TriominoInfo::Type::RIGHTUP)
    {
        Vector2 left = { cellIndex.x + 1, cellIndex.y };
        Vector2 down = { cellIndex.x, cellIndex.y - 1 };
        if (isBlue == true)
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::BLUE;
            mBoard[left.x][left.y].cellType = CellInfo::Type::BLUE;
            mBoard[down.x][down.y].cellType = CellInfo::Type::BLUE;
            Engine::LoggerIns().LogEvent("isBlue");
        }
        else
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::RED;
            mBoard[left.x][left.y].cellType = CellInfo::Type::RED;
            mBoard[down.x][down.y].cellType = CellInfo::Type::RED;
            Engine::LoggerIns().LogEvent("isRed");
        }
    }
    else if (triType == TriominoInfo::Type::RIGHTDOWN)
    {
        Vector2 left = { cellIndex.x + 1, cellIndex.y };
        Vector2 up = { cellIndex.x, cellIndex.y + 1 };
        if (isBlue == true)
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::BLUE;
            mBoard[left.x][left.y].cellType = CellInfo::Type::BLUE;
            mBoard[up.x][up.y].cellType = CellInfo::Type::BLUE;
            Engine::LoggerIns().LogEvent("isBlue");
        }
        else
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::RED;
            mBoard[left.x][left.y].cellType = CellInfo::Type::RED;
            mBoard[up.x][up.y].cellType = CellInfo::Type::RED;
            Engine::LoggerIns().LogEvent("isRed");
        }
    }
    else if (triType == TriominoInfo::Type::HORIZONTAL)
    {
        Vector2 left = { cellIndex.x + 1, cellIndex.y };
        Vector2 right = { cellIndex.x - 1, cellIndex.y };
        if (isBlue == true)
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::BLUE;
            mBoard[left.x][left.y].cellType = CellInfo::Type::BLUE;
            mBoard[right.x][right.y].cellType = CellInfo::Type::BLUE;
            Engine::LoggerIns().LogEvent("isBlue");
        }
        else
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::RED;
            mBoard[left.x][left.y].cellType = CellInfo::Type::RED;
            mBoard[right.x][right.y].cellType = CellInfo::Type::RED;
            Engine::LoggerIns().LogEvent("isRed");
        }
    }
    else if (triType == TriominoInfo::Type::VERTICAL)
    {
        Vector2 up = { cellIndex.x, cellIndex.y + 1 };
        Vector2 down = { cellIndex.x, cellIndex.y - 1 };
        if (isBlue == true)
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::BLUE;
            mBoard[up.x][up.y].cellType = CellInfo::Type::BLUE;
            mBoard[down.x][down.y].cellType = CellInfo::Type::BLUE;
            Engine::LoggerIns().LogEvent("isBlue");
        }
        else
        {
            mBoard[cellIndex.x][cellIndex.y].cellType = CellInfo::Type::RED;
            mBoard[up.x][up.y].cellType = CellInfo::Type::RED;
            mBoard[down.x][down.y].cellType = CellInfo::Type::RED;
            Engine::LoggerIns().LogEvent("isRed");
        }
    }
}

template<int WIDTH, int HEIGHT>
void Board<WIDTH, HEIGHT>::UpdateCharacter() noexcept
{
    //This is for window debug using console
    for (int row = 0; row < WIDTH; row++)
    {
        for (int column = 0; column < HEIGHT; column++)
        {
            switch (mBoard[row][column].cellType)
            {
            case CellInfo::Type::RED:
                mBoard[row][column].charater = 'R';
                break;
            case CellInfo::Type::GREEN:
                mBoard[row][column].charater = 'G';
                break;
            case CellInfo::Type::BLUE:
                mBoard[row][column].charater = 'B';
                break;
            case CellInfo::Type::RED_X:
                mBoard[row][column].charater = 'r';
                break;
            case CellInfo::Type::GREEN_X:
                mBoard[row][column].charater = 'g';
                break;
            case CellInfo::Type::BLUE_X:
                mBoard[row][column].charater = 'b';
                break;
            case CellInfo::Type::NORMAL:
                mBoard[row][column].charater = '0';
                break;
            }
        }
    }
}
template<int WIDTH, int HEIGHT>
void Board<WIDTH, HEIGHT>::DebugBoardPosition() noexcept
{
    for (int r = 0; r < WIDTH; r++)
    {
        for (int c = 0; c < HEIGHT; c++)
        {
            sf::Vector2f rect = mBoard[r][c].GetCellSprite().getPosition();
            std::string spritePosX = std::to_string(rect.x);
            std::string R = std::to_string(r);
            std::string C = std::to_string(c);
            std::string spritePosY = std::to_string(rect.y);
            Engine::LoggerIns().LogDebug(spritePosX + " X position " + R);
            Engine::LoggerIns().LogDebug(spritePosY + " Y position " + C);
        }
    }
}

template<int WIDTH, int HEIGHT>
bool Board<WIDTH, HEIGHT>::IsMousePosOnBoard(Vector2 mousePos) noexcept
{
    sf::Vector2i windowPos = Engine::WindowIns().Getwindow().getPosition();
    std::string winPosX = std::to_string(windowPos.x);
    std::string winPosY = std::to_string(windowPos.y);
    Engine::LoggerIns().LogDebug(winPosX + winPosY + "WindowPos");
    sf::Vector2f rect = mBoard[0][0].GetCellSprite().getPosition();
    sf::Vector2f rect1 = mBoard[WIDTH-1][HEIGHT - 1].GetCellSprite().getPosition();
    float globalPosX = rect.x;
    float globalPosY = rect.y;
    float globalPosX1 = rect1.x;
    float globalPosY1 = rect1.y;

    if (mousePos.x < (globalPosX1 - CellInfo::CELLSIZE * 0.5) ||
        mousePos.y < (globalPosY1 - CellInfo::CELLSIZE * 0.5))
    {
        std::string spritePosX = std::to_string(globalPosX);
        std::string spritePosY = std::to_string(globalPosY);
        Engine::LoggerIns().LogDebug(spritePosX + spritePosY + "Out of board. It below from board");
        return false;
    }
    else if (mousePos.x > (globalPosX + CellInfo::CELLSIZE * 0.5) ||
        mousePos.y > (globalPosY + CellInfo::CELLSIZE * 0.5))
    {
        std::string spritePosX = std::to_string(globalPosX1);
        std::string spritePosY = std::to_string(globalPosY1);
        Engine::LoggerIns().LogDebug(spritePosX + spritePosY + "Out of board. It up from board");
        return false;
    }
    Engine::LoggerIns().LogDebug("in board.");
    return true;
}

template<int WIDTH, int HEIGHT>
Vector2 Board<WIDTH, HEIGHT>::MousePosToCellLoction(Vector2 mousePos) noexcept
{
    sf::Vector2f rect = mBoard[0][0].GetCellSprite().getPosition();
    Vector2 boardPosition = Vector2{ static_cast<int>(((mousePos.x - rect.x) / -CellInfo::CELLSIZE) + 0.5), static_cast<int>(((mousePos.y- rect.y) / -CellInfo::CELLSIZE) + 0.5) };
    return boardPosition;
}