/*
junseok.yang
assignment4
cs230
spring 2019
Mesh.cpp
*/
#include <CS230/graphics/Mesh.hpp>         //include mesh
#include <CS230/math/angles.hpp>           //include angle PI TWO_PI...
#include <cmath>                           //use cos() sin()
#include <CS230/window/WindowSize.hpp>      

std::size_t CS230::Mesh::GetPointCount() const noexcept
{
    return points.size();
}

CS230::vector2 CS230::Mesh::GetPoint(std::size_t index) const noexcept
{
    if (index >= 0 && index < GetPointCount())
    {
        return points[index];
    }
    else
        return points.back();
}

CS230::Color4ub CS230::Mesh::GetColor(std::size_t index) const noexcept
{
    if (index >= 0 && index < colors.size())
    {
        return colors[index];
    }
    else if(colors.size()==0)
    {
        Color4ub black(255);
        return black;
    }
    else
    {
        return colors.back();
    }
}

CS230::vector2 CS230::Mesh::GetTextureCoordinate(std::size_t index) const noexcept
{
    if (index >= 0 && index < textureCoordinates.size())
    {
        return textureCoordinates[index];
    }
    else if(textureCoordinates.size()==0)
    {
        return {0,0};
    }
    else
    {
        return textureCoordinates.back();
    }
}

CS230::PointListPattern CS230::Mesh::GetPointListPattern() const noexcept
{
    return pointListType;
}

void CS230::Mesh::SetPointListType(PointListPattern type) noexcept
{
    pointListType = type;
}

void CS230::Mesh::AddColor(Color4ub color) noexcept
{
    colors.push_back(color);
}

void CS230::Mesh::AddPoint(vector2 point) noexcept
{
    points.push_back(point);   
}

void CS230::Mesh::AddTextureCoordinate(vector2 texture_coordinate) noexcept
{
    textureCoordinates.push_back(texture_coordinate);
}

void CS230::Mesh::ClearColors() noexcept
{
    colors.clear();
}

bool CS230::Mesh::HasMoreThanOneColor() const noexcept
{
    if (colors.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CS230::Mesh::ClearTextureCoordinates() noexcept
{
    textureCoordinates.clear();
}

void CS230::Mesh::ClearPoints() noexcept
{
    points.clear();
}

void CS230::Mesh::Clear() noexcept
{
    ClearColors();
    ClearPoints();
    ClearTextureCoordinates();
}

CS230::Mesh CS230::MESH::create_circle(float radius, Color4ub color, std::size_t point_count) noexcept
{
    Mesh m_Mesh_Circle;

    m_Mesh_Circle.SetPointListType(PointListPattern::TriangleFan);

    m_Mesh_Circle.AddPoint({ 0,0 });
    
    for (float i = 0; i <= TWO_PI; i += (TWO_PI) / point_count)
    {
        m_Mesh_Circle.AddPoint({ radius*sin(i), -radius*cos(i) });
    }
    m_Mesh_Circle.AddColor(color);
    
    return m_Mesh_Circle;
}

CS230::Mesh CS230::MESH::create_wire_circle(float radius, Color4ub color, std::size_t point_count) noexcept
{
    Mesh m_Mesh_Wire_Circle;

    m_Mesh_Wire_Circle.SetPointListType(PointListPattern::LineLoop);

    for (float i = 0; i <= TWO_PI; i += (TWO_PI) / point_count)
    {
        m_Mesh_Wire_Circle.AddPoint({ radius*sin(i), -radius*cos(i) });
    }
    m_Mesh_Wire_Circle.AddColor(color);
    return m_Mesh_Wire_Circle;
}

CS230::Mesh CS230::MESH::create_box(float dimension, Color4ub color) noexcept
{
    return create_rectangle(dimension, dimension, color);
}

CS230::Mesh CS230::MESH::create_rectangle(float width, float height, Color4ub color) noexcept
{
    Mesh m_Mesh_Rectangle;

    m_Mesh_Rectangle.SetPointListType(PointListPattern::TriangleFan);

    m_Mesh_Rectangle.AddPoint({ -width / 2,-height / 2 });
    m_Mesh_Rectangle.AddTextureCoordinate({ 0,1 });
    m_Mesh_Rectangle.AddPoint({ -width / 2,height / 2 });
    m_Mesh_Rectangle.AddTextureCoordinate({ 0,0 });
    m_Mesh_Rectangle.AddPoint({ width / 2,height / 2 });
    m_Mesh_Rectangle.AddTextureCoordinate({ 1,0 });
    m_Mesh_Rectangle.AddPoint({ width / 2,-height / 2 });
    m_Mesh_Rectangle.AddTextureCoordinate({ 1,1 });
    m_Mesh_Rectangle.AddColor(color);
   
    return m_Mesh_Rectangle;
}

CS230::Mesh CS230::MESH::create_wire_rectangle(float width, float height, Color4ub color) noexcept
{
    Mesh m_Mesh_Wire_Rectangle;

    m_Mesh_Wire_Rectangle.SetPointListType(PointListPattern::LineLoop);

    m_Mesh_Wire_Rectangle.AddPoint({ -width / 2,-height / 2 });
    m_Mesh_Wire_Rectangle.AddPoint({ -width / 2,height / 2 });
    m_Mesh_Wire_Rectangle.AddPoint({ width / 2,height / 2 });
    m_Mesh_Wire_Rectangle.AddPoint({ width / 2,-height / 2 });
    m_Mesh_Wire_Rectangle.AddColor(color);

    return m_Mesh_Wire_Rectangle;
}

CS230::Mesh CS230::MESH::create_wire_box(float dimension, Color4ub color) noexcept
{
    return create_wire_rectangle(dimension, dimension, color);
}

CS230::Mesh CS230::MESH::create_line(vector2 a, vector2 b, Color4ub color) noexcept
{
    Mesh m_Mesh_Line;

    m_Mesh_Line.SetPointListType(PointListPattern::Lines);

    m_Mesh_Line.AddPoint(a);
    m_Mesh_Line.AddPoint(b);
    m_Mesh_Line.AddColor(color);

    return m_Mesh_Line;
}
