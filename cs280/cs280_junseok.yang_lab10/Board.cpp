/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: board.cpp
Purpose: Source file for Board
Project: AStar (CS280 Programming Final)
Author: junseok yang
Creation date: 2021 06 01
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"

#include "Board.h"
#include "Cell.h"
#include "Image_Anims.h"


Board::Board() : cellSize({ 64,64 }) {}

void Board::Load(std::string fileName) {
	if (fileName.substr(fileName.find_last_of('.')) != ".dat") {
		throw std::runtime_error("Bad Filetype.  " + fileName + " not a sprite info file (.dat)");
	}
	std::ifstream inFile(fileName);
	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + fileName);
	}

	Vector2DInt center = Engine::GetWindow().GetSize() / 2;
	inFile >> boardWidth;
	inFile >> boardHeight;

	/* screenPosition is the xy position for where the cell is located on the screen.  
	This is the bottom left cell. position.  Use cellSize to find the other cell screen positions*/

	Vector2DInt screenPosition = { center.x - cellSize.x * (boardWidth - 1) / 2,
									center.y - cellSize.y * (boardHeight - 1) / 2 };
	// Dynamically create a 2D contiguous array (lab 3) of size boardWidth & boardHeight
	// Initialize each cell of the board using the xyIndex, cell type (read from the file), and screenPosition
	board = reinterpret_cast<Cell**>((Cell*)malloc(boardHeight * sizeof(Cell*) + boardWidth * boardHeight * sizeof(Cell)));
	Cell** cellptr = new(board)(Cell*);
	Cell* arr = new(&cellptr[static_cast<int>(boardHeight)]) Cell({0,0}, '0', screenPosition);
	for (int y = 0; y < static_cast<int>(boardHeight); y++)
	{
		board[y] = &arr[y * static_cast<int>(boardWidth)];
	}
	//////////////////////////////////////////////////////////////
	for (int y = 0; y < static_cast<int>(boardHeight); y++) {
		for (int x = 0; x < static_cast<int>(boardWidth); x++) {
			char frame;
			inFile >> frame;

			if (frame > 1) {
				if (IsClash() == true) {
					aiStartCells.push_back({ x,y });
				}

			}
			//Todo: use an in place new to call the constructor for the board item (Cell needs, screenPos & static_cast<Images>(frame));
			Cell* ptr = new(arr + y * static_cast<int>(boardWidth) + x) Cell({ x,y }, (frame), screenPosition);
			board[y][x] = *ptr;
			/////////////////////////////
			screenPosition.x += cellSize.x;
		}
		screenPosition.x = center.x - cellSize.x * (boardWidth - 1) / 2;
		screenPosition.y += cellSize.y;
	}
}

Board::~Board() {
	// delete the board
	for (int y = 0; y < static_cast<int>(boardHeight); y++) {
		for (int x = 0; x < static_cast<int>(boardWidth); x++) {
			GetCell({ x, y })->~Cell();		// Yes, I am manually calling the destructor.  
											// This wasn't allocated with a standard new, but we want the destructor called
		}
	}
	free(board);
}

void Board::Draw() {
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			board[y][x].Draw();
		}
	}
}

bool Board::IsMousePosOnBoard(Vector2DInt mousePos) {
	if (mousePos.x < GetCell({ 0, 0 })->GetPosition().x - cellSize.x/2) {
		return false;
	}
	if (mousePos.y < GetCell({ 0, 0 })->GetPosition().y - cellSize.y/2) {
		return false;
	}
	if (mousePos.x > GetCell({ boardWidth - 1, boardHeight - 1 })->GetPosition().x + cellSize.x / 2) {
		return false;
	}
	if (mousePos.y > GetCell({ boardWidth - 1, boardHeight - 1 })->GetPosition().y + cellSize.y / 2) {
		return false;
	}
	return true;
}

Vector2DInt Board::MousePosToCellLoction(Vector2DInt mousePos) {
	if (IsMousePosOnBoard(mousePos) == false) {
		Engine::GetLogger().LogError("Mouse pos was in an invalid location");
	}

	Vector2DInt temp = GetCell({ 0, 0 })->GetPosition() - cellSize/2;
	Vector2DInt boardClickLocation = mousePos - temp;

	return { boardClickLocation.x / cellSize.x, boardClickLocation.y / cellSize.y };
}

Cell* Board::GetCell(Vector2DInt location) {
	if (location.x < 0 || location.x >= boardWidth) {
		return nullptr;
	}
	if (location.y < 0 || location.y >= boardHeight) {
		return nullptr;
	}
	return &board[location.y][location.x];
}