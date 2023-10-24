#pragma once
#include "ShotStats.h"

/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Boat.h
Author: Kevin Wright  kevin.wright@digipen.edu
Creation Date: Feb 24, 2019

	Header file for the BattleShip boat for Assignment 1
******************************************************************************/
namespace CS170 {
	namespace BattleShip {
        class Board;

		class Boat
		{  
		public:
            enum BoatValue { ID, ORIENTATION, LENGTH, HITS_UNTIL_SUNK, X_LOCATION, Y_LOCATION };
            enum Orientation { HORIZONTAL, VERTICAL };

            Boat() {}
            Boat(int length,int id, Utils::Point location, Orientation orientation, const char* boatName)
                : length(length),orientation(orientation), id(id), hitsUntilSunk(length), location(location),boatName(boatName)
            {}
            Boat(int length,int id, const char* boatName)
                : length(length), id(id), hitsUntilSunk(length), boatName(boatName)
            {}
            Boat(int id, Utils::Point location, Orientation orientation)
                : orientation(orientation), id(id), hitsUntilSunk(length), location(location)
            {}
            Boat(int id, Board& board)
                : id(id), hitsUntilSunk(length)
            {
                FindRandomLocation(board);
            }
            Boat(int id) :id(id), hitsUntilSunk(length)
            {}

            virtual~Boat() {};

            void FindRandomLocation(Board& board);

            Orientation GetOrientation() { return orientation; }
            void SetOrientation(Orientation orientation) { this->orientation = orientation; } 
            int GetId()const { return id; }
            void SetId(int id) { this->id = id; }
            int GetHitsUntilSunk() { return this->hitsUntilSunk; }
            void SetHitsUntilSunk(int hitsUntilSunk) { this->hitsUntilSunk = hitsUntilSunk; }
            Utils::Point GetLocation() { return location; }
            void SetLocation(Utils::Point location) { this->location = location; }
            int GetBoatValue(int value) const;
            void SetBoatValue(int value, BoatValue boat_value);

            virtual const char* GetName() const = 0;
            virtual int GetLength() const = 0;
            void SetLength(int length) { this->length = length; }

        private:

            int length;
            Orientation orientation;
            int id;
            int hitsUntilSunk;
            Utils::Point location;
            const char* boatName;
		};

        class Carrier : public Boat
        {
        public:
            Carrier(int id, Utils::Point location, Orientation orientation,const char* boatName,int length)
                : Boat(length, id, location, orientation, boatName) { }
            Carrier(int id, const char* boatName, int length)
                : Boat(length, id, boatName) { }
            const char* GetName() const override { return "Carrier";   }
            int GetLength() const override { return 5; }
        private:
        };

        class Battleship : public Boat
        {
        public:
            Battleship(int id, Utils::Point location, Orientation orientation, const char* boatName, int length)
                : Boat(length, id, location, orientation, boatName) { }
            Battleship(int id, const char* boatName, int length)
                : Boat(length, id, boatName) { }
            const char* GetName() const override { return "Battleship"; }
            int GetLength() const override { return 4; }
        private:
        };

        class Cruiser : public Boat
        {
        public:
            Cruiser(int id, Utils::Point location, Orientation orientation, const char* boatName, int length)
                : Boat(length, id, location, orientation, boatName) { }
            Cruiser(int id, const char* boatName, int length)
                : Boat(length, id, boatName) { }
            const char* GetName() const override { return "Cruiser"; }
            int GetLength() const override { return 3; }
        private:
        };

        class Submarine : public Boat
        {
        public:
            Submarine(int id, Utils::Point location, Orientation orientation, const char* boatName, int length)
                : Boat(length, id, location, orientation, boatName) { }
            Submarine(int id, const char* boatName, int length)
                : Boat(length, id, boatName) { }
            const char* GetName() const override { return "Submarine"; }
            int GetLength() const override { return 3; }
        private:
        };
        
        class Destroyer : public Boat
        {
        public:
            Destroyer(int id, Utils::Point location, Orientation orientation, const char* boatName, int length)
                : Boat(length, id, location, orientation, boatName) { }
            Destroyer(int id, const char* boatName, int length)
                : Boat(length, id, boatName) { }
            const char* GetName() const override { return "Destroyer"; }
            int GetLength() const override { return 2; }
        private:
        };
	}
}
