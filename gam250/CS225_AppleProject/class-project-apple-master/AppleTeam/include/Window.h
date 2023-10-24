/************************************************************************
*	File name : Window.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Create and Control Window
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include <string>
#include "Vector2d.h"
#include <SFML/Graphics.hpp>
#include "Common.h"
class [[nodiscard]] Window {
public:
    void Init() noexcept;
    void Resize(int newWidth, int newHeight) noexcept;
    void UpdateEvent() noexcept;
    Vector2 GetSize() const noexcept;
	
    sf::RenderWindow& Getwindow() noexcept { return window; }

private:
    sf::Vector2u screenSize = { WindowInfo::WIDTH, WindowInfo::HEIGHT };
    sf::RenderWindow  window;
};