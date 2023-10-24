/************************************************************************
*	File name : Board.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Sets of cells.
*   This have sprite, position, index and so on.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Cell.h"

template<int WIDTH, int HEIGHT>
class [[nodiscard]] Board
{
public:
    Board() noexcept;
    ~Board() noexcept {}
    void SetSprite(std::shared_ptr<sf::Sprite> a_Sprite) noexcept;
    void UpdateCellPosition() noexcept;
    bool Isput(Vector2 cellIndex, TriominoInfo::Type triType) const noexcept;
    void UpdateCharacter() noexcept;
    void DebugBoardPosition() noexcept;
    CellInfo::Type GetCellType(Vector2 index) const noexcept { return mBoard[index.x][index.y].cellType; }
    void SetCellType(Vector2 cellIndex, TriominoInfo::Type triType, bool isBlue) noexcept;
    Cell GetCell(int r, int c) noexcept { return mBoard[r][c]; }
    bool IsMousePosOnBoard(Vector2 mousePos) noexcept;
    Vector2 MousePosToCellLoction(Vector2 mousePos) noexcept;
    
private:
    Cell mBoard[WIDTH][HEIGHT];
    std::shared_ptr<sf::Sprite> boardSprite;
};
	 
#include "Board.cpp"