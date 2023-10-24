#include "StateManager.h"

void GameState::HandleEvents(Engine* game)
{
	game->getMouse().Mouse_Nothing();

	SDL_Event p_Event;

	ImGui_ImplSdlGL3_ProcessEvent(&p_Event);

	while (SDL_PollEvent(&p_Event) != 0)
	{
		switch (p_Event.type)
		{
		case SDL_QUIT:
			game->Quit();
			break;
		case SDL_MOUSEMOTION:
		{
			int x = (p_Event.motion.x - game->Window().Get_Screen_Width() / 2) / game->getCamera().GetScale();
			int y = (p_Event.motion.y - game->Window().Get_Screen_Height() / 2) / game->getCamera().GetScale();
			game->getMouse().SetMousePos(x, y);
		}
		break;
		case SDL_KEYDOWN:
			game->get_keyboard_input().pressKey(p_Event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			if (p_Event.key.keysym.sym == SDLK_v)
			{
				game->Window().Set_Window_Vsync();
			}
			else if (p_Event.key.keysym.sym == SDLK_f)
			{
				game->Window().Change_Window_Type();
			}
			game->get_keyboard_input().releaseKey(p_Event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
		{
			if (p_Event.button.button == SDL_BUTTON_LEFT)
			{
				game->getMouse().Mouse_Downed(MouseButton::Left);
			}
			else if (p_Event.button.button == SDL_BUTTON_RIGHT)
			{
				game->getMouse().Mouse_Downed(MouseButton::Right);
			}
			else if (p_Event.button.button == SDL_BUTTON_MIDDLE)
			{
				game->getMouse().Mouse_Downed(MouseButton::Wheel);
			}
		}
		break;
		case SDL_MOUSEBUTTONUP:
		{
			if (p_Event.button.button == SDL_BUTTON_LEFT)
			{
				game->getMouse().Mouse_Clicked(MouseButton::Left);
			}
			else if (p_Event.button.button == SDL_BUTTON_RIGHT)
			{
				game->getMouse().Mouse_Clicked(MouseButton::Right);
			}
			else if (p_Event.button.button == SDL_BUTTON_MIDDLE)
			{
				game->getMouse().Mouse_Clicked(MouseButton::Wheel);
			}
		}
		break;
		//case SDL_MOUSEWHEEL:
		//{
		//    const float SPEED_SCALE = 0.1f;

		//    if (p_Event.wheel.y > 0 && game->getCamera().GetScale() < 1)
		//    {
		//        game->getCamera().SetCameraZoom(SPEED_SCALE);
		//        //SetScale(m_Camera.GetScale() + SPEED_SCALE);
		//    }
		//    else if (p_Event.wheel.y < 0 && game->getCamera().GetScale() > 0.3)
		//    {
		//        game->getCamera().SetCameraZoom(-SPEED_SCALE);
		//    }
		//}
		}

	}

	if (game->get_keyboard_input().isKeyPressed(SDLK_ESCAPE))
	{
		game->Quit();
	}
}

void GameState::FrameDelay(FPS* fpslimiter, float& m_fps)
{
	fpslimiter->Begin();
	m_fps = fpslimiter->End();
}

BattleStat GameState::Card_Compare(CardType Enemy_Act, int order)
{
	delay = 0;
	BattleStat bt_stat;
	if (game_Cards[order] == Card_Attack)
	{
		switch (Enemy_Act)
		{
		case CardType::Card_Attack:
			bt_stat = BattleStat::Attack_VS_Attack;
			break;
		case CardType::Card_Defence:
			bt_stat = BattleStat::Attack_VS_Def;
			break;
		case CardType::Card_Special:
			bt_stat = BattleStat::Attack_VS_Special;
			break;
		case CardType::Card_Stunned:
			bt_stat = BattleStat::Attack_VS_None;
			break;
		}
	}
	else if (game_Cards[order] == Card_Defence)
	{
		switch (Enemy_Act)
		{
		case CardType::Card_Attack:
			bt_stat = BattleStat::Def_VS_Attack;
			break;
		case CardType::Card_Defence:
			bt_stat = BattleStat::Def_VS_Def;
			break;
		case CardType::Card_Special:
			bt_stat = BattleStat::Def_VS_Special;
			break;
		case CardType::Card_Stunned:
			bt_stat = BattleStat::DeF_VS_None;
			break;
		}
	}
	else if (game_Cards[order] == Card_Special)
	{
		switch (Enemy_Act)
		{
		case CardType::Card_Attack:
			bt_stat = BattleStat::Special_VS_Attack;
			break;
		case CardType::Card_Defence:
			bt_stat = BattleStat::Special_VS_Def;
			break;
		case CardType::Card_Special:
			bt_stat = BattleStat::Special_VS_Special;
			break;
		}
	}
	return bt_stat;
}

void GameState::Battle(BattleStat& bt_stat, int order, Enemy& enemy, Player& player)
{
	
	
	switch (bt_stat)
	{
	case BattleStat::Attack_VS_Attack:
	{
		player.Attack(delay,enemy, order);
		enemy.Attack(delay,player, order);
	}
	break;
	case BattleStat::Attack_VS_Def:
	{
		enemy.Defence(delay);
		player.Attack(delay,enemy, order);
		
	}
	break;
	case BattleStat::Attack_VS_Special:
	{
		player.Attack(delay,enemy, order);
		enemy.Special(delay, player);
	}
	break;
	case BattleStat::Def_VS_Attack:
	{
		player.Defence(delay);
		enemy.Attack(delay,player, order);
	}
	break;
	case BattleStat::Def_VS_Def:
	{
		player.Defence(delay);
		enemy.Defence(delay);
	}
	break;
	case BattleStat::Def_VS_Special:
	{
		player.Defence(delay);
		enemy.Special(delay, player);
	}
	break;
	case BattleStat::Special_VS_Attack:
	{
		player.Special(delay, enemy);
		enemy.Attack(delay, player, order);
	}
	break;
	case BattleStat::Special_VS_Def:
	{
		player.Special(delay, enemy);
		enemy.Defence(delay);
	}
	break;
	case BattleStat::Special_VS_Special:
	{
		player.Special(delay, enemy);
		enemy.Special(delay, player);
	}
	break;
	case BattleStat::Attack_VS_None:
	{
		player.Attack(delay, enemy, order);
	}
	break;
	case BattleStat::DeF_VS_None:
	{
		player.Defence(delay);
	}
	break;
	}


	if (delay == 100)
	{
		delay = 0;
		bt_stat = BattleStat::Battle_Done;
	}
	else
	{
		delay++;
	}
}
