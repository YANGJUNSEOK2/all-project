#pragma once

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
		struct Board;

		enum Orientation { HORIZONTAL, VERTICAL };

		struct Boat {
			const int length = 4;
			Orientation orientation;
			int id;
			int hitsUntilSunk;
			Utils::Point location;
		};
		
		// This will set the various values of Boat.  
		void InitBoatAndPlace(Boat &boat, Utils::Point location, Orientation orientation);
		//This will Create use the random number generator to init a boat position & orientation. 
		//If that position and orientation are not valid, it will get a new random position & orientation
		void InitRandomLocation(Boat &boat, int id, Board &board);
	}
}
