#pragma once

/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   PRNG.h
Author:junseok.yang
Creation Date:spring/5/8

	Header for the pseudo random number generator
******************************************************************************/
namespace CS170 {
	namespace Utils {
		unsigned rand(void);              // returns a random 32-bit integer
		void srand(unsigned, unsigned);   // seed the generator
		int Random(int low, int high);    // range
   	}
}

