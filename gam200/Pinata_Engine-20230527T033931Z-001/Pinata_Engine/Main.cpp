#include "Source/FPS/FPS.h"
#include "Source/Engine/Engine.h"
#include "Source/State/MainMenu.h"

int main(int argc, char* args[])
{
	FPS fps;
	float m_fps;
	float m_MaxFPS = 70.f;
	fps.Init(m_MaxFPS);


	Engine game;
	//Start up SDL and create window
	game.Init(&game);

	game.ChangeState(MainMenu::Instance(), &game);

	//While application is running
	while (game.Running())
	{
		//Handle events on queue
		game.HandleEvents(&game);
		game.Draw();
		game.Update();
		Physics::IsCollidingWith_Object(&game, game.get_objects());
		fps.Begin();
		m_fps = fps.End();
		game.Window().Show_FPS_Inwindow(m_fps);
	}

	//Free resources and close SDL
	game.Close(&game);

	return 0;
}
