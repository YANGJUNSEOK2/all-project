/*
junseok.yang
assignment3
cs230
spring 2019
*/

#include <CS230/graphics/Color4f.hpp>
#include <CS230/graphics/Color4ub.hpp>

namespace CS230
{
    Color4f::Color4f(float grey, float alpha) noexcept : red(grey), green(grey), blue(grey), alpha(alpha) {};
    Color4f::Color4f(float red, float green, float blue, float alpha) noexcept
        :red(red), green(green), blue(blue), alpha(alpha)
    { };
    Color4f to_color4f(const Color4ub& eight_bit_color)
    {
        Color4f change_Float;
        
        change_Float.red = static_cast<float>(eight_bit_color.red) / 255.0f;
        change_Float.blue = static_cast<float>(eight_bit_color.blue) / 255.0f;
        change_Float.green = static_cast<float>(eight_bit_color.green) / 255.0f;
        change_Float.alpha = static_cast<float>(eight_bit_color.alpha)/ 255.0f;
        return change_Float;
        
    }
   
    Color4ub::Color4ub(unsigned_byte grey, unsigned_byte alpha) noexcept
        :red(grey), green(grey), blue(grey), alpha(alpha)
    { };
    Color4ub::Color4ub(unsigned_byte red, unsigned_byte green, unsigned_byte blue, unsigned_byte alpha) noexcept
        :red(red),green(green),blue(blue),alpha(alpha)
    { }
    Color4ub to_color4ub(const Color4f& float_colors)
    {
        Color4ub change_Unsigned;
        if(float_colors.red<0.0f)
        {
            change_Unsigned.red = static_cast<unsigned char>(float_colors.red) * 255*0;
        }
        else if(float_colors.red>1.0f)
        {
            change_Unsigned.red = static_cast<unsigned char>(float_colors.red) * 255*1;
        }
        if(float_colors.blue<0.0f)
        {
            change_Unsigned.blue = static_cast<unsigned char>(float_colors.blue) * 255*0;
        }
        else if(float_colors.blue>1.0f)
        {
            change_Unsigned.blue = static_cast<unsigned char>(float_colors.blue) * 255*1;
        }
        if(float_colors.green<0.0f)
        {
            change_Unsigned.green = static_cast<unsigned char>(float_colors.green) * 255*0;
        }
        else if(float_colors.green>1.0f)
        {
            change_Unsigned.green = static_cast<unsigned char>(float_colors.green) * 255*1;
        }
        if (float_colors.alpha < 0.0f)
        {
            change_Unsigned.alpha = static_cast<unsigned char>(float_colors.alpha) * 255*0;
        }
        else if (float_colors.alpha > 1.0f)
        {
            change_Unsigned.alpha = static_cast<unsigned char>(float_colors.alpha) *255*1;
        }
        change_Unsigned.red = static_cast<unsigned char>(float_colors.red) * 255;
        change_Unsigned.blue = static_cast<unsigned char>(float_colors.blue) * 255;
        change_Unsigned.green = static_cast<unsigned char>(float_colors.green) * 255;
        change_Unsigned.alpha = static_cast<unsigned char>(float_colors.alpha) * 255;
        return change_Unsigned;
    }
}
