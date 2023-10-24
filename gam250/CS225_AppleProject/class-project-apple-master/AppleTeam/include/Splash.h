/************************************************************************
*	File name : Splash.h
*	Project name : apple
*   Author	    Primary author : Junseok Yang
*			    Secondary author : Seungguk Jang
*	File description : Splash Scene
*	2021 summer Semester cs225 class project
*************************************************************************/
#include "IScene.h"
#include <string>
#include "Window.h"
class [[nodiscard]] Splash final : public IScene
{
public:
    Splash() = default;
    bool Init()  noexcept override;
    void Update(double delta_time) noexcept override;
    void Draw() noexcept override;
    void ShutDown() noexcept override;
    void SetNextScene() noexcept override;
    std::string GetName() const noexcept override;

private:
    std::string levelName = "Splash";

    sf::Texture heroTexture;
    sf::Texture platformTexture;
    sf::Texture digipenTexture;
    sf::Sprite heroSprite;
    sf::Sprite platformSprite;
    sf::Sprite digipenSprite;

    bool splashVisible = true;

    struct [[nodiscard]] Position
    {
        float x;
        float y;
    };

    Position heroPos;
    Position platformPos;

    int index = 0;
    float frame = 0.f;
    float frameSpeed = 0.1f;
    const int changeCount = 5;

    const float gravity = 0.1f;
    bool isJumping = false;
    bool isBottom = true;

    const float platformSpeed = 0.1f;

    float HERO_Y_BOTTOM = (float)(550 - heroTexture.getSize().y);
    float PLATFORM_Y_BOTTOM = (float)(550 - platformTexture.getSize().y);
};