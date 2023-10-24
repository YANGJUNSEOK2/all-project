/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Standard.cpp
Purpose: Source file for Standard
Project: CS280
Author: junseok.yang
Creation date: 4/28/2021
-----------------------------------------------------------------*/
#include "Standard.h"
#include "Cell.h"
#include "Image_Anims.h"

bool Standard::Visit()
{
    Vector2DInt currVec = toVisit.front();
    Vector2DInt vecLeft = Vector2DInt{ currVec.x - 1,currVec.y };
    Vector2DInt vecRight = Vector2DInt{ currVec.x + 1,currVec.y };
    Vector2DInt vecDown = Vector2DInt{ currVec.x,currVec.y - 1 };
    Vector2DInt vecUp = Vector2DInt{ currVec.x,currVec.y + 1 };

    for (int i = 0; i < toVisit.size(); i++)
    {
        if (TryToAdd(Vector2DInt{ currVec.x,currVec.y }) == true)
        {
            if (GetBoard()->GetCell(Vector2DInt{ currVec.x,currVec.y })->GetImage() == Images::Red)
            {
                if (TryToAdd(vecUp) == true)
                {
                    if (GetBoard()->GetCell(vecUp)->GetImage() != Images::Off)
                    {
                        GetBoard()->GetCell(vecUp)->SetToImage(Images::RedX);
                        toVisit.push_back(vecUp);
                    }
                }
                if (TryToAdd(vecRight) == true)
                {
                    if (GetBoard()->GetCell(vecRight)->GetImage() != Images::Off)
                    {
                        GetBoard()->GetCell(vecRight)->SetToImage(Images::RedX);
                        toVisit.push_back(vecRight);
                    }
                }
                if (TryToAdd(vecDown) == true)
                {
                    if (GetBoard()->GetCell(vecDown)->GetImage() != Images::Off)
                    {
                        GetBoard()->GetCell(vecDown)->SetToImage(Images::RedX);
                        toVisit.push_back(vecDown);
                    }
                }
                if (TryToAdd(vecLeft) == true)
                {
                    if (GetBoard()->GetCell(vecLeft)->GetImage() != Images::Off)
                    {
                        GetBoard()->GetCell(vecLeft)->SetToImage(Images::RedX);
                        toVisit.push_back(vecLeft);
                    }
                }
            }
        }
    }
    toVisit.pop_front();
    if (toVisit.empty() == false)
        return false;

    if (toVisit.empty() == true)
        return true;

    return false;
}

void Standard::PlayerSelected(Vector2DInt cellLocation)
{
    toVisit.clear();
    GetBoard()->GetCell(Vector2DInt{ cellLocation })->SetToImage(Images::RedX);
    if (GetBoard()->GetCell(Vector2DInt{ cellLocation.x ,cellLocation.y })->GetImage() == Images::RedX)
    {
        toVisit.push_back(cellLocation);
    }
}

bool Standard::TryToAdd(Vector2DInt cellPos)
{
    if (GetBoard()->GetCell(Vector2DInt{ cellPos.x,cellPos.y }) != nullptr)
    {
        if (GetBoard()->GetCell(Vector2DInt{ cellPos.x,cellPos.y })->GetImage() == Images::Red)//red
        {
            return false;
        }
        else if (GetBoard()->GetCell(Vector2DInt{ cellPos.x,cellPos.y })->GetImage() == Images::RedX)//x
        {
            GetBoard()->GetCell(Vector2DInt{ cellPos.x, cellPos.y })->SetToImage(Images::Red);
            return true;
        }
        else if (GetBoard()->GetCell(Vector2DInt{ cellPos.x,cellPos.y })->GetImage() == Images::None)//none
        {
            return true;
        }
        else if (GetBoard()->GetCell(Vector2DInt{ cellPos.x,cellPos.y })->GetImage() == Images::Off)//off
        {
            return false;
        }
    }
    return false;
}
