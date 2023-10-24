/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author:junseok.yang
Creation Date:Spring 2019.3.25
cs170 lab3
******************************************************************************/
#pragma once

#include <iostream>
#include <string>
//The char version of WriteColumn should use that character as a fill character
namespace CS170
{
    namespace Lap2
    {
        extern const int column1Width;


        void WriteColumn(char value, int width = 20);
        void  WriteColumn(std::string value, int width = 20);;
        void WriteColumn(int value, int width = 20);
        void WriteColumn(double value, int width = 20);
    }
}


