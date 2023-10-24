/************************************************************************
*	File name : Triomino.cpp
*	Project name : apple
*	Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description :
*	Explain : Middle of block(cell) is weight. For example,
*	000             0@0                   000
*	0@@  is left up @@0 is right down but @@@ is horizontal,
*	0@0             000                   000
*
*	0@0
*	0@0 is vertical
*	0@0
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Triomino.h"
#include "Common.h"
#include <SFML/Graphics.hpp>
Triomino::Triomino() noexcept
{
	for (int r = 0; r < TRIWIDTH; r++)
	{
		int i = 0;
		if (i < TRIHEIGHT)
		{
			mTri[r][i].boardPos = { (r - TRIWIDTH * 0.5f), (-TRIHEIGHT * 0.5f) };
			mTri[r][i].windowCenterPos = { (WindowInfo::WIDTH * 0.5f), (WindowInfo::HEIGHT * 0.5f) };
			mTri[r][i].cellType = CellInfo::Type::NOTHING;
			mTri[r][i+1].boardPos = { (r - TRIWIDTH * 0.5f), (1 - TRIHEIGHT * 0.5f) };
			mTri[r][i+1].windowCenterPos = { (WindowInfo::WIDTH * 0.5f), (WindowInfo::HEIGHT * 0.5f) };
			mTri[r][i+1].cellType = CellInfo::Type::NOTHING;
			mTri[r][i+2].boardPos = { (r - TRIWIDTH * 0.5f), (2 - TRIHEIGHT * 0.5f) };
			mTri[r][i+2].windowCenterPos = { (WindowInfo::WIDTH * 0.5f), (WindowInfo::HEIGHT * 0.5f) };
			mTri[r][i+2].cellType = CellInfo::Type::NOTHING;
		}
		i += TRIHEIGHT;
	}
	mType = TriominoInfo::Type::LEFTDOWN;
}

void Triomino::SetSprite(std::shared_ptr<sf::Sprite> a_Sprite) noexcept
{
	triSprite = a_Sprite;
}
void Triomino::UpdateCellPosition() noexcept
{
	for (int r = 0; r < TRIWIDTH; r++)
	{
		for (int c = 0; c < TRIHEIGHT; c++)
		{
			mTri[r][c].SetSprite(triSprite);
			mTri[r][c].UpdateSpritePos();
		}
	}
}
void Triomino::SetType(TriominoInfo::Type aType) noexcept
{
    mType = aType;
}

void Triomino::Update() noexcept
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::WindowIns().Getwindow());
	v2 pixelPosition = { static_cast<float>(pixelPos.x), static_cast<float>(pixelPos.y) };
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			mTri[r][c].cellType = CellInfo::Type::NOTHING;
			mTri[r][c].windowCenterPos = pixelPosition;
			mTri[r][c].UpdateSpritePos();
		}
	}
	switch (mType)
	{
	case TriominoInfo::Type::LEFTUP:
		if (isBlue == true)
		{
			mTri[1][1].cellType = CellInfo::Type::BLUE;
			mTri[1][0].cellType = CellInfo::Type::BLUE;
			mTri[0][1].cellType = CellInfo::Type::BLUE;
		}
		else
		{
			mTri[1][1].cellType = CellInfo::Type::RED;
			mTri[1][0].cellType = CellInfo::Type::RED;
			mTri[0][1].cellType = CellInfo::Type::RED;
		}
		break;
	case TriominoInfo::Type::LEFTDOWN:
		if (isBlue == true)
		{
			mTri[1][1].cellType = CellInfo::Type::BLUE;
			mTri[1][2].cellType = CellInfo::Type::BLUE;
			mTri[0][1].cellType = CellInfo::Type::BLUE;
		}
		else
		{
			mTri[1][1].cellType = CellInfo::Type::RED;
			mTri[1][2].cellType = CellInfo::Type::RED;
			mTri[0][1].cellType = CellInfo::Type::RED;
		}
		break;
	case TriominoInfo::Type::RIGHTUP:
		if (isBlue == true)
		{
			mTri[1][1].cellType = CellInfo::Type::BLUE;
			mTri[2][1].cellType = CellInfo::Type::BLUE;
			mTri[1][0].cellType = CellInfo::Type::BLUE;
		}
		else
		{
			mTri[1][1].cellType = CellInfo::Type::RED;
			mTri[2][1].cellType = CellInfo::Type::RED;
			mTri[1][0].cellType = CellInfo::Type::RED;
		}
		break;
	case TriominoInfo::Type::RIGHTDOWN:
		if (isBlue == true)
		{
			mTri[1][1].cellType = CellInfo::Type::BLUE;
			mTri[1][2].cellType = CellInfo::Type::BLUE;
			mTri[2][1].cellType = CellInfo::Type::BLUE;
		}
		else
		{
			mTri[1][1].cellType = CellInfo::Type::RED;
			mTri[1][2].cellType = CellInfo::Type::RED;
			mTri[2][1].cellType = CellInfo::Type::RED;
		}
		break;
	case TriominoInfo::Type::HORIZONTAL:
		if (isBlue == true)
		{
			mTri[2][1].cellType = CellInfo::Type::BLUE;
			mTri[1][1].cellType = CellInfo::Type::BLUE;
			mTri[0][1].cellType = CellInfo::Type::BLUE;
		}
		else
		{
			mTri[2][1].cellType = CellInfo::Type::RED;
			mTri[1][1].cellType = CellInfo::Type::RED;
			mTri[0][1].cellType = CellInfo::Type::RED;
		}
		break;
	case TriominoInfo::Type::VERTICAL:
		if (isBlue == true)
		{
			mTri[1][0].cellType = CellInfo::Type::BLUE;
			mTri[1][1].cellType = CellInfo::Type::BLUE;
			mTri[1][2].cellType = CellInfo::Type::BLUE;
		}
		else
		{
			mTri[1][0].cellType = CellInfo::Type::RED;
			mTri[1][1].cellType = CellInfo::Type::RED;
			mTri[1][2].cellType = CellInfo::Type::RED;
		}
		break;
	}
}

