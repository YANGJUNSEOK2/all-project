/************************************************************************
*	File name : ScreenShot.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include "ImageLoader.hpp"

class ScreenShot
{
public:
    Image capture_screenshot_of_back_buffer_to_image(int pixels_width, int pixels_height, int left_x = 0,
        int bottom_y = 0) noexcept;
private:
};