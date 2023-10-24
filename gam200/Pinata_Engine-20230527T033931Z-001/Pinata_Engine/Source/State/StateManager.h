#pragma once
#include <iostream>
#include "SDL.h"
#include "../Engine/Engine.h"
#include "../FPS/FPS.h"
#include "../IO_Manager/KeyboardInput.h"
#include "..//IO_Manager/MouseInput.h"
#include "../Camera/Camera.hpp"
#include "../Shader/Shader.hpp"
#include "../Sprite/SpriteBatch/SpriteBatch.hpp"
#include "../Texture/Texture.hpp"
#include "../Sound/Sound.hpp"
#include "../Game_Objects/Colors.h"
#include "../IO_Manager/file_IO.h"
#include "../Game_Objects/Characters.h"
#include "../Game_Objects/GameObjects.h"

class GameState
{
public:
	virtual void Init(Engine* game) = 0;
	virtual void Close(Engine* game) = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	void HandleEvents(Engine* game);
	void FrameDelay(FPS* fpslimiter,float &m_fps);

	virtual void Update(Engine* game, float dt) = 0;
	virtual void Draw(Engine* game) = 0;

	static void ChangeState(Engine* game, GameState* state) {
		game->ChangeState(state, game);
	}

	 BattleStat Card_Compare(CardType Enemy_Act, int order);
	 void Battle(BattleStat& bt_stat, int order,Enemy& enemy, Player& player);
private:
	int delay = 0;

protected:
	GameState() = default;
};