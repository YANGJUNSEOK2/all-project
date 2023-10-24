#include "Level1.h"
#include <windows.h>
#include <shellapi.h>
#include "MainMenu.h"

unsigned int i = 0;

Level1 Level1::m_Level1;

void Level1::Init(Engine* game)
{
	Game_Phase = Phase::Phase_Init;

	FileIO newFile;
	newFile.OpenReadFile("Data/Save.txt");
	newFile.Load();
	newFile.CloseReadFile();

	//loadMedia(game->Render());
	g_BG.Background_Init(game);
	g_UI.UI_Init(game);
	player.Init(game);
	Enemy.Init(game);
	attack.Card_Init(game);
	defence.Card_Init(game);
	special.Card_Init(game);
	firstCard.Card_Init(game);
	secondCard.Card_Init(game);
	thirdCard.Card_Init(game);
	Enem_showcard.Card_Init(game);
	Enem_showcard_second.Secret_Card_Init_Second(game);
	Enem_showcard_Third.Secret_Card_Init_Third(game);
	g_BG.BGSound_Play();
	Blood_sucking.Effect_Init(game);
	std::cout << "Level1 Init" << std::endl;

    m_sprite.SpriteInit();
	m_Font.init("Fonts/sunsin.ttf", 64);

	game->getCamera().InitCamera(game->Window().Get_Screen_Width(), game->Window().Get_Screen_Height());
}

void Level1::Close(Engine* game)
{
	game->Cleanup_Objects();
	g_BG.BGSound_Free();
	std::cout << "Level1 Close" << std::endl;
}

void Level1::Pause()
{
	std::cout << "Level1 Paused" << std::endl;
}

void Level1::Resume()
{
	std::cout << "Level1 Resumed" << std::endl;
}



void Level1::Update(Engine* game, float dt)
{
	game->getCamera().UpdateCamera();
	//std::cout << "X: " << game->getMouse().Get_Mouse_Pos().x << "Y: " << game->getMouse().Get_Mouse_Pos().y << std::endl;
	switch (Game_Phase)
	{
	case Phase::Phase_Init:
	{
		Enemy.Settings(EnemyAct);
		Enem_showcard.Setup(EnemyAct[0]);
        for (int count = 0; count < 3; count++)
        {
            game_Cards[count] = CardType::Card_None;
        }
		Game_Phase = Phase::Phase_Choose;
		if (player_current_special_guage <= 3)
		{
			player_current_special_guage++;
		}
	}
	break;
	case Phase::Phase_Choose:
	{
		if (!(game->get_keyboard_input().isKeyDown(SDLK_n)))
		{
			attack.Card_Selecting(game);
			defence.Card_Selecting(game);
			special.Card_Selecting(game);

			if (game->getMouse().Is_Mouse_Clicked(MouseButton::Right))
			{
				for (unsigned int i = 0; i < 3; i++)
				{
					if (game_Cards[i] == CardType::Card_Special)
					{
						special.Reset_Special_selected();
					}
					game_Cards[i] = CardType::Card_None;

				}
			}

			firstCard.Card_Select_Update();
			secondCard.Card_Select_Update();
			thirdCard.Card_Select_Update();
		}
		else if (game_Cards[2] != CardType::Card_None)
		{
			attack.Change_Color(Colors::WHITE);
			defence.Change_Color(Colors::WHITE);
			Game_Phase = Phase::Phase_Compare;
		}
	}
	break;
	case Phase::Phase_Compare:
	{
		Enemy.ResetStat();
		special.Reset_Special_selected();
		battle_stat[0] = Card_Compare(EnemyAct[0], 0);
		battle_stat[1] = Card_Compare(EnemyAct[1], 1);
		battle_stat[2] = Card_Compare(EnemyAct[2], 2);
		Game_Phase = Phase::Phase_Battle;
	}
	break;

	

	case Phase::Phase_Battle:
	{
		firstCard.Change_Color(Colors::RED);
		Enem_showcard.Change_Color(Colors::RED);
		Enem_showcard_second.Setup(EnemyAct[1]);
		Enem_showcard_Third.Setup(EnemyAct[2]);
		
		for (unsigned int i = 0; i < 3; ++i)
		{
			if (battle_stat[0] != BattleStat::Battle_Done)
			{
				Battle(battle_stat[0], 0, Enemy, player);
				break;
			}
			firstCard.Change_Color(Colors::WHITE);
			Enem_showcard.Change_Color(Colors::WHITE);
			secondCard.Change_Color(Colors::RED);
			Enem_showcard_second.Change_Color(Colors::RED);
			if (battle_stat[1] != BattleStat::Battle_Done)
			{
				Battle(battle_stat[1], 1, Enemy, player);
				break;
			}
			secondCard.Change_Color(Colors::WHITE);
			Enem_showcard_second.Change_Color(Colors::WHITE);
			thirdCard.Change_Color(Colors::RED);
			Enem_showcard_Third.Change_Color(Colors::RED);
			if (battle_stat[2] != BattleStat::Battle_Done)
			{
				Battle(battle_stat[2], 2, Enemy, player);
				break;
			}
		}
		if (battle_stat[2] == BattleStat::Battle_Done)
		{
			thirdCard.Change_Color(Colors::WHITE);
			Enem_showcard_Third.Change_Color(Colors::WHITE);
			Enem_showcard_second.SetPath("Texture/Cards/question_mark.png");
			Enem_showcard_Third.SetPath("Texture/Cards/question_mark.png");
			Game_Phase = Phase::Phase_Init;
		}
	}
	break;
	case Phase::Phase_End:
	{

	}
	break;
	}

	if (player.GetHP() <= 0 || Enemy.GetHP() <= 0)
	{
		game->ChangeState(MainMenu::Instance(), game);
	}

	game->Window().Swapbufferwindow();
}

void Level1::Draw(Engine* game)
{
	game->Update_Shaders();

	g_BG.Adding_Screen(game);
	g_UI.Adding_Screen(game);

	player.Adding_Animation(game, 4, 30);
    player.GetHealthUI().Adding_Screen(game);

	Enemy.Adding_Animation(game, 4, 30);
    Enemy.GetHealthUI().Adding_Screen(game);

	attack.Adding_Screen(game);
	defence.Adding_Screen(game);
	special.Adding_Screen(game);

	firstCard.Adding_Screen(game);
	secondCard.Adding_Screen(game);
	thirdCard.Adding_Screen(game);
	
	Enem_showcard.Adding_Screen(game);
	Enem_showcard_second.Adding_Screen(game);
	Enem_showcard_Third.Adding_Screen(game);

	if (player.GetCharStat() == CharacterStatus::Stat_Stunned && Game_Phase != Phase::Phase_Battle)
	{
		player.GetStunnEffect().Adding_Animation(game, 3, 30);
	}
	if (Enemy.GetCharStat() == CharacterStatus::Stat_Stunned && Game_Phase != Phase::Phase_Battle)
	{
		Enemy.GetStunnEffect().Adding_Animation(game, 3, 30);
	}
	
	if (Enemy.GetSpecialStatus())
	{
	Blood_sucking.Update_positions(player.X + 70, player.Y + player.Height / 2);
	Blood_sucking.Adding_Animation(game, 8, 6);
	}

    const Color fontColor(0, 0, 0, 255);
    m_sprite.Begin();
    m_Font.Draw(m_sprite, "Level 1", Vector2<float>{-50.0f, 300.0f}, Vector2<float>{1.0f, 1.0f}, -1.0f, Colors::RED);
    m_sprite.End();
    m_sprite.SpriteRenderBatch();

	game->getShader().UnUseDisable();
}



