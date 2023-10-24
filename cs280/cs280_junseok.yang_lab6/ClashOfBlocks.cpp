/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ClashOfBlocks.cpp
Purpose: Source file for ClashOfBlocks
Project: CS280
Author: junseok.yang
Creation date: 4/28/2021
-----------------------------------------------------------------*/
#include "ClashOfBlocks.h"
#include "Cell.h"
#include "Image_Anims.h"

bool ClashOfBlocks::Visit()
{
    int visit_step = toVisit.begin()->step;

    if (visit_step == 0)
    {
        for (; visit_step == toVisit.begin()->step; )
        {
            toVisit.begin()->step += 2;
            board->GetCell(toVisit.begin()->cellPos)->SetToImage(static_cast<Images>(static_cast<int>(board->GetCell(toVisit.begin()->cellPos)->GetImage()) - 1));
            toVisit.push_back(*toVisit.begin());
            toVisit.pop_front();

            if (toVisit.empty() == true)
                return true;
        }
    }
    else if (visit_step == 1)
    {
        for (; visit_step == toVisit.begin()->step; )
        {
            toVisit.begin()->step += 2;
            board->GetCell(toVisit.begin()->cellPos)->SetToImage(static_cast<Images>(static_cast<int>(board->GetCell(toVisit.begin()->cellPos)->GetImage()) - 1));
            toVisit.push_back(*toVisit.begin());
            toVisit.pop_front();

            if (toVisit.empty() == true)
                return true;
        }
    }
    else if (visit_step != 0 || visit_step != 1)
    {
        for (; visit_step == toVisit.begin()->step; )
        {
            ToVisit Up = *toVisit.begin();
            Up.cellPos = { Up.cellPos.x,  Up.cellPos.y + 1 };
            Up.step += 2;

            ToVisit Right = *toVisit.begin();
            Right.cellPos = { Right.cellPos.x + 1,  Right.cellPos.y };
            Right.step += 2;

            ToVisit Down = *toVisit.begin();
            Down.cellPos = { Down.cellPos.x,  Down.cellPos.y - 1 };
            Down.step += 2;

            ToVisit Left = *toVisit.begin();
            Left.cellPos = { Left.cellPos.x - 1,  Left.cellPos.y };
            Left.step += 2;

            TryToAdd(Up);
            TryToAdd(Right);
            TryToAdd(Down);
            TryToAdd(Left);

            toVisit.pop_front();

            if (toVisit.empty() == true)
                return true;
        }
    }
    if (toVisit.empty() == true)
        return true;

    return false;
}

void ClashOfBlocks::PlayerSelected(Vector2DInt cellLocation)
{
    ToVisit player_pos;
    ToVisit ai_pos;

    player_pos.cellPos = cellLocation;
    player_pos.step = 0;
    player_pos.imageToUse = Images::RedX;
    board->GetCell(cellLocation)->SetToImage(Images::RedX);
    toVisit.push_back(player_pos);

    for (auto ai_CellPos : board->GetAIStartSpots())
    {
        ai_pos.cellPos = ai_CellPos;
        ai_pos.step = 1;
        ai_pos.imageToUse = static_cast<Images>(static_cast<int>(board->GetCell(ai_pos.cellPos)->GetImage()) - 1);
        toVisit.push_back(ai_pos);
    }
}

bool ClashOfBlocks::TryToAdd(ToVisit tryToAdd)
{
    if (GetBoard()->GetCell({ tryToAdd.cellPos.x,tryToAdd.cellPos.y }) != nullptr && GetBoard()->GetCell({ tryToAdd.cellPos.x,tryToAdd.cellPos.y })->GetImage() == Images::None)
    {
        if (tryToAdd.imageToUse == Images::Red)//red
        {
            return false;
        }
        else if (tryToAdd.imageToUse == Images::RedX)//x
        {
            GetBoard()->GetCell({ tryToAdd.cellPos.x,tryToAdd.cellPos.y })->SetToImage(Images::Red);
            toVisit.push_back(tryToAdd);
            return true;
        }

        else if (tryToAdd.imageToUse == Images::Blue)//blue
        {
            GetBoard()->GetCell({ tryToAdd.cellPos.x,tryToAdd.cellPos.y })->SetToImage(Images::Blue);
            toVisit.push_back(tryToAdd);
            return true;
        }

        else if (tryToAdd.imageToUse == Images::Green)//green
        {
            GetBoard()->GetCell({ tryToAdd.cellPos.x,tryToAdd.cellPos.y })->SetToImage(Images::Green);
            toVisit.push_back(tryToAdd);
            return true;
        }
        else if (tryToAdd.imageToUse == Images::None)//none
        {
            return true;
        }
        else if (tryToAdd.imageToUse == Images::Off)//off
        {
            return false;
        }
    }
    return false;
}