/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author:junseok.yang
Creation Date:Spring 2019.3.25
cs170 lab3
******************************************************************************/
#include"WriteData.h"
 
#include <iomanip>

namespace CS170
{
    namespace Lap2
    {
        const int column1Width = 2;

        void WriteColumn(char value, int width)
        {
            //fill char
            std::cout << std::setw(width) << value;
        }

        void  WriteColumn(std::string value, int width)
        {
            std::cout << std::setw(width) << value;
        }

        void WriteColumn(int value, int width)
        {
            std::cout << std::setw(width) << value;
        }

        void WriteColumn(double value, int width)
        {
             std::cout<<std::setw(width) <<std::fixed<<std::setprecision(15)<< value;
        }
    }
}