/************************************************************************
*	File name : ScreenShot.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "ScreenShot.hpp"
#include "../Shader/glCheck/glCheck.hpp"
#include <glew.h>

Image ScreenShot::capture_screenshot_of_back_buffer_to_image(int pixels_width, int pixels_height, int left_x,
    int bottom_y) noexcept
{
    Image screenShot;
    screenShot.ResizeToPixelWidthHeight(pixels_width, pixels_height);
    glCheck(glReadBuffer(GL_BACK_LEFT));
    if (glReadnPixels != nullptr)
    {
        glCheck(glReadnPixels(left_x, bottom_y, pixels_width, pixels_height, GL_RGBA, GL_UNSIGNED_BYTE, screenShot.GetPixelsBufferBytesSize(), screenShot.GetPixelsPointer()));
    }
    else
    {
        glCheck(glReadPixels(left_x, bottom_y, pixels_width, pixels_height, GL_RGBA, GL_UNSIGNED_BYTE, screenShot.GetPixelsPointer()));
    }
    screenShot.FlipVertically();
    return screenShot;
}
