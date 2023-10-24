#pragma once
#include "StateManager.h"
#include "..//Game_Objects/Characters.h"
#include "../Game_Objects/GameObjects.h"
#include "../Font/Font.hpp"

class Level1 : public GameState
{
public:

	Level1() = default;
	void Init(Engine* game) override;
	void Close(Engine* game) override;

	void Pause() override;
	void Resume() override;

	void Update(Engine* game, float dt) override;
	void Draw(Engine* game) override;

	// Implement Singleton Pattern
	static Level1* Instance()
	{
		return &m_Level1;
	}
	~Level1() = default;
protected:


private:
    SpriteBatch m_sprite;
    Font m_Font;

	Background g_BG;
	UI g_UI;
	Attack_Card attack;
	Defence_Card defence;
	Special_Card special;

    Select_Card_1 firstCard;
    Select_Card_2 secondCard;
    Select_Card_3 thirdCard;
	
	Player player;
	Enemy Enemy;
	CardType EnemyAct[3];
	BloodSucking_Effects Blood_sucking;
	
	Enemy_Showing_Card Enem_showcard;
	Enemy_Showing_Card Enem_showcard_second;
	Enemy_Showing_Card Enem_showcard_Third;
	
	BattleStat battle_stat[3];
	static Level1 m_Level1;
	//SDL_Surface* menuSprite = nullptr;

    BackgroundSound BGM;

};