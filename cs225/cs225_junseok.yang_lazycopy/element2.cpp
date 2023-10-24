/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: element2.cpp
Author: junseok.yang
Creation Date:FALL/10/30/2019
    Source file element2 Inheritance AbstractElement,  cs225 assignment3, Adding clone function.
******************************************************************************/
#include "element2.h" // link element2 header

CS225::Element2::Element2(int _val) : p_val(new int(_val)) { }

CS225::Element2::Element2(const Element2& rhs) 
	: AbstractElement(), p_val(new int(*rhs.p_val)) 
{ }

CS225::AbstractElement* CS225::Element2::clone() const
{
    return new Element2(*this);
} // Element2 clone

CS225::Element2& CS225::Element2::operator=(const Element2& rhs) {
  if (this!=&rhs) {
		delete p_val;
		p_val = new int(*rhs.p_val);
	} 
  return *this;
}

int CS225::Element2::Get() const {
	return *p_val;
}

void CS225::Element2::Print() const { 
  std::cout << "(" << *p_val << ") "; 
}

void CS225::Element2::Set(int new_val) { 
	*p_val = new_val; 
}

CS225::Element2::~Element2() {
	delete p_val;
}
