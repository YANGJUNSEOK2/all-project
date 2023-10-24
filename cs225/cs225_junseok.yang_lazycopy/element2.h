/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: element2.h
Author: junseok.yang
Creation Date:FALL/10/30/2019
    Header file element2 Inheritance AbstractElement,  cs225 assignment3
******************************************************************************/
#ifndef ELEMENT2_H
#define ELEMENT2_H
#include <iostream> // use std::cout
#include "abstract-element.h" // Inheritance AbstractElement

/*
 * A concrete class implementing AbstractElement interface
 * Uses dynamically allocated data.
 */
namespace CS225 {

  class Element2 : public AbstractElement {
    public:
      Element2(int _val);
      Element2(const Element2& rhs);
      AbstractElement*clone() const override; // make virtual constructor
      Element2& operator=(const Element2& rhs);
      virtual int Get() const override;
      virtual void Set(int new_val) override;
      virtual void Print() const override;
      virtual ~Element2();
    private:
      int * p_val;
  };

}
#endif
