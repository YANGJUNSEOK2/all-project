/*
junseok.yang
shaderslab
cs230
spring 2019
Demo.hpp
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

    CS230::Shader   shader{};
    CS230::Vertices shape;
    CS230::material material{};
};
