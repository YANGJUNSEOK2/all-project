/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: element1.h
Author: junseok.yang
Creation Date:FALL/10/30/2019
    Header file element1 Inheritance AbstractElement,  cs225 assignment3
******************************************************************************/
#ifndef ELEMENT1_H
#define ELEMENT1_H
#include <iostream> // use std::cout
#include "abstract-element.h" // Inheritance AbstractElement
/*
 * A concrete class implementing AbstractElement interface
 * Trivial.
 */
namespace CS225 {

  class Element1 : public AbstractElement {
    public:
      Element1(int _val);
      AbstractElement* clone() const override; // make virtual constructor
      virtual int Get() const override;
      virtual void Set(int new_val) override;
      virtual void Print() const override;
    private:
      int val;
  };
}
#endif
