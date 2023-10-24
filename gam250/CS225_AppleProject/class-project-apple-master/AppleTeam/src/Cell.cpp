/************************************************************************
*	File name : Cell.cpp
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Minimum units to be written to the board.
*   This have sprite, position, index and so on.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Cell.h"

void Cell::SetSprite(std::shared_ptr<sf::Sprite> aSprite) noexcept
{
    cellSprite = *aSprite.get();
}

void Cell::UpdateSpritePos() noexcept
{
    cellSprite.setPosition(static_cast<float>(windowCenterPos.x - boardPos.x * CellInfo::CELLSIZE), static_cast<float>(windowCenterPos.y - boardPos.y * CellInfo::CELLSIZE));
}

sf::Sprite Cell::GetCellSprite() noexcept
{
    if (cellType == CellInfo::Type::NORMAL)
    {
        cellSprite.setTextureRect(sf::Rect(0, 0, CellInfo::CELLSIZE, CellInfo::CELLSIZE));
    }
    else if (cellType == CellInfo::Type::NOTHING)
    {
        cellSprite.setTextureRect(sf::Rect(64, 0, CellInfo::CELLSIZE, CellInfo::CELLSIZE));
    }
    else if (cellType == CellInfo::Type::RED)
    {
        cellSprite.setTextureRect(sf::Rect(128, 0, CellInfo::CELLSIZE, CellInfo::CELLSIZE));
    }
    else if (cellType == CellInfo::Type::RED_X)
    {
        cellSprite.setTextureRect(sf::Rect(192, 0, CellInfo::CELLSIZE, CellInfo::CELLSIZE));
    }
    else if (cellType == CellInfo::Type::BLUE)
    {
        cellSprite.setTextureRect(sf::Rect(256, 0, CellInfo::CELLSIZE, CellInfo::CELLSIZE));
    }
    else if (cellType == CellInfo::Type::BLUE_X)
    {
        cellSprite.setTextureRect(sf::Rect(320, 0, CellInfo::CELLSIZE, CellInfo::CELLSIZE));
    }
    else
    {
        cellSprite.setTextureRect(sf::Rect(384, 0, CellInfo::CELLSIZE, CellInfo::CELLSIZE));
    }

    return cellSprite;
}