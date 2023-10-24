#pragma once
#include "StateManager.h"

class MainMenu : public GameState
{
public:

	MainMenu() = default;
	void Init(Engine* game) override;
	void Close(Engine* game) override;

	void Pause() override;
	void Resume() override;

	void Update(Engine* game, float dt) override;
	void Draw(Engine* game) override;

	// Implement Singleton Pattern
	static MainMenu* Instance()
	{
		return &m_MainMenu;
	}
	~MainMenu() = default;
protected:


private:
	SpriteBatch HOWTOPLAY;
	SpriteBatch CREDIT;
	SpriteBatch PLAY;
	static MainMenu m_MainMenu;
	//SDL_Surface* menuSprite = nullptr;
};
