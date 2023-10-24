#pragma once
#include <glew.h>
#include "../../MathLibrary/MathLibrary.hpp"
#include "Render.hpp"

namespace JS_Engine {
    namespace Graphics {
        class Renderer {
        public:
            //Submit Renderer
            virtual void SubmitRenderer(const Render *p_Render) = 0;
            //Flush Renderer
            virtual void FlushRenderer() = 0;
            //Begin Renderer
            virtual void BeginRenderer() { }
            //End Renderer
            virtual void EndRenderer() { }
            //Push Stack
            void PushStack(const MathLibrary::Matrix &p_Matrix, bool p_Override = false)
            {
                if(p_Override)
                {
                    m_Stack.push_back(p_Matrix);
                }
                else
                {
                    m_Stack.push_back(m_Stack.back()*p_Matrix);
                }
                m_StackBack = &m_Stack.back();
            }
            //Pop Stack
            void PopStack()
            {
                if(m_Stack.size()>1)
                {
                    m_Stack.pop_back();
                }
                m_StackBack = &m_Stack.back();
            }
        protected:
            std::vector<MathLibrary::Matrix> m_Stack;
            const MathLibrary::Matrix *m_StackBack;

            Renderer()
            {
                m_Stack.push_back(MathLibrary::Matrix::Identiy());
                m_StackBack = &m_Stack.back();
            }
        };
    }
}