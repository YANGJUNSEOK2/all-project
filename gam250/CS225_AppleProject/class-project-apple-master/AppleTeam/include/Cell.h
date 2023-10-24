/************************************************************************
*	File name : Cell.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Minimum units to be written to the board.
*   This have sprite, position, index and so on.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Engine.h"
#include "Vector2d.h"
struct [[nodiscard]] Cell
{
    Cell() = default;
    ~Cell() = default;
    void SetSprite(std::shared_ptr<sf::Sprite> a_Sprite) noexcept;
    void UpdateSpritePos() noexcept;
    sf::Sprite GetCellSprite() noexcept;

    v2 boardPos = { 0.f,0.f };
    v2 windowCenterPos = { 0.f,0.f };

    sf::Vector2f spriteWindowPos = { 0.f,0.f };
    sf::Sprite cellSprite;
    char charater = 0;

    CellInfo::Type cellType = CellInfo::Type::NOTHING;
};