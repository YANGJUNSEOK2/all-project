/************************************************************************
*	File name : MouseInput.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "MouseInput.h"
#include  <iostream>

    MouseInput::MouseInput()
    {
        Mouse_LeftDown = false;
        Mouse_RightDown = false;
        Mouse_WheelDown = false;
        Mouse_LeftClick = false;
        Mouse_RightClick = false;
        Mouse_WheelClick = false;
    }

    void MouseInput::SetMousePos(float x, float y)
    {
        Pos.x = x;
        Pos.y = y;
    }

    Vector2<float> MouseInput::Get_Mouse_Pos() const
    {
        return Pos;
    }


    void MouseInput::Mouse_Clicked(MouseButton Button)
    {
        switch (Button)
        {
        case MouseButton::Left:
        {
            Mouse_LeftDown = false;
            Mouse_LeftClick = true;
        }
        break;
        case MouseButton::Right:
        {
            Mouse_RightDown = false;
            Mouse_RightClick = true;
        }
        break;
        case MouseButton::Wheel:
        {
            Mouse_WheelDown = false;
            Mouse_WheelClick = true;
        }
        break;
        }
    }

    void MouseInput::Mouse_Downed(MouseButton Button)
    {
        switch (Button)
        {
        case MouseButton::Left:
        {
            Mouse_LeftDown = true;
        }
        break;
        case MouseButton::Right:
        {
            Mouse_RightDown = true;
        }
        break;
        case MouseButton::Wheel:
        {
            Mouse_WheelDown = true;
        }
        break;
        }
    }


    bool MouseInput::Is_Mouse_Clicked(MouseButton Button) const
    {
        switch (Button)
        {
        case MouseButton::Left:
        {
            return Mouse_LeftClick;
        }
        break;
        case MouseButton::Right:
        {
            return Mouse_RightClick;
        }
        break;
        case MouseButton::Wheel:
        {
            return Mouse_WheelClick;
        }
        break;
        }
        return false;
    }

    bool MouseInput::Is_Mouse_Downed(MouseButton Button) const
    {
        switch (Button)
        {
        case MouseButton::Left:
        {
            return Mouse_LeftDown;
        }
        break;
        case MouseButton::Right:
        {
            return Mouse_RightDown;
        }
        break;
        case MouseButton::Wheel:
        {
            return Mouse_WheelDown;
        }
        break;
        }
        return false;
    }


    void MouseInput::Mouse_Nothing()
    {
        Mouse_LeftClick = false;
        Mouse_RightClick = false;
        Mouse_WheelClick = false;
    }
