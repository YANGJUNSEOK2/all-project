
/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Board.cpp
Author: junseok.yang
Creation Date:SPRING/5/25/2019
    Header file for the BattleShip board logic for Assignment4
******************************************************************************/
#include <iostream>   // cout, endl
#include <iomanip>  // setw
#include <cassert> // assert

#include "Board.h"   //include board
#include "Point.h"   //include point
#include "Boat.h"    //include boat
#include "ShotStats.h"    //include shotstats
#include "PRNG.h"    //include rand

namespace {
    const int HIT_OFFSET = 100; //!< Add this to the boat ID
    const int EMPTY = 0;
    const int MISS = -1;
}

namespace CS170 {
    namespace BattleShip {
        Board::Board(int numBoats, int width, int height) :numBoats(numBoats), width(width), height(height)
        {

            this->grid = new int[width*height];

            this->m_shotStats.duplicates = 0;
            this->m_shotStats.hits = 0;
            this->m_shotStats.misses = 0;
            this->m_shotStats.sunk = 0;

            this->boats = new Boat*[numBoats];

            for (int i = 0; i < width*height; i++)
            {
                this->grid[i] = 0;
            }
        }
        Board::~Board()
        {

            delete boats;

            delete[] grid;

        }

        void Board::DestroyBoats()
        {
            for (int i = 0; i < this->numBoats; i++)
            {
                delete this->boats[i];
            }
        }

        // Using point, Get the value of the grid and return the correct result
        Board::ShotResult Board::TakeShot(const CS170::Utils::Point &point)
        {
            if (IsPointValid(point) == false)
            {
                return ShotResult::INVALID;
            }

            int my_grid = GetBoardValue(point);

            switch (my_grid)
            {
            case ::MISS:
                this->m_shotStats.duplicates++;
                return ShotResult::DUPLICATE;
            case ::EMPTY:
                if (::EMPTY == my_grid)
                {
                    this->m_shotStats.misses++;
                    SetBoardValue(point, ::MISS);
                    return MISS;
                }
                return ShotResult::INVALID;
            default:

                if (my_grid > ::HIT_OFFSET || my_grid == ::MISS)
                {
                    this->m_shotStats.duplicates++;
                    return ShotResult::DUPLICATE;
                }
                else
                {
                    this->grid[(this->width*point.y) + point.x] += ::HIT_OFFSET;
                    int my_ID = GetBoardValue(point) - ::HIT_OFFSET;

                    int hit = boats[my_ID - 1]->GetHitsUntilSunk();

                    boats[my_ID - 1]->SetHitsUntilSunk(hit - 1);

                    if (this->boats[my_ID - 1]->GetHitsUntilSunk() == 0)
                    {
                        this->m_shotStats.sunk++;
                        this->m_shotStats.hits++;
                        std::cout << "You sank my " << boats[my_ID - 1]->GetName() << "\n";
                        
                        return ShotResult::SUNK;
                    }
                    else
                    {
                        this->m_shotStats.hits++;
                        return ShotResult::HIT;
                    }
                }
            }
        }

        // This function should just return the grid value at the given point
        int Board::GetBoardValue(const CS170::Utils::Point &point)
        {
            assert((point.x >= 0 && point.x < this->width) && (point.y >= 0 && point.y < this->height));

            int m_grid = this->grid[(point.y*this->width) + point.x];
            return m_grid;
        }

        // This function should set the grid value at a given point
        void Board::SetBoardValue(const CS170::Utils::Point &point, int value)
        {
            assert((point.x >= 0 && point.x < this->width) && (point.y >= 0 && point.y < this->height));

            this->grid[(point.y*this->width) + point.x] = value;
        }

        // Checks if a point is outside of the grid 
        bool Board::IsPointValid(const CS170::Utils::Point &point)
        {

            if (point.x < 0 || point.x >= this->width || point.y < 0 || point.y >= this->height)
                return false;
            else
                return true;
        }

        // Checks if the given boat is a valid location
        bool Board::IsBoatPositionValid(const Boat &boat)
        {

            int m_grid = 0;
            m_grid = boat.GetBoatValue(Boat::Y_LOCATION)*this->width + boat.GetBoatValue(Boat::X_LOCATION);

            if (IsPointValid({ boat.GetBoatValue(Boat::X_LOCATION), boat.GetBoatValue(Boat::Y_LOCATION) }) != true)
            {
                return false;
            }

            if (boat.GetBoatValue(Boat::LENGTH) <= (this->width - boat.GetBoatValue(Boat::X_LOCATION)) && boat.GetBoatValue(Boat::ORIENTATION) == Boat::Orientation::HORIZONTAL)
            {
                if (this->grid[m_grid] == EMPTY)
                {
                    for (int i = 0; i < boat.GetBoatValue(Boat::LENGTH); i++)
                    {

                        if (this->grid[m_grid + i] != 0)
                        {
                            return false;
                        }


                    }
                    return true;
                }

            }
            if (boat.GetBoatValue(Boat::LENGTH) <= (this->height - boat.GetBoatValue(Boat::Y_LOCATION)) && boat.GetBoatValue(Boat::ORIENTATION) == Boat::Orientation::VERTICAL)
            {
                if (this->grid[m_grid] == EMPTY)
                {
                    for (int i = 0; i < boat.GetBoatValue(Boat::LENGTH); i++)
                    {

                        if (this->grid[m_grid + i * this->width] != EMPTY)
                        {
                            return false;
                        }
                    }
                    return true;
                }

            }
            return false;
        }

        // Add the boat to our boats array and add its values to our board
        void  Board::AddBoatToBoard(Boat &boat)
        {
            boats[boat.GetBoatValue(Boat::ID) - 1] = &boat;

            if (boat.GetBoatValue(Boat::ORIENTATION) == Boat::HORIZONTAL)
            {
                if (boat.GetBoatValue(Boat::X_LOCATION) >= 0 || boat.GetBoatValue(Boat::X_LOCATION) <= (this->width - boat.GetBoatValue(Boat::LENGTH)))
                {


                    for (int i = 0; i < boat.GetBoatValue(Boat::LENGTH); i++)
                    {

                        this->grid[(this->width*(boat.GetBoatValue(Boat::Y_LOCATION))) + boat.GetBoatValue(Boat::X_LOCATION) + i] = boat.GetBoatValue(Boat::ID);
                    }


                }
            }
            else if (boat.GetBoatValue(Boat::ORIENTATION) == Boat::VERTICAL)
            {
                if (boat.GetBoatValue(Boat::Y_LOCATION) >= 0 || boat.GetBoatValue(Boat::Y_LOCATION) <= (this->height - boat.GetBoatValue(Boat::LENGTH)))
                {


                    for (int i = 0; i < boat.GetBoatValue(Boat::LENGTH); i++)
                    {

                        this->grid[(this->width*(boat.GetBoatValue(Boat::Y_LOCATION) + i)) + (boat.GetBoatValue(Boat::X_LOCATION))] = boat.GetBoatValue(Boat::ID);
                    }
                }
            }
        }

        void Board::DrawBoard(bool showboats, int field_width) {
            // Write a row of column index
            std::cout << std::setw(field_width) << ' ';
            for (int x = 0; x < this->width; x++) {
                std::cout << std::setw(field_width) << x;
            }
            std::cout << std::endl;

            // Write seperator
            std::cout << std::setw(field_width) << ' ';
            for (int x = 0; x < this->width; x++) {
                std::cout << std::setw(field_width) << '-';
            }
            std::cout << std::endl;

            for (int y = 0; y < this->height; y++) {
                std::cout << std::setw(field_width - 1) << y << '|';   // write the row index and a seperator
                for (int x = 0; x < this->width; x++) {
                    int value = GetBoardValue(CS170::Utils::Point{ x, y });
                    // Is it a boat?
                    if ((value > 0) && (value <= HIT_OFFSET) && (showboats == false)) {
                        value = 0;
                    }
                    std::cout << std::setw(field_width) << value;
                }
                std::cout << std::endl;
            }
        }

        // Returns our shot status, how many times we fired, misses, duplicates and ships sunk
        ShotStats Board::GetShotStats() const
        {
            return m_shotStats;
        }

        int Board::GetBoard(int value) const
        {
            switch (value)
            {
            case BoardValue::DUPLICATES:
                return Board::duplicates;
                break;
            case BoardValue::HEIGHT:
                return Board::height;
                break;
            case BoardValue::NUMBOAT:
                return Board::numBoats;
                break;
            case BoardValue::SHOTSTATS_HIT:
                return Board::m_shotStats.hits;
                break;
            case BoardValue::SHOTSTATS_DUPLICATE:
                return Board::m_shotStats.duplicates;
                break;
            case BoardValue::SHOTSTATS_MISS:
                return Board::m_shotStats.misses;
                break;
            case BoardValue::SHOTSTATS_SUNK:
                return Board::m_shotStats.sunk;
                break;
            case BoardValue::WIDTH:
                return Board::width;
                break;
            default:
                return 0;
            }
        }

        void Board::SetBoard(int value, BoardValue board_value)
        {
            switch (board_value)
            {
            case BoardValue::DUPLICATES:
                Board::duplicates = value;
                break;
            case BoardValue::HEIGHT:
                Board::height = value;
                break;
            case BoardValue::WIDTH:
                Board::width = value;
                break;
            case BoardValue::NUMBOAT:
                Board::numBoats = value;
                break;
            case BoardValue::SHOTSTATS_HIT:
                  Board::m_shotStats.hits = value;
                break;
            case BoardValue::SHOTSTATS_DUPLICATE:
                Board::m_shotStats.duplicates = value;
                break;
            case BoardValue::SHOTSTATS_MISS:
                Board::m_shotStats.misses = value;
                break;
            case BoardValue::SHOTSTATS_SUNK:
                Board::m_shotStats.sunk = value;
                break;
            default:
                break;
            }
        }
    }
}


