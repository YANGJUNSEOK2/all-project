/************************************************************************
*	File name : Vertex.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once

#include <glew.h>
#include "../MathLibrary/Vector2.hpp"

struct Position
{
    float x;
    float y;
};

struct Color
{
    Color() : r(0), g(0), b(0), a(0) {}
    Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a) :
        r(r), g(g), b(b), a(a) {}
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

struct UV
{
    float u;
    float v;
};

struct Vertex
{
    Position position = { 0.f,0.f };
    Color color;
    UV uv = { 0.f,0.f };

    void setPosition(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    Vector2<float> getPosition()
    {
        return { position.x ,position.y };
    }

    void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
    {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void setUV(float u, float v)
    {
        uv.u = u;
        uv.v = v;
    }

    Vector2<float> getUV()
    {
        return { uv.u ,uv.v };
    }
};

