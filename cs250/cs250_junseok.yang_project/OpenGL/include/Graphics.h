/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Graphics.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#pragma once

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <iostream>
#include <unordered_map>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "shader.h"
#include "Camera.h"
#include "model.h"
#include "mesh.h"
#include "object.h"
namespace MyEngine
{
    class Graphics
    {
    public:
        Graphics();
        ~Graphics();
        void Init();
        void Update(float dt);
        void imguiInit();
        void imguiUpdate(float dt);
        void drawGui();

        GLFWwindow* GetWindow() { return window; }

    private:
        std::unique_ptr<Shader> mainShader;
        std::unique_ptr<Shader> grassShader;
        std::unique_ptr<Shader> tessShader;
        std::unique_ptr<Shader> noise1DShader;

        std::unique_ptr<Camera> camera_;

        std::vector<std::unique_ptr<Object>> objects_;
        std::vector<std::string> modelName;
        std::unordered_map<std::string, std::unique_ptr<Model>> _models;
        std::unordered_map<std::string, std::unique_ptr<Mesh>> _meshs;

        GLFWwindow* window = nullptr;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        bool show_toon = false;

        bool show_fog = false;
        float fog_max_dist = 30.f;
        bool show_normal = false;
        float normal_size = 0.2f;

        bool show_tess = false;
        bool show_noise = false;
        glm::vec3 grass_color = glm::vec3(0.51, 0.11, 0.07);

        glm::vec3 mesh_color = glm::vec3(1.0, 0.51, 0.07);

        glm::vec3 tess_color = glm::vec3(0.0, 1.0, 1.0);

        // lighting
        glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 0.0f);
        // glfw: whenever the window size changed (by OS or user resize) this callback function executes
        // ---------------------------------------------------------------------------------------------


        glm::mat4 ProjectionMatrix{};
        glm::mat4 ModelviewMatrix{};
        glm::mat3 NormalMatrix{};
        float     TessLevelInner{ 1 };
        float     TessLevelOuter{ 1 };
        float     Shrink{ 0.9f };


        const int SCR_WIDTH = 1200;
        const int SCR_HEIGHT = 900;
        int toon_levels = 3;
        glm::vec3 obj_color = glm::vec3(0.1f, 0.5f, 0.3f);

        enum STATE
        {
            STATE_DEFAULT,
            STATE_FOG,
            STATE_TOON,
            STATE_NOISE,
            STATE_TESS,
            STATE_SPLINE,
            STATE_SHADOW
        }state_;
    };
    extern Graphics* GRAPHICS;
}

#endif