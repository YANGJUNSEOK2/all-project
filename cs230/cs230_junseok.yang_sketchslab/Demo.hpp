/*
junseok.yang
sketch_lap
cs230
spring 2019
Demo.h
*/
#pragma once
#include <CS230/sketch/sketch.hpp>
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

    CS230::Sketch sketch{};

    void koch(CS230::vector2 p0, CS230::vector2 p1, float limit);
    void tree(CS230::vector2 p0, CS230::vector2 p1, float limit);
    float my_random(float min, float max);
};