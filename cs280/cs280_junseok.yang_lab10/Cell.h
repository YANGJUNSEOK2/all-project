/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cell.h
Purpose: header file for cell
Project: AStar (CS280 Programming Final)
Author: junseok yang
Creation date: 2021 06 01
-----------------------------------------------------------------*/
#pragma once

#include "../Engine/Heap.h"
#include "..\Engine\BasicDataTypes.h"

class Sprite;
enum class Images;

class Cell {
public:
	friend std::ostream& operator<<(std::ostream& out, Cell*& cell);

	Cell(Vector2DInt xyIndex, char type, Vector2DInt screenPosition);
	virtual ~Cell();
	Vector2DInt GetPosition();
	void Draw();
	void SetToImage(Images image);
	Images GetImage();

	unsigned int GetGCost();
	unsigned int GetFCost();
	unsigned int GetHCost();
	Vector2DInt GetXYIndex();

	Vector2DInt GetParent_xyIndex();
	// You may add additional functions
	void CalculateAstarVariables(Cell* parent, Cell* selected, Heap<Cell*>* visit);
	void SetGCost(unsigned int rhs) { gCost = rhs; }
	void SetFCost(unsigned int rhs) { fCost = rhs; }
	void SetHCost(unsigned int rhs) { hCost = rhs; }
	void SetPosition(Vector2DInt screenPos) { screenPosition = screenPos; }
	void SetXYIndex(Vector2DInt XYIndex) { xyIndex = XYIndex; }
	void SetParent_xyIndex(Vector2DInt Parent_xyIndex) { parent_xyIndex = Parent_xyIndex; }

	Cell* GetPnext() { return pNext; }
	void SetPnext(Cell* next) { pNext = next; }
private:
	Vector2DInt xyIndex;
	Vector2DInt parent_xyIndex;
	Vector2DInt screenPosition;
	Sprite* sprite;

	unsigned int gCost;
	unsigned int fCost;
	unsigned int hCost;
	Cell* pNext;
	// You may add member variables
};