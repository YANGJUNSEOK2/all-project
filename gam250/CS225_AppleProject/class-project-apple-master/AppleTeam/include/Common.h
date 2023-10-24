/************************************************************************
*	File name : Common.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description :
*   Sets of Information that used in other files(The informations are read in at least two different files)
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include <string>

namespace CellInfo
{
    enum class Type
    {
        NORMAL = 0,
        NOTHING,
        RED,
        RED_X,
        BLUE,
        BLUE_X,
        GREEN,
        GREEN_X,
        COUNT,
    };
    constexpr int CELLSIZE = 64;
}
namespace TriominoInfo
{
    enum class Type
    {
        LEFTUP,
        LEFTDOWN,
        RIGHTUP,
        RIGHTDOWN,
        HORIZONTAL,
        VERTICAL,
    };
}
namespace WindowInfo
{
    constexpr int WIDTH = 1280;
    constexpr int HEIGHT = 640;
    
};

namespace Imgpath
{
    const std::string SPLASH = "assets/DigiPen_BLACK_1024px.png";
    const std::string CELL = "assets/Images.png";
}

namespace PlayerInfo
{
    enum class Color
    {
        BLUE,
        RED,
        GREEN,
        COUNT,
    };
    constexpr int PlayerNum = 2;
}