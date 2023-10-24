/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: abstract_element.h
Author: junseok.yang
Creation Date:FALL/10/30/2019
    Header file abstract_element Inheritance ObjectCounter,  cs225 assignment3, 
    Make the clone function, Please override when making element 3.
******************************************************************************/
#pragma once
#include "CRTP.h" //Inheritance ObjectCounter

namespace CS225 {
    class AbstractElement :public ObjectCounter<AbstractElement>
    {
    public:
        virtual AbstractElement* clone() const = 0; // make virtual constructor
        virtual int Get() const = 0;
        virtual void Set(int new_val) = 0;
        virtual void Print() const = 0;
    };
}

