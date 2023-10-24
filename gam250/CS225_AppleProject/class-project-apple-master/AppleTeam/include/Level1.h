/************************************************************************
*	File name : Level1.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Level1 Scene. 8x8 board and can put blocks using mouse but cannot get scores
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "IScene.h"
#include "Board.h"
#include "Triomino.h"

static constexpr int L1WIDTH = 8;
static constexpr int L1HEIGHT = 8;

class [[nodiscard]] Level1 final : public IScene
{
public:
    Level1() noexcept
    {
        lvImage.loadFromFile(Imgpath::CELL);
        lvTexture.loadFromImage(lvImage);
        lvSprite = std::make_shared<sf::Sprite>(sf::Sprite{});
        lvSprite.get()->setTexture(lvTexture);
        lvBoard.SetSprite(lvSprite);
        lvBoard.UpdateCellPosition();
        mTri.SetSprite(lvSprite);
        mTri.UpdateCellPosition();
    }
    ~Level1() noexcept {}
    bool Init() noexcept override;
    void Update(double delta_time) noexcept override;
    void Draw() noexcept override;
    void ShutDown() noexcept override;
    void SetNextScene() noexcept override;
    std::string GetName() const noexcept override;

private:
    std::string levelName = "Level1";
    Board<8, 8> lvBoard;
    Triomino mTri;
    bool isBlue = true;
    int mTurnNum = 0;
    sf::Image lvImage;
    sf::Texture lvTexture;
    std::shared_ptr<sf::Sprite> lvSprite;
    int* i = new int(1);
};