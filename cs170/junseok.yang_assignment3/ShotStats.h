#pragma once

/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Boat.h
Author: Kevin Wright  kevin.wright@digipen.edu
Creation Date: May 8, 2019

	Header file for the BattleShip ShotStats for Assignment 3
******************************************************************************/
namespace CS170 {
	namespace BattleShip {
		struct ShotStats 
	    {
			int hits;       //!< The number of boat hits
			int misses;     //!< The number of boat misses
			int duplicates; //!< The number of duplicate (misses/hits)
			int sunk;       //!< The number of boats sunk
        };
	}
}
