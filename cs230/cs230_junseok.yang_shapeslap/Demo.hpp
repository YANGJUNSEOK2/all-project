/*
junseok.yang
shape_lap
cs230
spring 2019
Demo.h
*/
#pragma once
#include <CS230/graphics/Material.hpp>
#include <CS230/graphics/Shader.hpp>
#include <CS230/sketch/sketch.hpp>
#include <CS230/window/InputButtons.hpp>
#include <CS230/window/WindowSize.hpp>

class Demo
{
public:
    bool StartUpWasSuccessful();
    bool ShouldClose() const;
    void Update(float delta_time_seconds);
    void Draw();
    void ShutDown();
    void HandleMouseMove(int mouse_x, int mouse_y);
    void HandleResizeEvent(CS230::window::size size);
    void HandleKeyReleased(CS230::KeyboardButton keyboard_button);

private:
    int   mouseX     = 0;
    int   mouseY     = 0;
    int   width      = 800;
    int   height     = 600;
    float seconds    = 0;
    int   frameCount = 0;
    bool  isDone     = false;

    CS230::Shader   shader_name{};
    CS230::Shader   shader_animal{};

    CS230::Vertices backGround;

    CS230::Vertices name;
    CS230::Vertices name2;
    CS230::Vertices name3;
    CS230::Vertices name4;
    CS230::Vertices name5;
    CS230::Vertices name6;
    CS230::Vertices name7;
    CS230::Vertices name8;
    CS230::Vertices name9;
    CS230::Vertices name10;
    CS230::Vertices name11;
    CS230::Vertices name12;
    CS230::Vertices name13;

    CS230::Vertices shape;
    CS230::Vertices shape2;
    CS230::Vertices shape3;
    CS230::Vertices shape4;
    CS230::Vertices shape5;
    CS230::Vertices shape6;
    CS230::Vertices shape7;
    CS230::Vertices shape8;
    CS230::Vertices shape9;
    CS230::Vertices shape10;
    CS230::Vertices shape11;
    CS230::Vertices shape12;
    CS230::Vertices shape13;
    CS230::Vertices shape14;

    CS230::material material_name{};
    CS230::material material_animal{};
};
