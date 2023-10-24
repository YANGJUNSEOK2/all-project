/************************************************************************
*	File name : IScene.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Basis for every Scenes.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include <string>

class [[nodiscard]] IScene
{
public:
    IScene() = default;
    IScene(const IScene&) = default;
    IScene(IScene&&) = default;
    IScene& operator=(const IScene&) = default;
    IScene& operator=(IScene&&) = default;
    virtual ~IScene() = default;
    
    
    virtual bool Init() = 0;
    virtual void Update(double delta_time) = 0;
    virtual void Draw() = 0;
    virtual void ShutDown() = 0;
    virtual void SetNextScene() = 0;
    [[nodiscard]] virtual std::string GetName() const = 0;
};