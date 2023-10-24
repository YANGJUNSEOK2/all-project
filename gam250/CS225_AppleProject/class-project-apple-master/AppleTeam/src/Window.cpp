/************************************************************************
*	File name : Window.cpp
*	Project name : apple
*	Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Create and Control Window
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "InputManager.h"
#include "Engine.h"
void Window::Init() noexcept
{
	window.create(sf::VideoMode(screenSize.x, screenSize.y), "Apple project");
}
void Window::UpdateEvent() noexcept
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Num1)
			{
				Engine::InputManagerIns().SetKey(InputManager::KeyboardMapping::_1, true);
			}
			else if (event.key.code == sf::Keyboard::Num2)
			{
				Engine::InputManagerIns().SetKey(InputManager::KeyboardMapping::_2, true);
			}
			else if (event.key.code == sf::Keyboard::Num3)
			{
				Engine::InputManagerIns().SetKey(InputManager::KeyboardMapping::_3, true);
			}
			else if (event.key.code == sf::Keyboard::Num4)
			{
				Engine::InputManagerIns().SetKey(InputManager::KeyboardMapping::_4, true);
			}
			else if (event.key.code == sf::Keyboard::Num5)
			{
				Engine::InputManagerIns().SetKey(InputManager::KeyboardMapping::_5, true);
			}
			else if (event.key.code == sf::Keyboard::Num6)
			{
				Engine::InputManagerIns().SetKey(InputManager::KeyboardMapping::_6, true);
			}
			else if (event.key.code == sf::Keyboard::F1)
			{
				Engine::InputManagerIns().SetKey(InputManager::KeyboardMapping::F1, true);
			}
			else if (event.key.code == sf::Keyboard::F2)
			{
				Engine::InputManagerIns().SetKey(InputManager::KeyboardMapping::F2, true);
			}
			break;
		}
	}
}
void Window::Resize(int newWidth, int newHeight) noexcept {
	screenSize.x = newWidth;
	screenSize.y = newHeight;
	window.setSize(screenSize);
}

Vector2 Window::GetSize() const noexcept {
	return Vector2{ static_cast<int>(screenSize.x),static_cast<int>(screenSize.y) };
}

