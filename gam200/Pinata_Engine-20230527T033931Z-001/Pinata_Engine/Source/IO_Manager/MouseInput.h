#pragma once
#include "../MathLibrary/Vector2.hpp"

    enum MouseButton
    {
        Left,
        Right,
        Wheel
    };

    class MouseInput
    {
    public:
        MouseInput();
        ~MouseInput() = default;
        void SetMousePos(float x, float y);
        Vector2<float> Get_Mouse_Pos() const;

        void Mouse_Clicked(MouseButton Button);
        void Mouse_Downed(MouseButton Button);

        bool Is_Mouse_Clicked(MouseButton Button) const;
        bool Is_Mouse_Downed(MouseButton Button) const;

        void Mouse_Nothing();

    private:
        Vector2<float> Pos;
        bool Mouse_RightDown;
        bool Mouse_LeftDown;
        bool Mouse_WheelDown;
        bool Mouse_LeftClick;
        bool Mouse_RightClick;
        bool Mouse_WheelClick;
    };
