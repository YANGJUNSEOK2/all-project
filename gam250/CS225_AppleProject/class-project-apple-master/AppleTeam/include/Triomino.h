/************************************************************************
*	File name : Triomino.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description :
*   Explain : Middle of block(cell) is weight. For example,
*   000             0@0                   000
*   0@@  is left up @@0 is right down but @@@ is horizontal,
*   0@0             000                   000
*
*   0@0
*   0@0 is vertical
*   0@0
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Cell.h"
#include "Common.h"

constexpr static int TRIWIDTH = 3;
constexpr static int TRIHEIGHT = 3;

class [[nodiscard]] Triomino
{
public:
    Triomino() noexcept;
    void SetSprite(std::shared_ptr<sf::Sprite> a_Sprite) noexcept;
    void UpdateCellPosition() noexcept;
    void SetType(TriominoInfo::Type aType) noexcept;
    void Update() noexcept;
    TriominoInfo::Type GetType() const noexcept { return mType; }
    Cell GetCell(int r, int c) noexcept { return mTri[r][c]; }
    void TurnOver() noexcept { isBlue = !isBlue; }
    void SetIsPlayer(bool isBlueTurn) noexcept { isBlue = isBlueTurn; }
private:
    TriominoInfo::Type mType = TriominoInfo::Type::LEFTDOWN;
    Cell mTri[TRIWIDTH][TRIHEIGHT];
    std::shared_ptr<sf::Sprite> triSprite;
    bool isBlue = true;
};