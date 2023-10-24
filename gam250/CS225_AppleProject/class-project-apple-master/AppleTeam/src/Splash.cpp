/************************************************************************
*	File name : Splash.cpp
*	Project name : apple
*	Author	    Primary author : Junseok Yang
*			    Secondary author : Seungguk Jang
*	File description : Splash Scene
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Splash.h"
#include <string>
#include <iostream>
#include "Engine.h"

bool Splash::Init() noexcept
{
	if (!heroTexture.loadFromFile("assets/orange_hero.png"))
	{
		return false;
	}
	heroSprite = sf::Sprite(heroTexture);

	heroPos.x = 50;
	heroPos.y = HERO_Y_BOTTOM;

	if (!platformTexture.loadFromFile("assets/platform.png"))
	{
		return false;
	}
	platformSprite.setTexture(platformTexture);

	if (!digipenTexture.loadFromFile("assets/DigiPen_BLACK_1024px.png"))
	{
		return false;
	}
	digipenSprite.setTexture(digipenTexture);

	Vector2 winCenter = Engine::WindowIns().GetSize();
	digipenSprite.setOrigin(sf::Vector2f(digipenTexture.getSize()) / 2.f);
	sf::Vector2f center = { static_cast<float>(winCenter.x) * 0.5f , static_cast<float>(winCenter.y) * 0.5f };
	digipenSprite.setPosition(center);

	platformPos.x = 1024 - 20;
	platformPos.y = PLATFORM_Y_BOTTOM;

	Engine::LoggerIns().LogVerbose(levelName + " is Init");
	return true;
}
void Splash::Update([[maybe_unused]] double delta_time) noexcept
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		Engine::SceneManagerIns().SetNextScene(LevelNum::Level1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (isBottom && !isJumping)
		{
			isJumping = true;
			isBottom = false;
		}
	}
	if (isJumping)
	{
		heroPos.y -= gravity;
	}
	else
	{
		heroPos.y += gravity;
	}

	if (heroPos.y >= HERO_Y_BOTTOM)
	{
		heroPos.y = HERO_Y_BOTTOM;
		isBottom = true;
	}
	if (heroPos.y <= HERO_Y_BOTTOM - 100)
	{
		isJumping = false;
	}

	frame += frameSpeed;
	if (frame > changeCount)
	{
		frame -= changeCount;
		++index;
		if (index >= 2) { index = 0; }
	}

	if (platformPos.x <= 0)
	{
		platformPos.x = 1024;
	}
	else
	{
		platformPos.x -= platformSpeed;
	}

	platformSprite.setPosition(platformPos.x, platformPos.y);

	heroSprite.setPosition(heroPos.x, heroPos.y);
	Engine::LoggerIns().LogVerbose(levelName + " is updating");
}
void Splash::Draw() noexcept
{
	Engine::WindowIns().Getwindow().clear(sf::Color::White);
	Engine::WindowIns().Getwindow().draw(heroSprite);
	Engine::WindowIns().Getwindow().draw(platformSprite);
	Engine::WindowIns().Getwindow().draw(digipenSprite);
	Engine::WindowIns().Getwindow().display();

	Engine::LoggerIns().LogVerbose(levelName + " is Drawing");
}
void Splash::ShutDown() noexcept
{
	Engine::LoggerIns().LogVerbose(levelName + " is ShutDown");
}
void Splash::SetNextScene() noexcept
{

}

std::string Splash::GetName() const noexcept
{
	return levelName;
}