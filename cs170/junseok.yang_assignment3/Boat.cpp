/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Boat.cpp
Author:junseok.yang
Creation Date:Spring/5/08/2019
    Header file for the BattleShip boat logic for Assignment 3
******************************************************************************/
#include "Point.h"    //include point
#include "Boat.h"     //include boat
#include "Board.h"    //include board
#include "PRNG.h"     //include rand

namespace CS170 {
    namespace BattleShip {

        void Boat::FindRandomLocation(Board& board)
        {
            do
            {
                int x = Utils::Random(0, /*board.width*/board.GetBoard(Board::WIDTH) - 1);
                this->location.x = x;
                int y = Utils::Random(0, board.GetBoard(Board::HEIGHT) - 1);
                this->location.y = y;
                this->orientation = static_cast<Orientation>(Utils::Random(0, 1));

            } while (!board.IsBoatPositionValid(*this));
        }
        
        int Boat::GetBoatValue(int value) const
        {
            switch (value)
            {
            case BoatValue::ID:
                return Boat::id;
                break;
            case BoatValue::LENGTH:
                return Boat::length;
                break;
            case BoatValue::ORIENTATION:
                return Boat::orientation;
                break;
            case BoatValue::HITS_UNTIL_SUNK:
                return Boat::hitsUntilSunk;
                break;
            case BoatValue::X_LOCATION:
                return Boat::location.x;
                break;
            case BoatValue::Y_LOCATION:
                return Boat::location.y;
                break;
            default:
                return 0;
                break;
            }
        }

        void Boat::SetBoatValue(const int value, BoatValue boat_value)
        {
            switch (boat_value)
            {
            case BoatValue::ID:
                Boat::id = value;
                break;
            case BoatValue::LENGTH:
                break;
            case BoatValue::ORIENTATION:
                if (value == HORIZONTAL)
                {
                    orientation = HORIZONTAL;

                }
                else if (value == VERTICAL)
                {
                    orientation = VERTICAL;
                }
                break;
            case BoatValue::HITS_UNTIL_SUNK:
                Boat::hitsUntilSunk = value;
                break;
            case BoatValue::X_LOCATION:
                Boat::location.x = value;
                break;
            case BoatValue::Y_LOCATION:
                Boat::location.y = value;
                break;
            default:
                break;
            }
        }

    }
}