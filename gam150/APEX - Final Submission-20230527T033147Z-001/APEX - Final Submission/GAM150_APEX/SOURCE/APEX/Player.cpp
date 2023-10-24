/************************************************************************
*	File name : Player.cpp
*	Project name : APEX
*	Author	    Primary author : Haewon Shon
*			        Secondary author : Jookyung Lee
*			        Others : Junseok Yang, Wonju Cho
*			        
*			        All Functions for Player Class, 
*			        Including Creating/Moving/Animation/Item effect
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "Player.h"
#include "Domination.h"
#include <engine/State.h>
#include <engine/Object.h>

void Player::Jump()
{
    if (object.customPhysics.GetVelocity().y == 0)
    {
        object.customPhysics.SetVelocity(object.customPhysics.GetVelocity().x, 32.f);
    }
}

void Player::DownJump()
{
    if (object.customPhysics.GetVelocity().y == 0)
    {
        downDelay = 0.5f;
        object.customPhysics.SetVelocity(0.f, -15.f);
    }
}

void Player::Attack()
{
    float xDistance = abs(object.transform.position.x - opponent->object.transform.position.x);
    float yDistance = abs(object.transform.position.y - opponent->object.transform.position.y);

    if (xDistance < characterStatus.reach && yDistance < 80)
    {
        if (object.transform.position.x >= opponent->object.transform.position.x && characterDirection == Player::Direction::LEFT)
        {
            opponent->object.customPhysics.AddForce(-characterStatus.power, 0.0f);
            opponent->knockbackDelay = opponent->characterStatus.knockbackDefault;
        }

        if (object.transform.position.x <= opponent->object.transform.position.x && characterDirection == Player::Direction::RIGHT)
        {
            opponent->object.customPhysics.AddForce(characterStatus.power, 0.0f);
            opponent->knockbackDelay = opponent->characterStatus.knockbackDefault;
        }
    }

    isAttack = true;
    attackDelay = characterStatus.attackDefault;
    object.customPhysics.SetVelocity(object.customPhysics.GetVelocity());
}

void Player::PlayerMovement(float dt)
{
    if (knockbackDelay <= 0)
    {
        if (State::m_input->IsPressed(controller.right))
        {
            status = Player::Status::RIGHT_WALK;
            characterDirection = Player::Direction::RIGHT;
            object.customPhysics.SetVelocity(dt * characterStatus.speed, object.customPhysics.GetVelocity().y);
        }

        if (State::m_input->IsPressed(controller.left))
        {
            status = Player::Status::LEFT_WALK;
            characterDirection = Player::Direction::LEFT;
            object.customPhysics.SetVelocity(-dt * characterStatus.speed, object.customPhysics.GetVelocity().y);
        }

        if (State::m_input->IsReleased(controller.right))
        {
            status = Player::Status::RIGHT_STAND;
            object.customPhysics.SetVelocity(0, object.customPhysics.GetVelocity().y);
        }

        if (State::m_input->IsReleased(controller.left))
        {
            status = Player::Status::LEFT_STAND;
            object.customPhysics.SetVelocity(0, object.customPhysics.GetVelocity().y);
        }

        if (State::m_input->IsTriggered((controller.jump)))
        {
            Jump();
        }

        if (State::m_input->IsTriggered((controller.jump_down)))
        {
            DownJump();
        }

        //Attacking
        if (State::m_input->IsTriggered((controller.attack)) && attackDelay < 0.f)
        {
            Attack();
        }
    }
}

void Player::SetPlayerMovingAndStatus(float dt)
{
    // if player is stiking side of the platform, give ghost collision for a moment
    if(isStickSide == true)
    {
        downDelay = 0.1f;
    }
    // Ghost collision when jump
    if (object.customPhysics.GetVelocity().y < 0)
    {
        object.customPhysics.ActiveGhostCollision(true);
    }
    if (object.customPhysics.GetVelocity().y > 0 || downDelay > 0.f)
    {
        object.customPhysics.ActiveGhostCollision(false);
    }

    // knock-back part
    if (knockbackDelay < 0.3f && knockbackDelay > 0.f)
    {
        if (knockbackDelay < 0.05f)
        {
            if (object.customPhysics.GetVelocity().x > 0)
            {
                object.customPhysics.AddForce(-8.f, 0.f);
            }
            if (object.customPhysics.GetVelocity().x < 0)
            {
                object.customPhysics.AddForce(8.f, 0.f);
            }
        }
        else if (knockbackDelay < 0.1f)
        {
            if (object.customPhysics.GetVelocity().x > 0)
            {
                object.customPhysics.AddForce(-5.f, 0.f);
            }
            if (object.customPhysics.GetVelocity().x < 0)
            {
                object.customPhysics.AddForce(5.f, 0.f);
            }
        }
        else
        {

            if (object.customPhysics.GetVelocity().x > 0)
            {
                object.customPhysics.AddForce(-3.f, 0.f);
            }
            if (object.customPhysics.GetVelocity().x < 0)
            {
                object.customPhysics.AddForce(3.f, 0.f);
            }
        }
    }

    // Set status based on direction and prev status
    if (status != Player::Status::WIN)
    {
        if (attackDelay > 0 && characterDirection == Player::Direction::LEFT)
        {
            status = Player::Status::LEFT_ATTACK;
        }
        else if (attackDelay > 0 && characterDirection == Player::Direction::RIGHT)
        {
            status = Player::Status::RIGHT_ATTACK;
        }
        else
        {
            if (characterDirection == Player::Direction::LEFT && object.customPhysics.GetVelocity().x == 0)
            {
                status = Player::Status::LEFT_STAND;
            }
            if (characterDirection == Player::Direction::RIGHT && object.customPhysics.GetVelocity().x == 0)
            {
                status = Player::Status::RIGHT_STAND;
            }
        }
    }
    else
    {
        object.customPhysics.SetVelocity(0.f, 0.f);
    }
    

    // Remove item effect if duration finished
    if(itemDuration < 0.f)
    {
        switch(character)
        {
        case 1: characterStatus = junseok; break;
        case 2: characterStatus = jookyung; break;
        case 3: characterStatus = wonju; break;
        case 4: characterStatus = haewon; break;
        }
    }

    respawnTime -= dt;
    trapCoolDown -= dt;
    knockbackDelay -= dt;
    attackDelay -= dt;
    downDelay -= dt;
    itemDuration -= dt;
}
void Player::CreatePlayerObject(Player* other, b2Vec2 startingPos, int id, int playerNum)
{
    // Set the object's unique name
    object.SetName("player");
    // Set the position of the object
    object.transform.position.Set(startingPos.x, startingPos.y, 0.0f);
    // Set the scale of the object
    object.transform.SetScale(50.f, 100.f);
    // Set the colors r,g,b,a (0~255)
    object.sprite.color = SDL_Color{ 255, 255, 255, 255 };

    status = Status::LEFT_STAND;
    characterDirection = Direction::LEFT;
    itemDuration = 0.f;

    // set controller
    if (playerNum == 1)
    {
        controller.left = SDL_SCANCODE_A;
        controller.right = SDL_SCANCODE_D;
        controller.jump = SDL_SCANCODE_W;
        controller.attack = SDL_SCANCODE_H;
        controller.jump_down = SDL_SCANCODE_S;
    }
    if (playerNum == 2)
    {
        controller.left = SDL_SCANCODE_LEFT;
        controller.right = SDL_SCANCODE_RIGHT;
        controller.jump = SDL_SCANCODE_UP;
        controller.attack = SDL_SCANCODE_KP_2;
        controller.jump_down = SDL_SCANCODE_DOWN;
    }

    if (id == 1) // junseok
    {
        character = 1;
        object.sprite.activeAnimation = false;
        object.sprite.LoadImage("texture/character/junseok.png", State::m_renderer);

        characterStatus = junseok;

        leftStandFile = "texture/character/waiting/left_junseok_waiting.png";
        rightStandFile = "texture/character/waiting/right_junseok_waiting.png";
        leftWalkFile = "texture/character/walking/left_junseok_walking.png";
        rightWalkFile = "texture/character/walking/right_junseok_walking.png";
        leftAttackFile = "texture/character/attack/left_junseok_attack.png";
        rightAttackFile = "texture/character/attack/right_junseok_attack.png";
        winFile = "texture/character/win/junseok_win.png";
        leftEffectFile = "texture/character/attack_effect/left_junseok_effect.png";
        rightEffectFile = "texture/character/attack_effect/right_junseok_effect.png  ";
    }

    else if (id == 2) // jookyung
    {
        character = 2;
        object.sprite.activeAnimation = false;
        object.sprite.LoadImage("texture/character/jookyung.png", State::m_renderer);

        characterStatus = jookyung;

        leftStandFile = "texture/character/waiting/left_jookyung_waiting.png";
        rightStandFile = "texture/character/waiting/right_jookyung_waiting.png";
        leftWalkFile = "texture/character/walking/left_jookyung_walking.png";
        rightWalkFile = "texture/character/walking/right_jookyung_walking.png";
        leftAttackFile = "texture/character/attack/left_jookyung_attack.png";
        rightAttackFile = "texture/character/attack/right_jookyung_attack.png";
        winFile = "texture/character/win/jookyung_win.png";
        leftEffectFile = "texture/character/attack_effect/left_jookyung_effect.png";
        rightEffectFile = "texture/character/attack_effect/right_jookyung_effect.png";
    }

    else if (id == 3) // wonju
    {
        character = 3;
        object.sprite.activeAnimation = false;
        object.sprite.LoadImage("texture/character/wonju.png", State::m_renderer);

        characterStatus = wonju;

        leftStandFile = "texture/character/waiting/left_wonju_waiting.png";
        rightStandFile = "texture/character/waiting/right_wonju_waiting.png";
        leftWalkFile = "texture/character/walking/left_wonju_walking.png";
        rightWalkFile = "texture/character/walking/right_wonju_walking.png";
        leftAttackFile = "texture/character/attack/left_wonju_attack.png";
        rightAttackFile = "texture/character/attack/right_wonju_attack.png";
        winFile = "texture/character/win/wonju_win.png";
        leftEffectFile = "texture/character/attack_effect/left_wonju_effect.png";
        rightEffectFile = "texture/character/attack_effect/right_wonju_effect.png";
    }

    else if (id == 4) // haewon
    {
        character = 4;
        object.sprite.activeAnimation = false;
        object.sprite.LoadImage("texture/character/haewon.png", State::m_renderer);

        characterStatus = haewon;

        leftStandFile = "texture/character/waiting/left_haewon_waiting.png";
        rightStandFile = "texture/character/waiting/right_haewon_waiting.png";
        leftWalkFile = "texture/character/walking/left_haewon_walking.png";
        rightWalkFile = "texture/character/walking/right_haewon_walking.png";
        leftAttackFile = "texture/character/attack/left_haewon_attack.png";
        rightAttackFile = "texture/character/attack/right_haewon_attack.png";
        winFile = "texture/character/win/haewon_win.png";
        leftEffectFile = "texture/character/attack_effect/left_haewon_effect.png";
        rightEffectFile = "texture/character/attack_effect/right_haewon_effect.png";
    }


    //* Here we predefine some info to create a body
    // Connect transform to the pointer
    object.customPhysics.pOwnerTransform = &object.transform;
    // Set body type (either DYNAMIC or STATIC)
    object.customPhysics.bodyType = CustomPhysics::DYNAMIC;
    //player.customPhysics.GetBody()->SetType(b2_staticBody);
    // Set body shape
    object.customPhysics.bodyShape = CustomPhysics::BOX;
    object.customPhysics.radius = 12;
    // Allocate body passing world
    // Set restitution
    object.customPhysics.SetRestitution(0);

    opponent = other;
}

void Player::SetCollisionMoving()
{
    if (object.customPhysics.IsCollidingWith(&opponent->object))
    {
        object.customPhysics.ActiveGhostCollision(true);
    }
}

void Player::AnimationUpdate(float /*dt*/)
{
    // based on controller's state, change current sprite to proper one
    if (prevStatus != status)
    {
        object.sprite.Free();
        switch (status)
        {
        case Status::LEFT_STAND:
            switch (character)
            {
            case 2:
                object.transform.SetScale(70.f, 100.f);
                break;
            case 3:
                object.transform.SetScale(70.f, 100.f);
                break;
            case 4:
                object.transform.SetScale(70.f, 100.f);
                break;
            default:
                object.transform.SetScale(100.f, 100.f);
            }
            object.sprite.LoadImage(leftStandFile, State::m_renderer);
            object.sprite.activeAnimation = true;
            object.sprite.SetFrame(2);
            object.sprite.SetSpeed(12.f);
            break;
        case Status::RIGHT_STAND:
            switch (character)
            {
            case 2:
                object.transform.SetScale(70.f, 100.f);
                break;
            case 3:
                object.transform.SetScale(70.f, 100.f);
                break;
            case 4:
                object.transform.SetScale(80.f, 100.f);
                break;
            default:
                object.transform.SetScale(100.f, 100.f);
            }
            object.sprite.LoadImage(rightStandFile, State::m_renderer);
            object.sprite.activeAnimation = true;
            object.sprite.SetFrame(2);
            object.sprite.SetSpeed(12.f);
            break;
        case Status::LEFT_WALK:
            switch (character)
            {
            case 1:
                object.transform.SetScale(60.f, 100.f);
                break;
            case 2:
                object.transform.SetScale(50.f, 100.f);
                break;
            case 3:
                object.transform.SetScale(60.f, 100.f);
                break;
            case 4:
                object.transform.SetScale(60.f, 100.f);
                break;
            default:
                object.transform.SetScale(70.f, 100.f);
            }
            object.sprite.LoadImage(leftWalkFile, State::m_renderer);
            object.sprite.activeAnimation = true;
            object.sprite.SetFrame(4);
            object.sprite.SetSpeed(12.f);
            break;
        case Status::RIGHT_WALK:
            switch (character)
            {
            case 1:
                object.transform.SetScale(60.f, 100.f);
                break;
            case 2:
                object.transform.SetScale(50.f, 100.f);
                break;
            case 3:
                object.transform.SetScale(60.f, 100.f);
                break;
            case 4:
                object.transform.SetScale(60.f, 100.f);
                break;
            default:
                object.transform.SetScale(70.f, 100.f);
            }
            object.sprite.LoadImage(rightWalkFile, State::m_renderer);
            object.sprite.activeAnimation = true;
            object.sprite.SetFrame(4);
            object.sprite.SetSpeed(12.f);
            break;
        case Status::LEFT_ATTACK:
            switch (character)
            {
            case 1:
                object.transform.SetScale(100.f, 100.f);
                break;
            case 2:
                object.transform.SetScale(80.f, 100.f);
                break;
            case 3:
                object.transform.SetScale(80.f, 100.f);
                break;
            case 4:
                object.transform.SetScale(80.f, 100.f);
                break;
            default:
                object.transform.SetScale(100.f, 100.f);
            }
            object.sprite.LoadImage(leftAttackFile, State::m_renderer);
            object.sprite.activeAnimation = true;
            object.sprite.SetFrame(4);
            object.sprite.SetSpeed(4.f / characterStatus.attackDefault);
            break;
        case Status::RIGHT_ATTACK:
            switch (character)
            {
            case 1:
                object.transform.SetScale(100.f, 100.f);
                break;
            case 2:
                object.transform.SetScale(80.f, 100.f);
                break;
            case 3:
                object.transform.SetScale(80.f, 100.f);
                break;
            case 4:
                object.transform.SetScale(80.f, 100.f);
                break;
            default:
                object.transform.SetScale(100.f, 100.f);
            }
            object.sprite.LoadImage(rightAttackFile, State::m_renderer);
            object.sprite.activeAnimation = true;
            object.sprite.SetFrame(4);
            object.sprite.SetSpeed(4.f / characterStatus.attackDefault);
            break;
        case Status::WIN:
            object.transform.SetScale(100.f, 100.f);
            object.sprite.LoadImage(winFile, State::m_renderer);
            object.sprite.activeAnimation = true;
            if(character == 4)
            {
                object.sprite.SetFrame(2);
            }
            else
            {
                object.sprite.SetFrame(3);
            }
            object.sprite.SetSpeed(12.f);
            break;
        default:
            break;
        }
        prevStatus = status;
    }
}

void Player::AllocateBody(b2World* world)
{
    object.customPhysics.AllocateBody(world);
}

void Player::AddSpeed(float value)
{
    characterStatus.speed += value;
    if (characterStatus.speed > 2000.f)
    {
        characterStatus.speed = 2000.f;
    }
    if (characterStatus.speed < 600.f)
    {
        characterStatus.speed = 600.f;
    }
    itemName = std::move("SpeedUp");
}

void Player::AddPower(float value)
{
    characterStatus.power += value;
    if (characterStatus.power > 70.f)
    {
        characterStatus.power = 70.f;
    }
    if (characterStatus.power < 30.f)
    {
        characterStatus.power = 30.f;
    }
    itemName = std::move("PowerUp");
}

void Player::AddStance(float value)
{
    characterStatus.knockbackDefault -= value;
    if (characterStatus.knockbackDefault < 0.2f)
    {
        characterStatus.knockbackDefault = 0.2f;
    }
    itemName = std::move("StanceUp");
}