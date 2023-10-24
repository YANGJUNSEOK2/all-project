/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: main.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <Graphics.h>

#include <iostream>
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
double deltaTime = 0.0;	// time between current frame and last frame
double lastFrame = 0.0;
float alpha = 0.0f;

int main()
{
    MyEngine::Graphics graphics;
    graphics.Init();
    graphics.imguiInit();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(graphics.GetWindow()))
    {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(graphics.GetWindow());

        // render
        // ------
        graphics.Update((float)deltaTime);
    }
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}