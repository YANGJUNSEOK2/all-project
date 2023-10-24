
#pragma once

//¸ø¾¸(¾¥·º)
namespace JS_Engine {
    namespace Input {
        enum class MouseInputButton;
        enum class KeyboardInputButton;

        class InputEventHandler
        {
        public:
            virtual void KeyPress(KeyboardInputButton button) = 0;
            virtual void KeyReleased(KeyboardInputButton button) = 0;
            virtual void MouseButtonPress(MouseInputButton button) = 0;
            virtual void MouseButtonReleased(MouseInputButton button) = 0;
            virtual void MouseWheelScroll(int scroll_amount) = 0;
            virtual void MouseMove(int mouse_x, int mouse_y) = 0;
        };

    }
}