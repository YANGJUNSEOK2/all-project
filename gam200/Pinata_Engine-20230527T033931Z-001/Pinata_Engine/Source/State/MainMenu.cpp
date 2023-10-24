#include "MainMenu.h"
#include "Level1.h"

//main menu
MainMenu MainMenu::m_MainMenu;

void MainMenu::Init(Engine* game)
{
	std::cout << "MainMenu Init" << std::endl;
	CREDIT.SpriteInit("Data/State/MainMenu/UI_Credit.txt", game);
	HOWTOPLAY.SpriteInit("Data/State/MainMenu/UI_Howtoplay.txt", game);
	PLAY.SpriteInit("Data/State/MainMenu/UI_Play.txt", game);
	game->getCamera().InitCamera(game->Window().Get_Screen_Width(), game->Window().Get_Screen_Height());

}

void MainMenu::Close(Engine* game)
{
	game->Cleanup_Objects();
	std::cout << "MaunMenu Close" << std::endl;
}


void MainMenu::Pause()
{
	std::cout << "MaunMenu Paused" << std::endl;
}

void MainMenu::Resume()
{
	std::cout << "MaunMenu Resumed" << std::endl;
}



void MainMenu::Update(Engine* game, float dt)
{
	game->getCamera().UpdateCamera();
	//Update screen
	if (PLAY.Is_mouse_collided())
	{
		if (game->getMouse().Is_Mouse_Clicked(MouseButton::Left))
		{
			game->ChangeState(Level1::Instance(), game);
		}
	}


	game->Window().Swapbufferwindow();
}


void MainMenu::Draw(Engine* game)
{
	game->Update_Shaders();

	CREDIT.Adding_Screen(game);
	HOWTOPLAY.Adding_Screen(game);
	PLAY.Adding_Screen(game);

	game->getShader().UnUseDisable();
}