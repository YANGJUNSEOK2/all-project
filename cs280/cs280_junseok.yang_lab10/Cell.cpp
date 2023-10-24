/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cell.cpp
Purpose: Source file for cell
Project: AStar (CS280 Programming Final)
Author: junseok yang
Creation date: 2021 06 01
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/TransformMatrix.h"

#include "Cell.h"
#include "Image_Anims.h"


Cell::Cell(Vector2DInt xyIndex, char type, Vector2DInt screenPosition)
    : xyIndex(xyIndex), screenPosition(screenPosition), gCost(static_cast<unsigned int>(-1)), fCost(static_cast<unsigned int>(-1)), hCost(static_cast<unsigned int>(-1)), pNext(nullptr)
{
    parent_xyIndex = xyIndex;
    sprite = new Sprite("assets/Images.spt");
    switch (type) {
    case '0':
        sprite->PlayAnimation(static_cast<int>(Images::None));
        break;
    case 'F':
        sprite->PlayAnimation(static_cast<int>(Images::RedX));
        break;
    case 'W':
        sprite->PlayAnimation(static_cast<int>(Images::Black));
        break;
    }
}

Cell::~Cell() {
    delete sprite;
}

Vector2DInt Cell::GetPosition() {
    return screenPosition;
}

Vector2DInt Cell::GetXYIndex() {
    return xyIndex;
}

Vector2DInt Cell::GetParent_xyIndex()
{
    return parent_xyIndex;
}

void Cell::CalculateAstarVariables(Cell* parent, Cell* selected, Heap<Cell*>* visit)
{
    if (parent == nullptr)
    {
        gCost = 0;
    }

    else if
        ((parent->GetXYIndex().x == GetXYIndex().x - 1 && parent->GetXYIndex().y == GetXYIndex().y) ||
        (parent->GetXYIndex().x == GetXYIndex().x + 1 && parent->GetXYIndex().y == GetXYIndex().y) ||
            (parent->GetXYIndex().x == GetXYIndex().x && parent->GetXYIndex().y == GetXYIndex().y - 1) ||
            (parent->GetXYIndex().x == GetXYIndex().x && parent->GetXYIndex().y == GetXYIndex().y + 1))//상하좌우
    {
        if (parent->GetFCost() + 10 < GetFCost())
        {
            gCost = parent->gCost + 10;
            visit->Update(visit->Find(this));
        }
    }
    else if
        ((parent->GetXYIndex().x == GetXYIndex().x - 1 && parent->GetXYIndex().y == GetXYIndex().y - 1) ||
        (parent->GetXYIndex().x == GetXYIndex().x - 1 && parent->GetXYIndex().y == GetXYIndex().y + 1) ||
            (parent->GetXYIndex().x == GetXYIndex().x + 1 && parent->GetXYIndex().y == GetXYIndex().y - 1) ||
            (parent->GetXYIndex().x == GetXYIndex().x + 1 && parent->GetXYIndex().y == GetXYIndex().y + 1)) //대각선
    {
        if (parent->GetFCost() + 14 < GetFCost())
        {
            gCost = parent->gCost + 14;
            visit->Update(visit->Find(this));
        }
    }

    int dstX = abs(selected->GetXYIndex().x - GetXYIndex().x);
    int dstY = abs(selected->GetXYIndex().y - GetXYIndex().y);

    if (dstX > dstY)
    {
        hCost = 14 * dstY + 10 * (dstX - dstY);
    }
    else
    {
        hCost = 14 * dstX + 10 * (dstY - dstX);
    }

    fCost = gCost + hCost;
}

void Cell::Draw() {
    sprite->Draw(TranslateMatrix(screenPosition));

    if (gCost != static_cast<unsigned int>(-1)) {
        // draw G cost replace the "" with a std::to_string( whatever your g cost is)
        Engine::Instance().DrawText(1, screenPosition + Vector2DInt{ -sprite->GetFrameSize().x / 2 + 5, 10 }, std::to_string(GetGCost()), SpriteFont::Justified::Left, 0x0000FFFF);
        // draw H cost replace the "" with a std::to_string( whatever your h cost is)
        Engine::Instance().DrawText(1, screenPosition + Vector2DInt{ sprite->GetFrameSize().x / 2 - 12, 10 }, std::to_string(GetHCost()), SpriteFont::Justified::Right, 0xFF0000FF);
        // draw F cost replace the "" with a std::to_string( whatever your f cost is)
        Engine::Instance().DrawText(0, screenPosition + Vector2DInt{ 0, -22 }, std::to_string(GetFCost()), SpriteFont::Justified::CenterX, 0x000000FF);
    }
}

void Cell::SetToImage(Images image) {
    sprite->PlayAnimation(static_cast<int>(image));
}

Images Cell::GetImage() {
    return static_cast<Images>(sprite->GetAnimation());
}

unsigned int Cell::GetGCost()
{
    return gCost;
}

unsigned int Cell::GetFCost()
{
    return fCost;
}

unsigned int Cell::GetHCost()
{
    return hCost;
}

std::ostream& operator<<(std::ostream& out, Cell*& cell) {
    out << std::endl << "{" << cell->xyIndex.x << ", " << cell->xyIndex.y << '}' << " = " << cell->GetFCost();
    return out;
}