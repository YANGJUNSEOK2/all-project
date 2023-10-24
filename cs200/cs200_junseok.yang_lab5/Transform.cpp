/*
 * junseok yang
 * Lab5 - 2D-Transform
 * CS200
 * Fall 2019
 */
#include "Transform.h" // include transform header

namespace
{
	constexpr float PI = 3.141592f;
}

Matrix WorldToRelative(const Vector& u, const Vector& v, const Point& C)
{
    Vector normal_u = Normalize(u);
    Vector normal_v = Normalize(v);
    float dot_u = Dot(normal_u, { C.x,C.y });
    float dot_v = Dot(normal_v, { C.x,C.y });
    return Matrix{ {u.x,v.x,0.f},{u.y,v.y,0.f},{-dot_u,-dot_v,1.f} };
}

Matrix RelativeToWorld(const Vector& u, const Vector& v, const Point& C)
{
	return Matrix{{u.x,u.y,0.f},{v.x,v.y,0.f},{C.x,C.y,1.f}};
}

Matrix Scale(const Vector& scale)
{
    return Matrix{ {scale.x,0.f,0.f} ,{0.f,scale.y,0.f}, {0.f,0.f,1.f} };
}

Matrix Rotate(int degree)
{
    const float radian = degree * PI / 180;
    float cosValue = static_cast<float>(cos(radian));
    float sinValue = static_cast<float>(sin(radian));
    return Matrix{ {cosValue,sinValue,0.f},
        {-sinValue,cosValue,0.f},
        {0.f,0.f,1.f} };
}

Matrix Translate(const Vector& translate)
{
	return Matrix{{1.f,0.f,0.f},{0.f,1.f,0.f},{translate.x,translate.y,1.f}};
}
