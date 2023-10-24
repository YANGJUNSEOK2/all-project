#include"MainGame.hpp"
#include<iostream>
#include<string>


namespace JS_Engine {
    namespace MainSystem {
        MainGame::MainGame():m_ScreenWidth(960),m_ScreenHeight(540), m_time(0.0f), m_Window(nullptr),m_GameState(GameState::PLAY)
        {
 
        }

        MainGame::~MainGame()
        {
        }

        void MainGame::GameRun()
        {
            InitSystem();

            m_Sprite.Init(-1,-1,2,2);

            m_PlayerTexture = ImageLoader::loadPNG("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

            GameLoop();
        }

        void MainGame::InitSystem()
        {
            //Initalize SDL
            SDL_Init(SDL_INIT_EVERYTHING);

            m_Window = SDL_CreateWindow("JS_Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,m_ScreenWidth,m_ScreenHeight,SDL_WINDOW_OPENGL);
            if(m_Window==nullptr)
            {
                ErrorSystem::FatalError("SDL Window could not be created!");
            }

            SDL_GLContext p_glContext = SDL_GL_CreateContext(m_Window);
            if(p_glContext==nullptr)
            {
                ErrorSystem::FatalError("SDL_GLContext could not be created!");
            }

            //glewExperimental = true;
            GLenum error = glewInit();
            if(error!=GLEW_OK)
            {
                ErrorSystem::FatalError("Could not init glew!");
            }

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            glClearColor(0, 0, 1.0f, 1.0f);

            InitShaders();
        }

        void MainGame::InitShaders()
        {
            m_ColorProgram.compileShaders("Source/MainSystem/GLSLProgram/colorShader.vert", "Source/MainSystem/GLSLProgram/colorShader.frag");
            //m_ColorProgram.compileShaders("Source/Graphics/Shader/VertexInfo.vert", "Source/Graphics/Shader/FragmentInfo.frag");
            m_ColorProgram.addAttribute("vertexPosition");
            m_ColorProgram.addAttribute("vertexColor");
            m_ColorProgram.addAttribute("vertexUV");
            m_ColorProgram.linkShaders();
         //m_ColorShader = new Graphics::Shader("Source/Graphics/Shader/VertexInfo.vert", "Source/Graphics/Shader/FragmentInfo.frag");
        }

        void MainGame::GameLoop()
        {
            while (m_GameState !=GameState::EXIT)
            {
                ProcessInput();
                m_time += 0.01f;
                DrawGame();
            }
        }

        void MainGame::ProcessInput()
        {
            SDL_Event p_Event;
           while(SDL_PollEvent(&p_Event))
           {
               switch (p_Event.type)
               {
               case SDL_QUIT:
                   m_GameState = GameState::EXIT;
                   break;
               case SDL_MOUSEMOTION:
                   std::cout << p_Event.motion.x << " " << p_Event.motion.y << std::endl;
                   break;
               }
           }
        }

        void MainGame::DrawGame()
        {
        
            glClearDepth(1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /*MathLibrary::Matrix Ortho = MathLibrary::Matrix::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
            m_ColorShader->ShaderEnable();
            m_ColorShader->SetUniformMatrix("ProjectionMatrix", Ortho);
            m_ColorShader->SetUniformMatrix("ModelMatrix", MathLibrary::Matrix::Translate(MathLibrary::Vector3(1, 1, 0)));
            m_ColorShader->SetUniformVector2("LightPosition", MathLibrary::Vector2(4.0f, 1.5f));
            m_ColorShader->SetUniformVector4("ColorInput", MathLibrary::Vector4(1.f, 0.f, 0.f, 1.0f));*/

            m_ColorProgram.useEnable();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_PlayerTexture.id);
            GLint textureLocation = m_ColorProgram.getUniformLocation("mySampler");
            glUniform1i(textureLocation, 0);

            GLuint timeLocation = m_ColorProgram.getUniformLocation("time");
            glUniform1f(timeLocation, m_time);

            m_Sprite.Draw();

            glBindTexture(GL_TEXTURE_2D, 0);
            m_ColorProgram.unUseDiable();

            //m_ColorShader->ShaderDisable();

            /*glEnableClientState(GL_COLOR_ARRAY);
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(-1, -1);
            glVertex2f(0, -1);
            glVertex2f(0, 0);
            glEnd();*/

            SDL_GL_SwapWindow(m_Window);
        }
    }
}