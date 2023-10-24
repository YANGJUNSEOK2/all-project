
/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Boat.cpp
Author:junseok.yang
Creation Date:Spring/3/30/2019
	Header file for the BattleShip boat logic for Assignment 1
******************************************************************************/
#include "Point.h"
#include "Boat.h"
#include "Board.h"
#include "PRNG.h"

namespace CS170 {
	namespace BattleShip {
        void InitBoatAndPlace(Boat& boat, Utils::Point location, Orientation orientation)
        {
            boat.location.x = location.x;
            boat.location.y = location.y;
            boat.orientation = orientation;
        }

        void InitRandomLocation(Boat& boat, int id, Board& board)
        {
            boat.id = id;

            boat.hitsUntilSunk = 4;

            do
            {

                int x = Utils::Random(0, board.width - 1);
                boat.location.x = x;
                int y = Utils::Random(0, board.height - 1);
                boat.location.y = y;
                boat.orientation = static_cast<Orientation>(Utils::Random(0, 1));

            } while (!IsBoatPositionValid(board, boat));

        }
    }
} 

