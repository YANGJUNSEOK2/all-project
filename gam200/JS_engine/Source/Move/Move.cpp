#include "Move.hpp"
namespace JS_Engine {
    namespace MoveSystem {


        void Move::Init()
        {
            m_Moving = MathLibrary::Vector2(0, 0);
        }

        MathLibrary::Vector2 Move::GetMoving() const
        {
            return m_Moving;
        }

        void Move::SetMoving(const MathLibrary::Vector2 p_Moving)
        {
            m_Moving = p_Moving;
        }
    }
}
