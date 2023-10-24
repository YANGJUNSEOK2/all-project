
/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Board.cpp
Author: junseok.yang
Creation Date:SPRING/3/30/2019
    Header file for the BattleShip board logic for Assignment 1
******************************************************************************/
#include <iostream>   // cout, endl
#include <iomanip>  // setw
#include <cassert> // assert

#include "Board.h"
#include "Point.h"
#include "Boat.h"
#include "ShotStats.h"
#include "PRNG.h"

namespace {
    const int HIT_OFFSET = 100; //!< Add this to the boat ID
    const int EMPTY = 0;
    const int MISS = -1;
}

namespace CS170 {
    namespace BattleShip {

        Board *CreateBoard(int numBoats, int width, int height)
        {
            Board *m_Board = new Board;

            m_Board->width = width;
            m_Board->height = height;
            m_Board->grid = new int[width*height];

            m_Board->numBoats = numBoats;
            m_Board->boats = new Boat*[numBoats];

            m_Board->m_shotStats.duplicates = 0;
            m_Board->m_shotStats.hits = 0;
            m_Board->m_shotStats.misses = 0;
            m_Board->m_shotStats.sunk = 0;

            for (int i = 0; i < width*height; i++)
            {
                m_Board->grid[i] = 0;
            }
           
            
            return m_Board;
        }

        // This should free any allocated data within the board
        void DestroyBoard(Board *board)
        {
            delete board->boats;
            
            delete board->grid;

            delete board;
        }

        // If our boats were dynamically allocated, This should free them
        void DestroyBoats(Board &board)
        {
            for (int i = 0; i < board.numBoats; i++)
            {
                delete board.boats[i];
            }
        }

        // Using point, Get the value of the grid and return the correct result
        ShotResult TakeShot(Board &board, const CS170::Utils::Point &point)
        {
            if (point.x < 0 || point.x >= board.width || point.y < 0 || point.y >= board.height)
                return ShotResult::INVALID;

            int m_grid = board.grid[(point.y*board.width) + point.x];

            switch (m_grid) 
            {
            case ::MISS:
                board.m_shotStats.duplicates++;
                return ShotResult::DUPLICATE;
            case ::EMPTY:
                if(::EMPTY==m_grid)
                {
                    board.m_shotStats.misses++;
                    board.grid[(point.y*board.width) + point.x] = ::MISS;
                    return MISS;
                }
                return ShotResult::INVALID;
            default:
                
                if (m_grid > ::HIT_OFFSET || m_grid == ::MISS) 
                {
                    board.m_shotStats.duplicates++;
                    return ShotResult::DUPLICATE;
                }
                else 
                {
                    board.grid[(board.width*point.y) + point.x] += ::HIT_OFFSET;
                    int m_ID = board.grid[(board.width*point.y) + point.x] - ::HIT_OFFSET;
                    board.boats[m_ID-1]->hitsUntilSunk--;
                    if (board.boats[m_ID-1]->hitsUntilSunk == 0)
                    {
                        board.m_shotStats.sunk++;
                        board.m_shotStats.hits++;
                        return ShotResult::SUNK;
                    }
                    else
                    {
                        board.m_shotStats.hits++;
                        return ShotResult::HIT;
                    }
                }
            }
        }

        // This function should just return the grid value at the given point
        int GetBoardValue(const Board &board, const CS170::Utils::Point &point)
        {
            assert((point.x >= 0 && point.x < board.width) && (point.y >= 0 && point.y < board.height));

            int m_grid = board.grid[(point.y*board.width) + point.x];
            return m_grid;
        }

        // This function should set the grid value at a given point
        void SetBoardValue(Board &board, const CS170::Utils::Point &point, int value)
        {
            assert((point.x >= 0 && point.x < board.width) && (point.y >= 0 && point.y < board.height));

            board.grid[(point.y*board.width) + point.x] = value;
        }

        // Checks if a point is outside of the grid 
        bool IsPointValid(const Board &board, const CS170::Utils::Point &point)
        {

            if (point.x < 0 || point.x >= board.width || point.y < 0 || point.y >= board.height)
                return false;
            else 
                return true;
        }

        // Checks if the given boat is a valid location
        bool IsBoatPositionValid(const Board &board, const Boat &boat)
        {
            
            int m_grid = 0;
            m_grid= boat.location.y*board.width + boat.location.x;

            if (!IsPointValid(board, boat.location))
            {
                return false;
            }

            if(boat.length<=(board.width-boat.location.x)&&boat.orientation==HORIZONTAL)
            {
                if (board.grid[m_grid] == EMPTY)
                {
                    for (int i = 0; i < boat.length; i++)
                    {

                        if (board.grid[m_grid + i] != 0)
                        {
                            return false;
                        }


                    }
                    return true;
                }
                
            }
            if(boat.length <= (board.height - boat.location.y) && boat.orientation == VERTICAL)
            {
                if (board.grid[m_grid] == EMPTY)
                {
                    for (int i = 0; i < boat.length; i++)
                    {

                        if (board.grid[m_grid + i*board.width] != EMPTY)
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
        void AddBoatToBoard(Board &board, Boat &boat)
        {
            board.boats[boat.id - 1] = &boat;

            if (boat.orientation == HORIZONTAL)
            {
                if (boat.location.x >= 0 || boat.location.x <=(board.width - boat.length))
                {


                    for (int i = 0; i < boat.length; i++)
                    {

                        board.grid[(board.width*(boat.location.y)) + boat.location.x + i] = boat.id;
                    }


                }
            }
            else if (boat.orientation == VERTICAL)
            {
                if (boat.location.y >= 0 || boat.location.y <=(board.height - boat.length))
                {


                    for (int i = 0; i < boat.length; i++)
                    {

                        board.grid[(board.width*(boat.location.y + i)) + (boat.location.x)] = boat.id;
                    }


                }
            }
        }

        void DrawBoard(const Board &board, bool showboats, int field_width) {
            // Write a row of column index
            std::cout << std::setw(field_width) << ' ';
            for (int x = 0; x < board.width; x++) {
                std::cout << std::setw(field_width) << x;
            }
            std::cout << std::endl;

            // Write seperator
            std::cout << std::setw(field_width) << ' ';
            for (int x = 0; x < board.width; x++) {
                std::cout << std::setw(field_width) << '-';
            }
            std::cout << std::endl;

            for (int y = 0; y < board.height; y++) {
                std::cout << std::setw(field_width - 1) << y << '|';   // write the row index and a seperator
                for (int x = 0; x < board.width; x++) {
                    int value = GetBoardValue(board, CS170::Utils::Point{ x, y });
                    // Is it a boat?
                    if ((value > 0) && (value < HIT_OFFSET) && (showboats == false)) {
                        value = 0;
                    }
                    std::cout << std::setw(field_width) << value;
                }
                std::cout << std::endl;
            }
        }
        
        // Returns our shot status, how many times we fired, misses, duplicates and ships sunk
        ShotStats GetShotStats(const Board &board)
        {
            return board.m_shotStats;
        }
    }
}


