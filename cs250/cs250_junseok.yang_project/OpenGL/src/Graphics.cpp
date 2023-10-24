/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Graphics.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#include "Graphics.h"
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "lib\ImGuiFileDialog\ImGuiFileDialog.h"

#include <unordered_map>
#include <algorithm>


#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

namespace MyEngine
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    const char* glsl_version = "#version 450";
    Graphics* GRAPHICS = nullptr;

    Graphics::Graphics()
    {
        GRAPHICS = this;
    }

    Graphics::~Graphics()
    {
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        objects_.clear();
        modelName.clear();
        _models.clear();
    }

    void Graphics::Init()
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


        // glfw window creation
        // --------------------
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Breakers", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        stbi_set_flip_vertically_on_load(true);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        mainShader = std::make_unique<Shader>("resources/shader/vertexShader.glsl",
            "resources/shader/fragmentShader.glsl");

        mainShader->use();

        grassShader = std::make_unique<Shader>("resources/shader/grassVShader.glsl",
            "resources/shader/grassFShader.glsl",
            "resources/shader/grassGShader.glsl");
        grassShader->use();

        tessShader = std::make_unique<Shader>("resources/shader/tessVShader.glsl",
            "resources/shader/tessFShader.glsl",
            "resources/shader/tessGShader.glsl",
            "resources/shader/tessCShader.glsl",
            "resources/shader/tessEShader.glsl");
        tessShader->use();

        TessLevelInner = 1;
        TessLevelOuter = 1;

        noise1DShader = std::make_unique<Shader>("resources/shader/vertexShader.glsl",
            "resources/shader/noiseFShader.glsl");
        noise1DShader->use();

        //load model files
        _models["suzzane"] = std::make_unique<Model>("resources/suzanne.obj");

        //create objects
        objects_.emplace_back(std::move(OBJECT->CreateObject("suzzane", glm::vec3(0.f, 0.f, -5.f),
            glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f))));

        camera_ = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

        for (const auto& model : _models)
            modelName.emplace_back(model.first);
    }

    void Graphics::Update(float dt)
    {
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        imguiUpdate(dt);

        //// activate shader
        mainShader->use();
        mainShader->SetUniform("Light.Position", lightPos);
        mainShader->SetUniform("levels", toon_levels);
        mainShader->SetUniform("Light.L", glm::vec3(0.9f));
        mainShader->SetUniform("Light.La", glm::vec3(0.2f));
        mainShader->SetUniform("Material.Kd", obj_color);
        mainShader->SetUniform("Material.Ka", 0.9f * 0.3f, 0.5f * 0.3f, 0.3f * 0.3f);
        if (show_fog)
        {
            mainShader->SetUniform("Fog.MaxDist", fog_max_dist);
            mainShader->SetUniform("Fog.MinDist", 1.0f);
            mainShader->SetUniform("Fog.Color", glm::vec3(clear_color.x, clear_color.y, clear_color.z));
            mainShader->SetUniform("Material.Ks", 0.0f, 0.0f, 0.0f);
            mainShader->SetUniform("Material.Shininess", 180.0f);
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 scale(0.0f);
        glm::mat4 view = camera_->GetViewMatrix();
        glm::mat4 projection =
            glm::perspective(glm::radians(camera_->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat3 normalMatrix(0.0f);
        glm::mat4 modelView;

        if (!show_fog)
        {
            for (const auto& obj : objects_)
            {
                model = glm::mat4(1.0f);
                scale = obj->getScale();
                glm::vec3 transform = obj->getPosition();
                model = glm::translate(model, transform);
                model = glm::scale(model, scale);

                normalMatrix = glm::mat3(glm::transpose(glm::inverse(model * view)));

                if (show_toon)
                {
                    mainShader->SetUniform("model", model);
                    mainShader->SetUniform("view", view);
                    mainShader->SetUniform("projection", projection);
                    mainShader->SetUniform("normalMatrix", normalMatrix);
                    _models[obj->getName()]->Draw_TRIANGLES(*mainShader);
                }

                if (show_normal)
                {
                    grassShader->use();
                    grassShader->SetUniform("model", model);
                    grassShader->SetUniform("view", view);
                    grassShader->SetUniform("projection", projection);
                    grassShader->SetUniform("magnitude", normal_size);
                    grassShader->SetUniform("grass_color", grass_color);
                    _models[obj->getName()]->Draw_TRIANGLES(*grassShader);

                }
                if (show_tess)
                {

                    tessShader->use();
                    modelView = model * view;
                    tessShader->SetUniform("Modelview", modelView);
                    tessShader->SetUniform("Projection", projection);
                    tessShader->SetUniform("LightPosition", lightPos);
                    tessShader->SetUniform("TessLevelInner", TessLevelInner);
                    tessShader->SetUniform("TessLevelOuter", TessLevelOuter);
                    tessShader->SetUniform("Shrink", Shrink);
                    tessShader->SetUniform("tesscolor", tess_color);
                    tessShader->SetUniform("NormalMatrix", normalMatrix);
                    glPatchParameteri(GL_PATCH_VERTICES, 3);
                    _models[obj->getName()]->Draw_PATCHES(*tessShader);
                }
                if (show_noise)
                {
                    noise1DShader->use();
                    noise1DShader->SetUniform("time", dt);
                    noise1DShader->SetUniform("model", model);
                    noise1DShader->SetUniform("view", view);
                    noise1DShader->SetUniform("projection", projection);
                    //noise1DShader->SetUniform("normalMatrix", normalMatrix);
                    _models[obj->getName()]->Draw_TRIANGLES(*noise1DShader);
                }
            }
        }
        else if (show_fog)
        {
            float distance;
            distance = 0.0f;
            for (int i = 0; i < 4; ++i)
            {
                model = glm::translate(model, glm::vec3(distance * 0.6f - 1.0f, 0.0f, -distance));
                normalMatrix = glm::mat3(glm::transpose(glm::inverse(model * view)));
                mainShader->SetUniform("model", model);
                mainShader->SetUniform("view", view);
                mainShader->SetUniform("projection", projection);
                mainShader->SetUniform("normalMatrix", normalMatrix);

                _models["suzzane"]->Draw_TRIANGLES(*mainShader);
                distance += 3.0f;
            }

            if (show_normal)
            {
                grassShader->use();
                distance = 0.0f;
                model = glm::mat4(1.0f);
                for (int i = 0; i < 4; ++i)
                {
                    model = glm::translate(model, glm::vec3(distance * 0.6f - 1.0f, 0.0f, -distance));
                    grassShader->SetUniform("model", model);
                    grassShader->SetUniform("view", view);
                    grassShader->SetUniform("projection", projection);
                    //grassShader->SetUniform("normalMatrix", normalMatrix);
                    grassShader->SetUniform("magnitude", normal_size);
                    grassShader->SetUniform("grass_color", grass_color);
                    _models["suzzane"]->Draw_TRIANGLES(*grassShader);
                    distance += 3.0f;
                }
            }
            if (show_tess)
            {
                tessShader->use();
                distance = 0.0f;
                model = glm::mat4(1.0f);
                for (int i = 0; i < 4; ++i)
                {
                    model = glm::translate(model, glm::vec3(distance * 0.6f - 1.0f, 0.0f, -distance));
                    modelView = model * view;
                    tessShader->SetUniform("Modelview", modelView);
                    tessShader->SetUniform("Projection", projection);
                    tessShader->SetUniform("LightPosition", lightPos);
                    tessShader->SetUniform("TessLevelInner", TessLevelInner);
                    tessShader->SetUniform("TessLevelOuter", TessLevelOuter);
                    tessShader->SetUniform("Shrink", Shrink);
                    tessShader->SetUniform("tesscolor", tess_color);
                    tessShader->SetUniform("NormalMatrix", normalMatrix);
                    glPatchParameteri(GL_PATCH_VERTICES, 3);
                    _models["suzzane"]->Draw_PATCHES(*tessShader);
                    distance += 3.0f;
                }
            }
            if (show_noise)
            {
                distance = 0.0f;
                model = glm::mat4(1.0f);
                for (int i = 0; i < 4; ++i)
                {
                    model = glm::translate(model, glm::vec3(distance * 0.6f - 1.0f, 0.0f, -distance));
                    noise1DShader->use();
                    noise1DShader->SetUniform("time", dt);
                    noise1DShader->SetUniform("model", model);
                    noise1DShader->SetUniform("view", view);
                    noise1DShader->SetUniform("projection", projection);
                    _models["suzzane"]->Draw_TRIANGLES(*noise1DShader);
                    distance += 3.0f;
                }
            }
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera_->process_keyboard(FORWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera_->process_keyboard(BACKWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera_->process_keyboard(LEFT, dt);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera_->process_keyboard(RIGHT, dt);

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void Graphics::imguiInit()
    {
        //// Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void Graphics::imguiUpdate(float dt)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        drawGui();
    }

    void Graphics::drawGui()
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Team Breakers");

        // open Dialog Simple
        if (ImGui::Button("Load Obj File"))
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj", ".", 5);

        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk() == true)
            {
                std::string pathName = ImGuiFileDialog::Instance()->GetCurrentPath();

                for (auto& fileName : ImGuiFileDialog::Instance()->GetSelectedFileNames())
                {
                    std::string filePathName = pathName;
                    filePathName.append('\\' + fileName);
                    std::cout << filePathName << std::endl;
                    // action
                    // Add Model & Model Name
                    size_t lastPoint = fileName.find_last_of('.');
                    if (lastPoint != std::string::npos && (lastPoint != 0))
                    {
                        std::string no_Ext = fileName.substr(0, lastPoint);
                        if (_models.find(no_Ext) == _models.end())
                        {
                            _models[no_Ext] = std::make_unique<Model>(filePathName);
                            modelName.emplace_back(no_Ext);
                        }
                    }
                }
            }
            // close
            ImGuiFileDialog::Instance()->Close();
        }

        static const char* current_item = nullptr;
        if (ImGui::BeginCombo("Loaded Model", current_item))
        {
            for (const auto& model : modelName)
            {
                bool is_selected =
                    (current_item ==
                        model.c_str()); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(model.c_str(), is_selected))
                    current_item = model.c_str();
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
                // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }

            ImGui::EndCombo();
        }

        if (ImGui::Button("Create Object"))
        {
            if (current_item != nullptr)
                objects_.emplace_back(std::move(OBJECT->CreateObject(
                    current_item, glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f))));
        }

        // ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)

        ImGui::ColorEdit3("background color", (float*)&clear_color); // Edit 3 floats representing a color
        ImGui::ColorEdit3("object color", (float*)&obj_color); // Edit 3 floats representing a color

        if (ImGui::CollapsingHeader("Fog Shading"))
        {
            ImGui::Checkbox("Fog On/Off", &show_fog);
            mainShader->SetUniform("show_fog", show_fog);
            ImGui::SliderFloat("fog factor", &fog_max_dist, 2.0f, 30.0f);
        }

        if (ImGui::CollapsingHeader("Toon Shading"))
        {
            ImGui::Checkbox("Toon On/Off", &show_toon);
            mainShader->SetUniform("show_toon", show_toon);
            ImGui::SliderInt("Toon shading levels", &toon_levels, 3, 10);
            mainShader->SetUniform("levels", toon_levels);
        }

        if (ImGui::CollapsingHeader("Geometry Shader"))
        {
            ImGui::Checkbox("Draw Normal", &show_normal);
            ImGui::SliderFloat("normal magnitude", &normal_size, 0.0f, 1.0f);
            ImGui::ColorEdit3("grass color", (float*)&grass_color); // Edit 3 floats representing a color
        }

        if (ImGui::CollapsingHeader("Tess Shader"))
        {
            ImGui::Checkbox("Draw tess", &show_tess);
            ImGui::SliderFloat("TessLevelInner", &TessLevelInner, 1.0f, 5.0f);
            ImGui::SliderFloat("TessLevelOuter", &TessLevelOuter, 1.0f, 5.0f);
            ImGui::SliderFloat("depth", &camera_->Zoom, 1.0f, 100.0f);
            ImGui::SliderFloat("Shrink", &Shrink, 0.0f, 1.0f);
            ImGui::ColorEdit3("tess color", (float*)&tess_color);
        }
        if (ImGui::CollapsingHeader("Noise Shader"))
        {
            ImGui::Checkbox("Draw Noise", &show_noise);
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
            ImGui::GetIO().Framerate);
        ImGui::End();
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}
