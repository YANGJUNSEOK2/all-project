/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AStar.cpp
Purpose: AStar logic for assignment 5
Project: AStar (CS280 Programming Final)
Author: junseok yang
Creation date: 2021 06 01
-----------------------------------------------------------------*/

#include "AStar.h"


#include <set>
#include <stack>

#include "Image_Anims.h"
#include "Cell.h"


void AStar::MakeBoard(std::string levelData) {
    board = new Board();	// Create the board class
    board->Load(levelData);	// load the data file and initialize the 2D array
    // Find the target cell (the other end of our search path)
    for (int x = 0; x < board->GetSize().x; x++) {
        for (int y = 0; y < board->GetSize().y; y++) {
            if (board->GetCell({ x,y })->GetImage() == Images::RedX)
            {
                beginSearch = board->GetCell({ x,y });
            }
        }
    }
}

void AStar::PlayerSelected(Vector2DInt cellLocation) {
    selected = board->GetCell(cellLocation);
    selected->SetToImage(Images::BlueX);
    beginSearch->CalculateAstarVariables(nullptr, selected, &toVisit);
    toVisit.Push(beginSearch);
}

bool AStar::Visit() {
    if (toVisit.IsEmpty() == true) //check list is empty
    {
        return true;
    }

    Cell* currCell = toVisit.Pop();
    currCell->SetToImage(Images::Green);

    if (currCell == selected)
    {
        Cell* curr = currCell;
        while (curr != nullptr)
        {
            curr->SetToImage(Images::Blue);
            curr = curr->GetPnext();
        }
        return true;
    }

    Vector2DInt locations[8];
    locations[0] = { currCell->GetXYIndex().x + 1, currCell->GetXYIndex().y + 1 };
    locations[1] = { currCell->GetXYIndex().x + 1, currCell->GetXYIndex().y };
    locations[2] = { currCell->GetXYIndex().x + 1, currCell->GetXYIndex().y - 1 };
    locations[3] = { currCell->GetXYIndex().x, currCell->GetXYIndex().y - 1 };
    locations[4] = { currCell->GetXYIndex().x - 1, currCell->GetXYIndex().y - 1 };
    locations[5] = { currCell->GetXYIndex().x - 1, currCell->GetXYIndex().y };
    locations[6] = { currCell->GetXYIndex().x - 1, currCell->GetXYIndex().y + 1 };
    locations[7] = { currCell->GetXYIndex().x, currCell->GetXYIndex().y + 1 };

    for (int i = 0; i < 8; i++)
    {
        if (board->GetCell(locations[i]) != nullptr) //check cell is in board
        {
            if (board->GetCell(locations[i])->GetImage() == Images::None || board->GetCell(locations[i])->GetImage() == Images::BlueX)
            {
                if (board->GetCell(locations[i])->GetFCost() == static_cast<unsigned int>(-1))
                {
                    board->GetCell(locations[i])->CalculateAstarVariables(currCell, selected, &toVisit);
                    toVisit.Push(board->GetCell(locations[i]));
                    board->GetCell(locations[i])->SetPnext(currCell);
                }
                board->GetCell(locations[i])->CalculateAstarVariables(currCell, selected, &toVisit);
                if (toVisit.found(board->GetCell(locations[i])) != true)
                {
                    board->GetCell(locations[i])->SetPnext(currCell);
                }
            }
        }
    }

    return false;
}

bool AStar::Compare(Cell* const& cellA, Cell* const& cellB)
{
    if (cellA != nullptr && cellB != nullptr)
    {
        if (cellA->GetFCost() < cellB->GetFCost())
        {
            return true;
        }
        if (cellA->GetFCost() == cellB->GetFCost())
        {
            if (cellA->GetHCost() < cellB->GetHCost())
            {
                return true;
            }
        }
    }
    return false;
}

void AStar::Unload() {
    delete board;
    while (toVisit.IsEmpty() == false) {
        toVisit.Pop();
    }
    beginSearch = nullptr;
    selected = nullptr;

    Level::Unload();
}