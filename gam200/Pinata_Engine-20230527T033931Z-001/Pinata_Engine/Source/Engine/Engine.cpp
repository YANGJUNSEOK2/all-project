#include "..//State/MainMenu.h"
#include "Engine.h"

void Engine::ChangeState(GameState* state, Engine* game)
{
    // cleanup the current state
    if (!states.empty()) {
        states.back()->Close(game);
        states.pop_back();
    }

    // store and init the new state
    states.push_back(state);
    states.back()->Init(game);
}

void Engine::PushState(GameState* state, Engine* game)
{
    // pause current state
    if (!states.empty()) {
        states.back()->Pause();
    }

    // store and init the new state
    states.push_back(state);
    states.back()->Init(game);
}

void Engine::PopState(Engine* game)
{
    // cleanup the current state
    if (!states.empty()) {
        states.back()->Close(game);
        states.pop_back();
    }

    // resume previous state
    if (!states.empty()) {
        states.back()->Resume();
    }
}

void Engine::Init(Engine* game)
{
    gameWindow.Init();

    timer.ResetTimeStamp();

	InitShader();
}

void Engine::HandleEvents(Engine* game)
{
    // let the state handle events
    states.back()->HandleEvents(this);
}


void Engine::Update()
{
    ImGui::Render();
    ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());

    const auto delta_time_seconds = timer.GetElapsedSeconds();
    timer.ResetTimeStamp();
    TimeUpdate(delta_time_seconds);

    // let the state update the game
    states.back()->Update(this, delta_time_seconds);
}

void Engine::TimeUpdate(float delta_time_seconds)
{
    ++frameCount;
    seconds += delta_time_seconds;

    fpsElapsedTime += delta_time_seconds;
    ++fpsFrames;
    if (fpsElapsedTime >= 1.0f)
    {
        fpsText = L"fps: " + std::to_wstring(int(fpsFrames / fpsElapsedTime));
        fpsElapsedTime = 0;
        fpsFrames = 0;
    }
}

void Engine::Draw()
{
    ImGui_ImplSdlGL3_NewFrame(gameWindow.Get_Window());

    {
        static float f = 0.0f;
        static int counter = 0;
        //ImGui::Text("Test Mode");                           // Display some text (you can use a format string too)
        //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
        ImGui::ColorEdit3("change background color", (float*)&gameWindow.clear_color); // Edit 3 floats representing a color

        //ImGui::Checkbox("Demo Window", &gameWindow.show_demo_window);      // Edit bools storing our windows open/close state
        //ImGui::Checkbox("Another Window", &gameWindow.show_another_window);

        //if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
        //    counter++;
        //ImGui::SameLine();
        //ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
  /*  if (gameWindow.show_another_window)
    {
        ImGui::Begin("Another Window", &gameWindow.show_another_window);
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            gameWindow.show_another_window = false;
        ImGui::End();
    }*/

    //// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
    //if (gameWindow.show_demo_window)
    //{
    //    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
    //    ImGui::ShowDemoWindow(&gameWindow.show_demo_window);
    //}

    // let the state draw the screen
    states.back()->Draw(this);
    //SDL_Flip(m_pScreen);


}

void Engine::Close(Engine* game)
{
    while (!states.empty()) {
        states.back()->Close(game);
        states.pop_back();
    }

    ImGui_ImplSdlGL3_Shutdown();
    ImGui::DestroyContext();

    // shutdown SDL
    SDL_Quit();
}

void Engine::Update_Shaders()
{
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(gameWindow.clear_color.x, gameWindow.clear_color.y, gameWindow.clear_color.z, gameWindow.clear_color.w);

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ColorProgram.UseEnable();

	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = m_ColorProgram.GetUniformLocation("shaderTexture");
	glUniform1i(textureLocation, 0);

	GLuint pLocation = m_ColorProgram.GetUniformLocation("P");

	Matrix3<float> cameraMatrix = m_Camera.GetCameraOrtho();

	glUniformMatrix3fv(pLocation, 1, GL_FALSE, &cameraMatrix.Elements[0][0]);

	
}

void Engine::InitShader()
{
	m_ColorProgram.CompileShaders("Shader/colorShader.vert", "Shader/colorShader.frag");
	m_ColorProgram.AddAttribute("vtPosition");
	m_ColorProgram.AddAttribute("vtColor");
	m_ColorProgram.AddAttribute("vtUV");
	m_ColorProgram.LinkShaders();
}

void Engine::Adding_Objects_To_ObjectsFactory(SpriteBatch* obj)
{
	Objects.push_back(obj);
}

void Engine::Cleanup_Objects()
{
    Objects.clear();
}