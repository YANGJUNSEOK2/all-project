/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: array.h
Author: junseok.yang
Creation Date:FALL/10/30/2019
    Header file Array,  cs225 assignment3, Make the ~Array() and  operator=.
******************************************************************************/
#ifndef ARRAY_H
#define ARRAY_H
#include "abstract-element.h" // link abstract-element
#include "element-factory.h" // link element-factory
#include <iostream> // use std::cout

namespace CS225 {

/*
 * Class Array implements a simple array-like data structure.
 * Objects inside the Array have to be derived from AbstractElement.
 */
	class Array {
		public:
			Array(int * array, unsigned int _size, 
					const ElementFactory* _pElementFactory
					);

            Array(const Array & array);

            ~Array();

			int Get(unsigned int pos) const;

			void Set(int id, int pos, int value);

			void Print() const;

            Array &operator=(const Array& rhs);

	protected:
            void DeleteData(); // helper function

            void DeepCopy(); // helper function

		private:
			AbstractElement** data;
			unsigned int size;
			const ElementFactory* pElementFactory;
            int* m_Shared; // reference counting
	};
}
#endif
