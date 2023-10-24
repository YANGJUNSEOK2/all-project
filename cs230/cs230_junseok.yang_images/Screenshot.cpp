/*
junseok.yang
assignment6
cs230
spring 2019
*/
#include <CS230/graphics/Screenshot.hpp>
#include <CS230/graphics/glCheck.hpp>
#include <GL/glew.h>

namespace CS230
{
    Image capture_screenshot_of_back_buffer_to_image(int pixels_width, int pixels_height, int left_x,
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
}
