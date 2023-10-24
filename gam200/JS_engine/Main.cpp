#include "Source/WindowSystem/WindowSystem.hpp"
#include "Source/Graphics/Shader/Shader.hpp"
#include "Source/MathLibrary/MathLibrary.hpp"
#include "Source/Graphics/Buffer/VertexBuffer.hpp"
#include "Source/Graphics/Buffer/IndexBuffer.hpp"
#include "Source/Graphics/Buffer/VertexArray.hpp"
#include "Source/Graphics/Render/Render.hpp"
#include "Source/Graphics/Render/RenderRegular.hpp"
#include "Source/Graphics/Render/RenderBatch.hpp"
#include "Source/Graphics/Sprite/StaticSprite.hpp"
#include "Source/Graphics/Sprite/Sprite.hpp"
#include "Source/Tools/Timer.hpp"
#include "Source/Graphics/Layer/TileLayer.hpp"
#include "Source/Move/Move.hpp"
#include <time.h>
#include <SDL.h>
#include "Source/MainSystem/MainGame/MainGame.hpp"

int main(int argc, char** argv)
{
    using namespace JS_Engine;
    using namespace MainSystem;

    MainGame mainGame;
    mainGame.GameRun();

    return 0;
}


//int main() {
//    using namespace JS_Engine;
//    using namespace WindowSystem;
//    using namespace Graphics;
//    using namespace MathLibrary;
//    using namespace Tools;
//    using namespace MoveSystem;
//
//    Window EngineWindow("JS_Engine", 960, 540);
//    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//    Matrix Ortho = Matrix::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
//    Shader* Test1 = new Shader("Source/Graphics/Shader/VertexInfo.vert", "Source/Graphics/Shader/FragmentInfo.frag");
//    
//    Shader& T1 = *Test1;
//    
//    T1.ShaderEnable();
//    
//    T1.SetUniformVector2("LightPosition", Vector2(0.0f, 0.0f));
//  
//
//    TileLayer Layer1(&T1);
//    for (float y = -9.0f; y < 9.0f; y += 0.1f) {
//        for (float x = -16.0f; x < 16.0f; x += 0.1f) {
//            Layer1.AddLayer(new Sprite(-2, -2, 4, 4, Vector4(1, 0, 0, 1)));
//        }
//    }
//
//    Timer		 CurrentTime;
//    float		 Timer = 0;
//    unsigned int Frames = 0;
//
//    float x = 0, y = 0;
//    static float speed = 0.5f;
//
//    while (!EngineWindow.IsWindowClosed()) {
//        EngineWindow.ClearWindow();
//        T1.ShaderEnable();
//        Layer1.DrawLayer();
//        Move* moving;
//        T1.SetMoving(Vector2(x, y)); T1.SetMoving(Vector2(x, y + speed));
//        if (EngineWindow.IsKeyboardPressed(GLFW_KEY_UP))
//        {
//            T1.SetMoving(Vector2(x,y+speed));
//            std::cout << "UP" << std::endl;
//        }
//        else if (EngineWindow.IsKeyboardPressed(GLFW_KEY_DOWN))
//        {
//            
//        }
//        if (EngineWindow.IsKeyboardPressed(GLFW_KEY_LEFT))
//        {
//            T1.SetUniformVector2("T1 Speed Left", Vector2(-speed, 0));
//        }
//        else if (EngineWindow.IsKeyboardPressed(GLFW_KEY_RIGHT))
//        {
//            T1.SetUniformVector2("T1 Speed Right", Vector2(speed, 0));
//        }
//
//        EngineWindow.UpdateWindow();
//        Frames++;
//        if (CurrentTime.ElapsedTimer() - Timer > 1.0f) {
//            Timer += 1.0f;
//            printf("%d FPS\n", Frames);
//            Frames = 0;
//        }
//    }
//    return 0;
//}





//int main() {
//    using namespace JS_Engine;
//    using namespace WindowSystem;
//    using namespace Graphics;
//    using namespace MathLibrary;
//    using namespace Tools;
//
//    Window EngineWindow("JS_Engine", 960, 540);
//    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//    Matrix Ortho = Matrix::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
//    Shader* Test1 = new Shader("Source/Graphics/Shader/VertexInfo.vert", "Source/Graphics/Shader/FragmentInfo.frag");
//    Shader* Test2 = new Shader("Source/Graphics/Shader/VertexInfo.vert", "Source/Graphics/Shader/FragmentInfo.frag");
//    Shader& T1 = *Test1;
//    Shader& T2 = *Test2;
//    T1.ShaderEnable();
//    T2.ShaderEnable();
//    T1.SetUniformVector2("LightPosition", Vector2(4.0f, 1.5f));
//    T2.SetUniformVector2("LightPosition", Vector2(4.0f, 1.5f));
//
//    TileLayer Layer1(&T1);
//    for (float y = -9.0f; y < 9.0f; y += 0.1f) {
//        for (float x = -16.0f; x < 16.0f; x += 0.1f) {
//            Layer1.AddLayer(new Sprite(x, y, 0.09f, 0.09f, Vector4(rand() % 1000 / 1000.0f, 0, 1, 1)));
//        }
//    }
//    TileLayer Layer2(&T2);
//    Layer2.AddLayer(new Sprite(-2, -2, 4, 4, Vector4(1, 1, 1, 1)));
//
//    Timer		 CurrentTime;
//    float		 Timer = 0;
//    unsigned int Frames = 0;
//
//    while (!EngineWindow.IsWindowClosed()) {
//        EngineWindow.ClearWindow();
//        double XCoord;
//        double YCoord;
//        EngineWindow.GetMousePosition(XCoord, YCoord);
//        T1.ShaderEnable();
//        T1.SetUniformVector2("LightPosition", Vector2((float)(XCoord * 32.0f / 960.0f - 16.0f), (float)(9.0f - YCoord * 18.0f / 540.0f)));
//        T2.ShaderEnable();
//        T2.SetUniformVector2("LightPosition", Vector2((float)(XCoord * 32.0f / 960.0f - 16.0f), (float)(9.0f - YCoord * 18.0f / 540.0f)));
//        Layer1.DrawLayer();
//        Layer2.DrawLayer();
//
//        EngineWindow.UpdateWindow();
//        Frames++;
//        if (CurrentTime.ElapsedTimer() - Timer > 1.0f) {
//            Timer += 1.0f;
//            printf("%d FPS\n", Frames);
//            Frames = 0;
//        }
//    }
//    return 0;
//}

//int main(int /*argc*/, char* /*argv*/[])
//{
//    //////////////////////////This is the ONLY one you should declare an
//    Application application;//application of your program! Do not declare
//    //////////////////////////another one!!!!
//
//    application.CreateDebugConsole();	// only in DEBUG mode
//
//    if (!application.CanStartUp())
//        return -1;
//    while (!application.IsDone())
//        application.Update();
//
//    application.DeleteDebugConsole();
//    return 0;
//}

//키 마우스 입력
//int main() {
//    using namespace JS_Engine;
//    using namespace WindowSystem;
//
//    Window EngineWindow("SimpleEngine", 960, 540);
//    glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
//
//    GLuint VAO;
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    while (!EngineWindow.IsWindowClosed()) {
//        EngineWindow.ClearWindow();
//        if (EngineWindow.IsKeyboardPressed(GLFW_KEY_A)) {
//            std::cout << "[A] KEYBOARD KEY PRESSED" << std::endl;
//        }
//        if (EngineWindow.IsMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
//            std::cout << "[LEFT] MOUSE BUTTON PRESSED" << std::endl;
//        }
//
//        double XPosition;
//        double YPosition;
//        EngineWindow.GetMousePosition(XPosition, YPosition);
//        std::cout << "(" << XPosition << ", " << YPosition << ")" << std::endl;
//
//        glBegin(GL_QUADS);
//        glVertex2f(-0.5f, -0.5f);
//        glVertex2f(-0.5f, 0.5f);
//        glVertex2f(0.5f, 0.5f);
//        glVertex2f(0.5f, -0.5f);
//        glEnd();
//        glDrawArrays(GL_ARRAY_BUFFER, 0, 0);
//        EngineWindow.UpdateWindow();
//    }
//    return 0;
//}