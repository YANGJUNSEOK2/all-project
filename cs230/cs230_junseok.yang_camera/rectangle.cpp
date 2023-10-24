/*
junseok.yang
assignment5
cs230
spring 2019
*/
#include <CS230/math/rectangle.hpp>
#include <cmath>

namespace CS230
{
    void rectangle::ExtendBy(vector2 point) noexcept
    {
        if (point.x < min.x)
        {
            min.x = point.x;
        }
        if (point.y < min.y)
        {
            min.y = point.y;
        }
        if (point.x > max.x)
        {
            max.x = point.x;
        }
        if (point.y > max.y)
        {
            max.y = point.y;
        }
    }

    bool rectangle::DoesContainPoint(vector2 point) const noexcept
    {
        if (point.x <= max.x&&point.x >= min.x)
        {
            if (point.y <= max.y&&point.y >= min.y)
            {
                return true;
            }
            return false;
        }
        return false;
    }

    bool rectangle::DoesIntersectWith(rectangle other) const noexcept
    {
        if(DoesContainPoint(other.min) || DoesContainPoint(other.max))
        {
            return true;
        }
        return false;
    }

    vector2 rectangle::CalculateCenter() const noexcept
    {
        float centerX = (min.x + max.x) / 2;
        float centerY = (min.y + max.y) / 2;
        
        return { centerX,centerY };
    }

    float   rectangle::CalculateWidth() const noexcept
    {
        return (max).x - (min).x;
    }

    float rectangle::CalculateHeight() const noexcept
    {
        return (max).y - (min).y;
    }
}
