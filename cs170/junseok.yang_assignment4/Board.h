#pragma once

/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Board.h
Author: junseok.yang
Creation Date: sping/5/25

	Header file for the BattleShip board logic for Assignment 4
******************************************************************************/
#include "ShotStats.h"    //include shotstats
#include "Point.h"        //inlclude point

#include <fstream>

namespace CS170 {
    namespace BattleShip {

        class Boat;

        //int count_Boat = 0;

        class Board
        { 
        public:
            enum BoardValue { NUMBOAT, WIDTH, HEIGHT, DUPLICATES, 
                SHOTRESULT ,SHOTSTATS_HIT, SHOTSTATS_MISS, SHOTSTATS_DUPLICATE,
                SHOTSTATS_SUNK, SHOTSTATS_INVALID};
            enum ShotResult { HIT, MISS, DUPLICATE, SUNK, INVALID };

            //ShotResult shotResult;

            // This should allocate a new Board struct and the values within it
           /* Board *CreateBoard(int numBoats, int width, int height);*/
            Board(int numBoats, int width, int height);
            // This should free any allocated data within the board
            ~Board();
            // If our boats were dynamically allocated, This should free them
            void DestroyBoats();
            // Using point, Get the value of the grid and return the correct result
            ShotResult TakeShot(const CS170::Utils::Point &point);
            // This function should just return the grid value at the given point
            int GetBoardValue(const CS170::Utils::Point &point);
            // This function should set the grid value at a given point
            void SetBoardValue(const CS170::Utils::Point &point, int value);
            // Checks if a point is outside of the grid 
            bool IsPointValid(const CS170::Utils::Point &point);
            // Checks if the given boat is a valid location
            bool IsBoatPositionValid(const Boat &boat);
            // Add the boat to our boats array and add its values to our board
            void AddBoatToBoard(Boat &boat);
            // Disaplys the board, this is already done for you 
            void DrawBoard(bool showboats = false, int field_width = 4);
            // Returns our shot status, how many times we fired, misses, duplicates and ships sunk
            ShotStats GetShotStats() const;

            void SetShotStats(ShotStats m_shotStats) { this->m_shotStats = m_shotStats; }

            Boat** GetBoats() const { return boats; }

            int GetBoard(int value) const;
           
            void SetBoard(int value, BoardValue board_value);

        private:
            // Board *m_Board;
            int *grid;			    // This is your 2D array which stores the values of our board (hit, miss, boat..)
            Boat **boats;		    // Array of boat pts
            int numBoats;		    // number of boats in the array boats
            int width;			    // width of our grid
            int height;			    // height of our grid
            int duplicates;		    // number of duplicates (how many times we picked the same grid position)
            ShotStats m_shotStats;  // make m_shotState
        };
    
	}
}
