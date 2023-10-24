/************************************************************************
*	File name : mainTest.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#define CATCH_CONFIG_MAIN
#pragma warning(push)
#pragma warning(disable: 4005)

#include <cmath>
#include "Matrix3.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "catch.hpp"

TEST_CASE("vector2 test")
{
    Vector2<float> a = 2.0f;
    Vector2<float> b = { 4.0f,4.0f };
    REQUIRE((a + b == Vector2<float>(6.0f)));
    REQUIRE((a - b == Vector2<float>(-2.f)));
    REQUIRE((a * b == Vector2<float>(8)));
    REQUIRE((a / b == Vector2<float>(0.5)));
}

TEST_CASE("vector2 test2") 
{
    Vector2<float>a = 2.0f;
    Vector2<float>b = a * 2.0f; // 4.0f
    Vector2<float>c = 2.0f * a;
    Vector2<float>d = { 1.0f,2.0f };
    REQUIRE((b == c));
    REQUIRE((a / 2.0f == Vector2<float>(1.0f)));
    REQUIRE((dot(a, b) == 16.f));
    REQUIRE((perpendicular(d) == Vector2<float>{-2.0f, 1.0f}));
    REQUIRE((magnitude_Squared(a) == dot(a, a)));
    REQUIRE((magnitude(a) == std::sqrt(magnitude_Squared(a))));
    REQUIRE((normalize(a) == (a / magnitude(a))));
    REQUIRE((distance_Between_Squared(a, b) == magnitude_Squared(a - b)));
    REQUIRE((distance_Between(a, b) == std::sqrt(distance_Between_Squared(a, b))));
    REQUIRE((angle_Between(a, d) == std::acos(dot(a, d) / (magnitude(a) * magnitude(d)))));
    REQUIRE((rotate_By(2.0f, d) == Vector2<float>(std::cos(2.0f) * d.x - std::sin(2.0f) * d.y, std::sin(2.0f) * d.x + std::cos(2.0f) * d.y)));
}
  
TEST_CASE("vector3 test")
{
    Vector3<float> a = 2.0f;
    Vector3<float> b = 4.0f;
    REQUIRE((a + b == Vector3<float>(6.0f)));
    REQUIRE((a - b == Vector3<float>(-2.f)));
    REQUIRE((a * b == Vector3<float>(8)));
    REQUIRE((a / b == Vector3<float>(0.5)));
}

TEST_CASE("vector3 test2")
{
    Vector3<float>a = 2.0f;
    Vector3<float>b = { 4.0f, 4.0f,4.0f};
    Vector3<float>d = { 1.0f,2.0f,3.0f };
    REQUIRE((dot(a, b) == 24.0f));
    REQUIRE((cross(a, d) == Vector3<float>{2.0f, -4.0f, 2.0f}));
    REQUIRE((magnitude_Squared(a) == dot(a, a)));
    REQUIRE((magnitude(a) == std::sqrt(magnitude_Squared(a))));
    REQUIRE((distance_Between_Squared(a, b) == magnitude_Squared(a - b)));
    REQUIRE((distance_Between(a, b) == std::sqrt(distance_Between_Squared(a, b))));
    REQUIRE((angle_Between(a, d) == std::acos(dot(a, d) / (magnitude(a) * magnitude(d)))));
}

TEST_CASE("vector4 test")
{
    Vector4<float> a = 2.0f;
    Vector4<float> b = { 4.0f, 4.0f,4.0f,4.0f };
    Vector4<float> c = a * 2.0f; // 4.0f
    Vector4<float> d = 2.0f * a;
    REQUIRE((c == d));
    REQUIRE((a + b == Vector4<float>(6.0f)));
    REQUIRE((a - b == Vector4<float>(-2.f)));
    REQUIRE((a * b == Vector4<float>(8)));
    REQUIRE((a / b == Vector4<float>(0.5)));
}

TEST_CASE("Matrix3 test")
{
    Matrix3<float> column = { {1.0f},{2.0f},{3.0f} };
    Matrix3<float> column_row = { 1.0f,2.0f,3.0f,1.0f,2.0f,3.0f,1.0f,2.0f,3.0f };
    Matrix3<float> digonal = 4.0f;
    Matrix3<float> result;
    Vector3<float> vec = 2.0f;
    Vector2<float> vecScale = { 2.0f,1.0f };
    Vector3<float> vecRe;
    float scale = 2.0f;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.Elements[j][i] = column.Elements[0][i] * column_row.Elements[j][0]
                + column.Elements[1][i] * column_row.Elements[j][1]
                + column.Elements[2][i] * column_row.Elements[j][2];

            REQUIRE(((column * column_row).Elements[j][i] == result.Elements[j][i]));
        }
    }

    REQUIRE((build_rotation<float>(scale).Column[0].x == cos(scale)));
    REQUIRE((build_rotation<float>(scale).Column[1].x == -sin(scale)));
    REQUIRE((build_rotation<float>(scale).Column[2].x == 0.0f));
    REQUIRE((build_rotation<float>(scale).Column[0].y == sin(scale)));
    REQUIRE((build_rotation<float>(scale).Column[1].y == cos(scale)));
    REQUIRE((build_rotation<float>(scale).Column[2].y == 0.0f));
    REQUIRE((build_rotation<float>(scale).Column[0].z == 0.0f));
    REQUIRE((build_rotation<float>(scale).Column[1].z == 0.0f));
    REQUIRE((build_rotation<float>(scale).Column[2].z == 1.0f));

    REQUIRE((build_identity<float>().Column[0].x == 1.0f));
    REQUIRE((build_identity<float>().Column[1].y == 1.0f));
    REQUIRE((build_identity<float>().Column[2].z == 1.0f));

    REQUIRE((build_scale<float>(vecScale.x, vecScale.y).Column[0].x == vecScale.x));
    REQUIRE((build_scale<float>(vecScale.x, vecScale.y).Column[1].y == vecScale.y));

    REQUIRE((build_scale<float>(scale).Column[0].x == scale));
    REQUIRE((build_scale<float>(scale).Column[1].y == scale));

    REQUIRE((build_scale<float>(vecScale).Column[0].x == vecScale.x));
    REQUIRE((build_scale<float>(vecScale).Column[1].y == vecScale.y));

    REQUIRE((build_translation<float>(vecScale.x, vecScale.y).Column[2].x == vecScale.x));
    REQUIRE((build_translation<float>(vecScale.x, vecScale.y).Column[2].y == vecScale.y));
    REQUIRE((build_translation<float>(vecScale.x, vecScale.y).Column[2].z == 1.0f));

    REQUIRE((build_translation<float>(vecScale).Column[2].x == vecScale.x));
    REQUIRE((build_translation<float>(vecScale).Column[2].y == vecScale.y));
    REQUIRE((build_translation<float>(vecScale).Column[2].z == 1.0f));
}
#pragma warning(pop)