/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: element1.cpp
Author: junseok.yang
Creation Date:FALL/10/30/2019
    Source file element1 Inheritance AbstractElement,  cs225 assignment3, Adding clone function.
******************************************************************************/
#include "element1.h" // link element1 header

CS225::Element1::Element1(int _val) : val(_val) { }

CS225::AbstractElement* CS225::Element1::clone() const
{
    return new Element1(*this);
} // Element1 clone

int CS225::Element1::Get() const { return val; }

void CS225::Element1::Set(int new_val) { val=new_val; }

void CS225::Element1::Print() const { 
  std::cout << "[" << Get() << "] "; 
}
