/************************************************************************
*	File name : InputManager.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Control mouse and keyboard input
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include <gsl/gsl>
#include <dyn_array.hpp>


class [[nodiscard]] InputManager
{
public:
	InputManager() noexcept {}
	~InputManager() noexcept
	{
		waskeyBoard.~span();
		delete[] keyBoard.heap;
	}
	enum class KeyboardMapping
	{
		_1, _2, _3, _4, _5, _6,
		F1, F2, COUNT,
	};
	enum class MouseMapping
	{
		LEFT,
		RIGHT,
		COUNT,
	};

	void SetKey(KeyboardMapping keyboard, bool isPress) noexcept;
	void Init() noexcept;
	
	bool IsKeyDown(KeyboardMapping key) noexcept;
	bool IsKeyReleased(KeyboardMapping key) noexcept;
	void Update() noexcept;
	
	static dyn_array keyBoard;
	
private:
	gsl::span<bool, static_cast<int>(KeyboardMapping::COUNT)> waskeyBoard{ new bool{false}, static_cast<int>(KeyboardMapping::COUNT) };
};
	