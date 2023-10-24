/*
junseok.yang
texture_lap
cs230
spring 2019
Demo.h
*/
#pragma once
#include <CS230/sketch/sketch.hpp>
#include <CS230/window/WindowSize.hpp>
#include <CS230/graphics/Material.hpp>

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

private:
    int   mouseX = 0;
    int   mouseY = 0;
    int   width = 800;
    int   height = 600;
    float seconds = 0;
    int   frameCount = 0;
    bool  isDone = false;

    std::wstring fpsText{};
    float        fpsElapsedTime = 0;
    int          fpsFrames = 0;

    CS230::Sketch           sketch{};
    CS230::Vertices shape{};
    CS230::material material;
    CS230::Texture  texture{};
    CS230::texture_uniform  textureuniform;
    CS230::Vertices         shape2{};
    CS230::material         material2;
    CS230::Texture          texture2{};
    CS230::texture_uniform  textureuniform2;
};
