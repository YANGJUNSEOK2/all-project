/************************************************************************
*	File name : Tutorial.cpp
*	Project name : APEX
*	Author	    Primary author : Wonju cho
*	        			Secondary author : Junseok Yang
*	        			Others : Haewon Shon, Jookyung Lee
*	        			
*	        			Functions for Tutorial Level
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "Tutorial.h"
#include "CommonLevel.h"
#include "Utils.h"

void TutorialLevel::Initialize()
{
	m_backgroundColor.r = 255, m_backgroundColor.g = 255,
		m_backgroundColor.b = 255;

	camera.position.Set(0.f, 0.f, 150.f);

	m_useBuiltInPhysics = false;

	mainFont = TTF_OpenFont("font/JaykopDot.ttf", 256);

	b2Vec2 gravity(0.f, -40.f);
	SetCustomPhysicsWorld(gravity);

	Create_UI();
    CreateCommonUI();
	GeneratePlatform(300.f, 0.f, 2500.f, 30.f, 0);
	GeneratePlatform(300.f, -150.f, 2500.f, 30.f, 1);

	player1.CreatePlayerObject(&player2, { -100.f, 350.f }, m_game->p1Character, 1);
	player2.CreatePlayerObject(&player1, { 100.f, 350.f }, m_game->p2Character, 2);

	player1.AllocateBody(GetCustomPhysicsWorld());
	AddObject(&player1.GetObject());
	AddCustomPhysicsComponent(&player1.GetObject());
	player2.AllocateBody(GetCustomPhysicsWorld());
	AddObject(&player2.GetObject());
	AddCustomPhysicsComponent(&player2.GetObject());

    trap.SetName("trap");
    trap.sound.LoadSound("sound/put_trap.wav");
    tutorialBeeb.SetName("tutorialBeeb");
    tutorialBeeb.sound.LoadSound("sound/menu_move.wav");
    tutorialSound.SetName("tutorialSound");
    tutorialSound.sound.LoadSound("sound/tutorial.wav");
    tutorialSound.sound.Play();
    hitsound.sound.LoadSound("sound/hit_sound.wav");

	playTime = 0.f;

}

void TutorialLevel::Update(float dt)
{
    /* pause */
    if (m_input->IsTriggered(SDL_SCANCODE_ESCAPE))
    {
        m_game->Pause();
    }

    /* CHEAT : SKIP TUTORIAL */
    if (m_input->IsTriggered(SDL_SCANCODE_BACKSPACE))
    {
        m_game->Change(LV_ModeSelect);
    }

	/* Player move control */
	player1.PlayerMovement(dt);
	player2.PlayerMovement(dt);
	player1.SetPlayerMovingAndStatus(dt);
	player2.SetPlayerMovingAndStatus(dt);
	player1.SetCollisionMoving();
	player2.SetCollisionMoving();
    CheckRespawn();

	/* Character's animation & effect */
	player1.AnimationUpdate(dt);
	player2.AnimationUpdate(dt);
	AttackEffect(player1, dt);
	AttackEffect(player2, dt);

	CheckTrapCollision();
	CheckSetTrap();
    TrapCooldownAnimation(dt);
    
    Print();

	playTime += dt;
	UpdateCustomPhysics(dt);
	Render(dt);
}

void TutorialLevel::Close()
{
    /* Reset Infos */
    tutorial_p1 = 0, tutorial_p2 = 0;
    w_moveCheck = 0, a_moveCheck = 0, s_moveCheck = 0, d_moveCheck = 0,
    right_moveCheck = 0, left_moveCheck = 0, up_moveCheck = 0, down_moveCheck = 0,
    p1_attackCheck = 0, p2_attackCheck = 0,
    p1_trapCheck = 0, p2_trapCheck = 0,
    pauseCheck = 0;

	RemoveObject(&key_h);
	RemoveObject(&key_j);
	RemoveObject(&hitsound);
	RemoveObject(&numpad2);
	RemoveObject(&numpad3);
	RemoveObject(&p1_movekey);
	RemoveObject(&p2_movekey);
    RemoveObject(&move_text);
    RemoveObject(&attack_text);
    RemoveObject(&trap_text);
    RemoveObject(&next_text);
    RemoveObject(&shoes_explain);
    RemoveObject(&strong_explain);
    RemoveObject(&superarmor_explain);
    RemoveObject(&shoes);
    RemoveObject(&strong);
    RemoveObject(&superarmor);

    RemoveObject(&p1);
    RemoveObject(&p2);
    RemoveObject(&p1_trapImage);
    RemoveObject(&p2_trapImage);
    RemoveObject(&p1_trapcooldown_ui);
    RemoveObject(&p2_trapcooldown_ui);
    RemoveObject(&p1_respawnText);
    RemoveObject(&p2_respawnText);
    RemoveObject(&p1_score_1);
    RemoveObject(&p1_score_2);
    RemoveObject(&p2_score_1);
    RemoveObject(&p2_score_2);

    tutorialSound.sound.Free();
    tutorialBeeb.sound.Free();
    trap.sound.Free();
    RemoveObject(&tutorialBeeb);
    RemoveObject(&tutorialSound);
    RemoveObject(&trap);
    
    player1.effect.sprite.Free();
	RemoveObject(&player1.effect);
	
    player2.effect.sprite.Free();
	RemoveObject(&player2.effect);
	/* Remove "custom" objects */
	RemoveCustomPhysicsWorld();
	// Wrap up state
	ClearBaseState();
}

void TutorialLevel::GeneratePlatform(float posX, float posY, float sizeX, float sizeY, int platformNumber)
{
	platform[platformNumber].SetName("platform");
	platform[platformNumber].transform.position.Set(posX, posY, 0.f);
	platform[platformNumber].transform.SetScale(sizeX, sizeY);
	// Set the rotation of the object
	platform[platformNumber].transform.rotation = 0;
	platform[platformNumber].sprite.color = SDL_Color{ 255, 255, 255, 255 };
	platform[platformNumber].sprite.LoadImage("texture/platform_image/long_platformer.png", m_renderer);

	platform[platformNumber].customPhysics.pOwnerTransform = &platform[platformNumber].transform;
	platform[platformNumber].customPhysics.bodyType = CustomPhysics::STATIC;
	platform[platformNumber].customPhysics.AllocateBody(GetCustomPhysicsWorld());

	AddObject(&platform[platformNumber]);
	AddCustomPhysicsComponent(&platform[platformNumber]);
}

/*
* Basic Functions
*/
void TutorialLevel::SelectText(Object *textObject, const char *textContents, const char *id, SDL_Color color)
{
	// Set the object's name
	textObject->SetName(id);

	// Set the scale of the object
	textObject->transform.SetScale(550, 50);

	// Set the text to render out
	textObject->text.SetText(State::m_renderer, textContents, mainFont);

	// Set the colors r,g,b,a (0~255)
	textObject->text.color = color;

	// Set either if the object to be hud or not
	textObject->text.isHud = true;

	// Register the object to the state
	AddObject(textObject);
}

void TutorialLevel::Create_UI()
{
	move_text.transform.position.Set(0.f, 300.f, 1.f);
	SelectText(&move_text, "Press movement key.", "up_w", { 0,0,0,255 });
	
	if (w_moveCheck + up_moveCheck == 2)
	{
		RemoveObject(&move_text);
	}

	p1_movekey.sprite.Free();
	p1_movekey.SetName("p1_key_explain");
	p1_movekey.transform.position.Set(-600.f, 150.f, 0.f);
	p1_movekey.transform.SetScale(210, 140.f);  
	p1_movekey.transform.rotation = 0;
	p1_movekey.sprite.color = SDL_Color{ 255,255,255,255 };
	p1_movekey.sprite.LoadImage("texture/UI/keyboard/wasd_keyboard.png", m_renderer);
	AddObject(&p1_movekey);

	p2_movekey.sprite.Free();
	p2_movekey.SetName("p2_key_explain");
	p2_movekey.transform.position.Set(150.f, 150.f, 0.f);
	p2_movekey.transform.SetScale(210.f, 140.f);
	p2_movekey.transform.rotation = 0;
	p2_movekey.sprite.color = SDL_Color{ 255,255,255,255 };
	p2_movekey.sprite.LoadImage("texture/UI/keyboard/keyboard.png", m_renderer);
	AddObject(&p2_movekey);


    shoes_explain.transform.position.Set(-450.f, -300.f, 1.f);
    SelectText(&shoes_explain, "This item makes player faster", "fast", { 0,0,0,255 });
    shoes_explain.transform.SetScale(300.f, 50.f);
    
    shoes.transform.position.Set(-650.f, -270.f, 0.f);
    shoes.transform.SetScale(100.f, 150.f);
    shoes.sprite.LoadImage("texture/items/Shoes.png", State::m_renderer);
    AddObject(&shoes);


    strong_explain.transform.position.Set(-100.f, -300.f, 1.f);
    SelectText(&strong_explain, "This item makes player more stronger", "fast", { 0,0,0,255 });
    strong_explain.transform.SetScale(300.f, 50.f);
    
    strong.transform.position.Set(-150.f, -270.f, 0.f);
    strong.transform.SetScale(100.f, 150.f);
    strong.sprite.LoadImage("texture/items/strong.png", State::m_renderer);
    AddObject(&strong);


    superarmor_explain.transform.position.Set(250.f, -300.f, 1.f);
    SelectText(&superarmor_explain, "This item makes player faster", "fast", { 0,0,0,255 });
    superarmor_explain.transform.SetScale(300.f, 50.f);
    
    superarmor.transform.position.Set(350.f, -270.f, 0.f);
    superarmor.transform.SetScale(100.f, 150.f);
    superarmor.sprite.LoadImage("texture/items/superarmor.png", State::m_renderer);
    AddObject(&superarmor);
}

void TutorialLevel::Print()
{
    if(m_input->IsTriggered(SDL_SCANCODE_W))
    {
        tutorialBeeb.sound.Play();
        p1_movekey.sprite.Free();
        p1_movekey.sprite.LoadImage("texture/UI/keyboard/w_pressed.png", m_renderer);
    }
	else if (m_input->IsReleased(SDL_SCANCODE_W))
	{
		w_moveCheck = 1;
        p1_movekey.sprite.Free();
        p1_movekey.sprite.LoadImage("texture/UI/keyboard/wasd_keyboard.png", m_renderer);
	}

	if (m_input->IsTriggered(SDL_SCANCODE_A))
	{
        tutorialBeeb.sound.Play();
        p1_movekey.sprite.Free();
        p1_movekey.sprite.LoadImage("texture/UI/keyboard/a_pressed.png", m_renderer);
	}
	else if (m_input->IsReleased(SDL_SCANCODE_A))
	{
		a_moveCheck = 1;
        p1_movekey.sprite.Free();
        p1_movekey.sprite.LoadImage("texture/UI/keyboard/wasd_keyboard.png", m_renderer);
	}

	if (m_input->IsTriggered(SDL_SCANCODE_S))
	{
        tutorialBeeb.sound.Play();
        p1_movekey.sprite.Free();
        p1_movekey.sprite.LoadImage("texture/UI/keyboard/s_pressed.png", m_renderer);
	}
	else if (m_input->IsReleased(SDL_SCANCODE_S))
	{
		s_moveCheck = 1; 
	    p1_movekey.sprite.Free();
        p1_movekey.sprite.LoadImage("texture/UI/keyboard/wasd_keyboard.png", m_renderer);
	}

	if (m_input->IsTriggered(SDL_SCANCODE_D))
	{
        tutorialBeeb.sound.Play();
        p1_movekey.sprite.Free();
        p1_movekey.sprite.LoadImage("texture/UI/keyboard/d_pressed.png", m_renderer);
	}
	else if (m_input->IsReleased(SDL_SCANCODE_D))
	{
		d_moveCheck = 1;
        p1_movekey.sprite.Free();
        p1_movekey.sprite.LoadImage("texture/UI/keyboard/wasd_keyboard.png", m_renderer);
	}

    
	if (m_input->IsTriggered(SDL_SCANCODE_UP))
	{
        tutorialBeeb.sound.Play();
        p2_movekey.sprite.Free();
        p2_movekey.sprite.LoadImage("texture/UI/keyboard/up_pressed.png", m_renderer);
	}
	else if (m_input->IsReleased(SDL_SCANCODE_UP))
	{
		up_moveCheck = 1;
        p2_movekey.sprite.Free();
        p2_movekey.sprite.LoadImage("texture/UI/keyboard/keyboard.png", m_renderer);
	}

	if (m_input->IsTriggered(SDL_SCANCODE_LEFT))
	{
        tutorialBeeb.sound.Play();
        p2_movekey.sprite.Free();
        p2_movekey.sprite.LoadImage("texture/UI/keyboard/left_pressed.png", m_renderer);
	}
	else if (m_input->IsReleased(SDL_SCANCODE_LEFT))
	{
		left_moveCheck = 1;
        p2_movekey.sprite.Free();
        p2_movekey.sprite.LoadImage("texture/UI/keyboard/keyboard.png", m_renderer);
	}

	if (m_input->IsTriggered(SDL_SCANCODE_DOWN))
	{
        tutorialBeeb.sound.Play();
        p2_movekey.sprite.Free();
	    p2_movekey.sprite.LoadImage("texture/UI/keyboard/down_pressed.png", m_renderer);
	}
	else if (m_input->IsReleased(SDL_SCANCODE_DOWN))
	{
		down_moveCheck = 1;
        p2_movekey.sprite.Free();
        p2_movekey.sprite.LoadImage("texture/UI/keyboard/keyboard.png", m_renderer);
	}

	if (m_input->IsTriggered(SDL_SCANCODE_RIGHT))
	{
        tutorialBeeb.sound.Play();
        p2_movekey.sprite.Free();
        p2_movekey.sprite.LoadImage("texture/UI/keyboard/right_pressed.png", m_renderer);
	}
	else if (m_input->IsReleased(SDL_SCANCODE_RIGHT))
	{
		right_moveCheck = 1;
        p2_movekey.sprite.Free();
        p2_movekey.sprite.LoadImage("texture/UI/keyboard/keyboard.png", m_renderer);
	}
	if (w_moveCheck + a_moveCheck + s_moveCheck + d_moveCheck == 4 
        && up_moveCheck + left_moveCheck + down_moveCheck + right_moveCheck == 4)
	{
		RemoveObject(&move_text);
		if (attack_text.text.GetTexture() == nullptr)
		{
			attack_text.transform.position.Set(0.f, 300.f, 1.f);
			SelectText(&attack_text, "Press attack key.", "h", { 0,0,0,255 });
		}
        if (key_h.sprite.GetTexture() == nullptr)
        {
            key_h.transform.position.Set(-390.f, 150.f, 0.f);
            key_h.transform.SetScale(70.f, 70.f);
            key_h.sprite.LoadImage("texture/UI/keyboard/key_h.png", State::m_renderer);
            AddObject(&key_h);
        }
		if (m_input->IsTriggered(SDL_SCANCODE_H))
		{
            tutorialBeeb.sound.Play();
            key_h.sprite.Free();
            key_h.sprite.LoadImage("texture/UI/keyboard/h_pressed.png", m_renderer);
		}
		else if (m_input->IsReleased(SDL_SCANCODE_H))
		{
            p1_attackCheck = 1;
            key_h.sprite.Free();
            key_h.sprite.LoadImage("texture/UI/keyboard/key_h.png", m_renderer);
		}

        if (numpad2.sprite.GetTexture() == nullptr)
        {
            numpad2.transform.position.Set(360, 150.f, 0.f);
            numpad2.transform.SetScale(70.f, 70.f);
            numpad2.sprite.LoadImage("texture/UI/keyboard/numpad2.png", m_renderer);
            AddObject(&numpad2);
        }
        if (m_input->IsTriggered(SDL_SCANCODE_KP_2))
        {
            tutorialBeeb.sound.Play();
            numpad2.sprite.Free();
            numpad2.sprite.LoadImage("texture/UI/keyboard/2_pressed.png", m_renderer);

        }
        else if (m_input->IsReleased(SDL_SCANCODE_KP_2))
        {
            p2_attackCheck = 1;
            numpad2.sprite.Free();
            numpad2.sprite.LoadImage("texture/UI/keyboard/numpad2.png", m_renderer);
        }
	}

	if (p1_attackCheck == 1 && p2_attackCheck == 1)
	{
		RemoveObject(&attack_text);
		if (trap_text.text.GetTexture() == nullptr)
		{
			trap_text.transform.position.Set(0.f, 300.f, 1.f);
			SelectText(&trap_text, "Press trap key.", "j", { 0,0,0,255 });
		}
        if (key_j.sprite.GetTexture() == nullptr)
        {
            key_j.transform.position.Set(-310, 150.f, 0.f);
            key_j.transform.SetScale(70.f, 70.f);
            key_j.sprite.LoadImage("texture/UI/keyboard/key_j.png", State::m_renderer);
            AddObject(&key_j);
        }
		if (m_input->IsTriggered(SDL_SCANCODE_J))
		{
            tutorialBeeb.sound.Play();
            key_j.sprite.Free();
            key_j.sprite.LoadImage("texture/UI/keyboard/j_pressed.png", m_renderer);
		}
		else if (m_input->IsReleased(SDL_SCANCODE_J))
		{
            p1_trapCheck = 1;
            key_j.sprite.Free();
            key_j.sprite.LoadImage("texture/UI/keyboard/key_j.png", m_renderer);
		}

        if (numpad3.sprite.GetTexture() == nullptr)
        {
            numpad3.transform.position.Set(440.f, 150.f, 0.f);
            numpad3.transform.SetScale(70.f, 70.f);
            numpad3.sprite.LoadImage("texture/UI/keyboard/numpad3.png", State::m_renderer);
            AddObject(&numpad3);
        }
        if (m_input->IsTriggered(SDL_SCANCODE_KP_3))
        {
            tutorialBeeb.sound.Play();
            numpad3.sprite.Free();
            numpad3.sprite.LoadImage("texture/UI/keyboard/3_pressed.png", State::m_renderer);
        }
        else if (m_input->IsReleased(SDL_SCANCODE_KP_3))
        {
            p2_trapCheck = 1;
            numpad3.sprite.Free();
            numpad3.sprite.LoadImage("texture/UI/keyboard/numpad3.png", m_renderer);
        }
	}

	if (p1_trapCheck == 1 && p2_trapCheck == 1)
	{
		RemoveObject(&trap_text);
		if (next_text.text.GetTexture() == nullptr)
		{
            next_text.transform.position.Set(0.f, 300.f, 1.f);
            SelectText(&next_text, "Press space to continue", "next", { 0, 0, 0, 255 });
		}
        if (m_input->IsTriggered(SDL_SCANCODE_SPACE))
        {
            m_game->Change(LV_ModeSelect);
        }
        if (m_input->IsTriggered(SDL_SCANCODE_RETURN))
        {
            m_game->Change(LV_ModeSelect);
        }
	}
}

/*
*  Item Functions
*/
void TutorialLevel::CheckSetTrap()
{
	if (State::m_input->IsTriggered(SDL_SCANCODE_J))
	{
        tutorialBeeb.sound.Play();
		if (player1.trapCoolDown < 0.f && player1.GetObject().customPhysics.GetVelocity().y == 0)
		{
			if (player1.trap.customPhysics.GetBody() != nullptr)
			{
				player1.trap.RemoveCustomPhysicsComponent();
				RemoveObject(&player1.trap);
			}
			player1.trapCoolDown = 5.f;
			player1.trap.SetName("p1 Trap");
			player1.trap.transform.position.Set(player1.GetObject().transform.position.x, player1.GetObject().transform.position.y - 40.f, 0.f);
			player1.trap.transform.SetScale(50.f, 20.f);

			player1.trap.sprite.color = SDL_Color{ 255, 0, 0, 255 };
			player1.trap.sprite.LoadImage("texture/items/trap.png", m_renderer);

			player1.trap.customPhysics.pOwnerTransform = &player1.trap.transform;
			player1.trap.customPhysics.bodyType = CustomPhysics::STATIC;
			player1.trap.customPhysics.AllocateBody(GetCustomPhysicsWorld());

			player1.trap.customPhysics.ActiveGhostCollision(false);

			AddObject(&player1.trap);
			AddCustomPhysicsComponent(&player1.trap);
		}
	}
	if (State::m_input->IsTriggered(SDL_SCANCODE_KP_3) && player2.GetObject().customPhysics.GetVelocity().y == 0)
	{
        tutorialBeeb.sound.Play();
		if (player2.trapCoolDown < 0.f)
		{
			if (player2.trap.customPhysics.GetBody() != nullptr)
			{
				player2.trap.RemoveCustomPhysicsComponent();
				RemoveObject(&player2.trap);
			}
			player2.trapCoolDown = 5.f;
			player2.trap.SetName("p2 Trap");
			player2.trap.transform.position.Set(player2.GetObject().transform.position.x, player2.GetObject().transform.position.y - 40.f, 0.f);
			player2.trap.transform.SetScale(50.f, 20.f);

			player2.trap.sprite.color = SDL_Color{ 0, 0, 255, 255 };
			player2.trap.sprite.LoadImage("texture/items/trap.png", m_renderer);

			player2.trap.customPhysics.pOwnerTransform = &player2.trap.transform;
			player2.trap.customPhysics.bodyType = CustomPhysics::STATIC;
			player2.trap.customPhysics.AllocateBody(GetCustomPhysicsWorld());

			player2.trap.customPhysics.ActiveGhostCollision(false);

			AddObject(&player2.trap);
			AddCustomPhysicsComponent(&player2.trap);
		}
	}
}

void TutorialLevel::CheckTrapCollision()
{
	if (player2.GetObject().customPhysics.IsCollidingWith(&player1.trap))
	{
		if (player2.GetDirection() == Player::Direction::RIGHT)
		{
            trap.sound.Play();
			player2.GetObject().customPhysics.SetVelocity(-100.f, 40.f);
			player2.SetKnockBackDelay(0.4f);
		}
		else
		{
            trap.sound.Play();
			player2.GetObject().customPhysics.SetVelocity(100.f, 40.f);
			player2.SetKnockBackDelay(0.4f);
		}
		player1.trap.RemoveCustomPhysicsComponent();
		RemoveObject(&player1.trap);
	}
	if (player1.GetObject().customPhysics.IsCollidingWith(&player2.trap))
	{
		if (player2.GetDirection() == Player::Direction::LEFT)
		{
            trap.sound.Play();
			player1.GetObject().customPhysics.SetVelocity(100.f, 40.f);
			player1.SetKnockBackDelay(0.4f);
		}
		else
		{
            trap.sound.Play();
			player1.GetObject().customPhysics.SetVelocity(100.f, 40.f);
			player1.SetKnockBackDelay(0.4f);
		}
		player2.trap.RemoveCustomPhysicsComponent();
		RemoveObject(&player2.trap);
	}
}

/*
* Effects
*/
void TutorialLevel::AttackEffect(Player& player, float dt)
{
	if (player.isAttack == true && player.effectLifeTime < 0.f)
	{
		hitsound.sound.Play();
		player.isAttack = false;
		b2Vec3 pos = player.GetObject().transform.position;
		player.effect.SetName("attackEffect");
		if (player.GetDirection() == Player::Direction::LEFT)
		{
			pos.Set(pos.x - player.GetCharacterStatus().reach / 2.f, pos.y + 8, pos.z);
			player.effect.sprite.LoadImage(player.GetLeftEffectFileName(), m_renderer);
		}
		if (player.GetDirection() == Player::Direction::RIGHT)
		{
			pos.Set(pos.x + player.GetCharacterStatus().reach / 2.f, pos.y + 8, pos.z);
			player.effect.sprite.LoadImage(player.GetRightEffectFileName(), m_renderer);
		}
		player.effect.transform.position.Set(pos.x, pos.y, pos.z);
		player.effect.transform.SetScale(player.GetCharacterStatus().reach, 100.f);
		player.effect.transform.rotation = 0;
		player.effect.sprite.color = SDL_Color{ 255, 255, 255, 255 };
		player.effect.sprite.activeAnimation = false;

		AddObject(&player.effect);
		player.effectLifeTime = 0.5f;
	}

	if (player.effectLifeTime < 0.f && player.effect.sprite.GetTexture() != nullptr)
	{
		player.effect.sprite.Free();
		RemoveObject(&player.effect);
	}

	else if (player.effectLifeTime > 0.f)
	{
		b2Vec3 pos = player.GetObject().transform.position;
		if (player.GetDirection() == Player::Direction::LEFT)
		{
			pos.Set(pos.x - player.GetCharacterStatus().reach / 2.f, pos.y, pos.z);
		}
		if (player.GetDirection() == Player::Direction::RIGHT)
		{
			pos.Set(pos.x + player.GetCharacterStatus().reach / 2.f, pos.y, pos.z);
		}
		player.effect.transform.position.Set(pos.x, pos.y, pos.z);
	}
	player.effectLifeTime -= dt;
}

void TutorialLevel::CreateCommonUI()
{
    p1.SetName("p1");
    p1.sprite.LoadImage("texture/UI/p1.png", m_renderer);
    p1.transform.SetScale(50, 50);
    p1.transform.position.Set(-500.f, m_height / 2.f - 50.f, 0.f);
    p1.sprite.isHud = true;
    AddObject(&p1);

    p1_trapImage.SetName("p1_trapImage");
    p1_trapImage.sprite.LoadImage("texture/items/trap.png", m_renderer);
    p1_trapImage.transform.SetScale(40, 30);
    p1_trapImage.sprite.color = SDL_Color{ 255, 0, 0, 255 };
    p1_trapImage.transform.position.Set(-500.f + 85.f, m_height / 2.f - 100.f, 0.f);
    p1_trapImage.sprite.isHud = true;
    AddObject(&p1_trapImage);

    p1_trapcooldown_ui.SetName("p1trapcooldown");
    p1_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p1_1.png", m_renderer);
    p1_trapcooldown_ui.transform.SetScale(120, 40);
    p1_trapcooldown_ui.transform.position.Set(-500.f, m_height / 2.f - 100.f, 0.f);
    p1_trapcooldown_ui.sprite.isHud = true;
    AddObject(&p1_trapcooldown_ui);

    p2.SetName("p2");
    p2.sprite.LoadImage("texture/UI/p2.png", m_renderer);
    p2.transform.SetScale(50, 50);
    p2.transform.position.Set(500.f, m_height / 2.f - 50.f, 0.f);
    p2.sprite.isHud = true;
    AddObject(&p2);

    p2_trapImage.SetName("p2_trapImage");
    p2_trapImage.sprite.LoadImage("texture/items/trap.png", m_renderer);
    p2_trapImage.transform.SetScale(40, 30);
    p2_trapImage.sprite.color = SDL_Color{ 0, 0, 255, 255 };
    p2_trapImage.transform.position.Set(500.f - 85.f, m_height / 2.f - 100.f, 0.f);
    p2_trapImage.sprite.isHud = true;
    AddObject(&p2_trapImage);

    p2_trapcooldown_ui.SetName("p2trapcooldown");
    p2_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p2_1.png", m_renderer);
    p2_trapcooldown_ui.transform.SetScale(120, 40);
    p2_trapcooldown_ui.transform.position.Set(500.f, m_height / 2.f - 100.f, 0.f);
    p2_trapcooldown_ui.sprite.isHud = true;
    AddObject(&p2_trapcooldown_ui);

    CreateScoreUI();
}

void TutorialLevel::CreateScoreUI()
{
    p1_score_1.SetName("p1_score_1");
    p1_score_2.SetName("p1_score_2");
    if (m_game->p1WinCount == 1)
    {
        p1_score_1.sprite.LoadImage("texture/UI/score_p1win.png", m_renderer);
        p1_score_2.sprite.LoadImage("texture/UI/score.png", m_renderer);
    }
    else if (m_game->p1WinCount == 2)
    {
        p1_score_1.sprite.LoadImage("texture/UI/score_p1win.png", m_renderer);
        p1_score_2.sprite.LoadImage("texture/UI/score_p1win.png", m_renderer);
    }
    else
    {
        p1_score_1.sprite.LoadImage("texture/UI/score.png", m_renderer);
        p1_score_2.sprite.LoadImage("texture/UI/score.png", m_renderer);
    }
    p1_score_1.transform.SetScale(30, 30);
    p1_score_1.sprite.color = SDL_Color{ 255, 255, 255, 255 };
    p1_score_1.transform.position.Set(-500.f + 50.f, m_height / 2.f - 50.f, 0.f);
    p1_score_1.sprite.isHud = true;
    AddObject(&p1_score_1);
    p1_score_2.transform.SetScale(30, 30);
    p1_score_2.sprite.color = SDL_Color{ 255, 255, 255, 255 };
    p1_score_2.transform.position.Set(-500.f + 85.f, m_height / 2.f - 50.f, 0.f);
    p1_score_2.sprite.isHud = true;
    AddObject(&p1_score_2);

    p2_score_1.SetName("p2_score_1");
    p2_score_2.SetName("p2_score_2");
    if (m_game->p2WinCount == 1)
    {
        p2_score_1.sprite.LoadImage("texture/UI/score_p2win.png", m_renderer);
        p2_score_2.sprite.LoadImage("texture/UI/score.png", m_renderer);
    }
    else if (m_game->p2WinCount == 2)
    {
        p2_score_1.sprite.LoadImage("texture/UI/score_p2win.png", m_renderer);
        p2_score_2.sprite.LoadImage("texture/UI/score_p2win.png", m_renderer);
    }
    else
    {
        p2_score_1.sprite.LoadImage("texture/UI/score.png", m_renderer);
        p2_score_2.sprite.LoadImage("texture/UI/score.png", m_renderer);
    }
    p2_score_1.transform.SetScale(30, 30);
    p2_score_1.sprite.color = SDL_Color{ 255, 255, 255, 255 };
    p2_score_1.transform.position.Set(500.f - 50.f, m_height / 2.f - 50.f, 0.f);
    p2_score_1.sprite.isHud = true;
    AddObject(&p2_score_1);
    p2_score_2.sprite.LoadImage("texture/UI/score.png", m_renderer);
    p2_score_2.transform.SetScale(30, 30);
    p2_score_2.sprite.color = SDL_Color{ 255, 255, 255, 255 };
    p2_score_2.transform.position.Set(500.f - 85.f, m_height / 2.f - 50.f, 0.f);
    p2_score_2.sprite.isHud = true;
    AddObject(&p2_score_2);
}

void TutorialLevel::CheckRespawn()
{
    // Check for p1
    if (player1.GetObject().transform.position.y < camera.position.y - m_height / 2.f - 200 && p1_respawnText.text.GetTexture() == nullptr)
    {
        player1.SetRespawnTime(1.5f);

        p1_respawnText.SetName("p1_respawnText");
        p1_respawnText.text.SetText(m_renderer, "Respawn..", mainFont);
        p1_respawnText.text.color = SDL_Color{ 0,0,0 , 255 };
        p1_respawnText.transform.SetScale(140, 50);
        p1_respawnText.transform.position.Set(-500.f - 200.f, m_height / 2.f - 50.f, 0.f);
        p1_respawnText.sprite.isHud = true;
        AddObject(&p1_respawnText);
    }

    else if (player1.GetRespawnTime() < 0.f && player1.GetObject().transform.position.y < camera.position.y - m_height / 2.f - 200)
    {
        RemoveObject(&p1_respawnText);

        player1.GetObject().RemoveCustomPhysicsComponent();
        RemoveObject(&player1.GetObject());
        player1.CreatePlayerObject(&player2, { 0, 200 }, m_game->p1Character, 1);
        player1.AllocateBody(GetCustomPhysicsWorld());
        AddObject(&player1.GetObject());
        AddCustomPhysicsComponent(&player1.GetObject());
    }
    // Check for p2
    if (player2.GetObject().transform.position.y < camera.position.y - m_height / 2.f - 200 && p2_respawnText.text.GetTexture() == nullptr)
    {
        player2.SetRespawnTime(1.5f);

        p2_respawnText.SetName("p2_respawnText");
        p2_respawnText.text.SetText(m_renderer, "Respawn..", mainFont);
        p2_respawnText.text.color = SDL_Color{ 0,0,0 , 255 };
        p2_respawnText.transform.SetScale(140, 50);
        p2_respawnText.transform.position.Set(500.f + 200.f, m_height / 2.f - 50.f, 0.f);
        p2_respawnText.sprite.isHud = true;
        AddObject(&p2_respawnText);
    }
    else if (player2.GetRespawnTime() < 0.f && player2.GetObject().transform.position.y < camera.position.y - m_height / 2.f - 200)
    {
        RemoveObject(&p2_respawnText);

        player2.GetObject().RemoveCustomPhysicsComponent();
        RemoveObject(&player2.GetObject());
        player2.CreatePlayerObject(&player1, { 0, 200 }, m_game->p2Character, 2);
        player2.AllocateBody(GetCustomPhysicsWorld());
        AddObject(&player2.GetObject());
        AddCustomPhysicsComponent(&player2.GetObject());
    }
}


void TutorialLevel::TrapCooldownAnimation(float dt)
{
    p1_trapcooldown_ui.sprite.Free();
    p2_trapcooldown_ui.sprite.Free();
    // Player1 UI
    if (player1.trapCoolDown > 0.f)
    {
        p1_trapcooldown_ui.sprite.Free();

        if (player1.trapCoolDown <= 5.f && player1.trapCoolDown > 4.f)
        {
            p1_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p1_6.png", m_renderer);
        }
        else if (player1.trapCoolDown <= 4.f && player1.trapCoolDown > 3.f)
        {
            p1_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p1_5.png", m_renderer);
        }
        else if (player1.trapCoolDown <= 3.f && player1.trapCoolDown > 2.f)
        {
            p1_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p1_4.png", m_renderer);
        }
        else if (player1.trapCoolDown <= 2.f && player1.trapCoolDown > 1.f)
        {
            p1_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p1_3.png", m_renderer);
        }
        else if (player1.trapCoolDown <= 1.f && player1.trapCoolDown > 0.f)
        {
            p1_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p1_2.png", m_renderer);
        }
    }
    else
    {
        p1_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p1_1.png", m_renderer);
    }

    // Player2 UI
    if (player2.trapCoolDown > 0.f)
    {
        p2_trapcooldown_ui.sprite.Free();

        if (player2.trapCoolDown <= 5.f && player2.trapCoolDown > 4.f)
        {
            p2_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p2_6.png", m_renderer);
        }
        else if (player1.trapCoolDown <= 4.f && player2.trapCoolDown > 3.f)
        {
            p2_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p2_5.png", m_renderer);
        }
        else if (player1.trapCoolDown <= 3.f && player2.trapCoolDown > 2.f)
        {
            p2_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p2_4.png", m_renderer);
        }
        else if (player1.trapCoolDown <= 2.f && player2.trapCoolDown > 1.f)
        {
            p2_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p2_3.png", m_renderer);
        }
        else if (player1.trapCoolDown <= 1.f && player2.trapCoolDown > 0.f)
        {
            p2_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p2_2.png", m_renderer);
        }
    }
    else
    {
        p2_trapcooldown_ui.sprite.LoadImage("texture/UI/trapcooldown/TrapCool_p2_1.png", m_renderer);
    }
    player1.trapCoolDown -= dt;
    player2.trapCoolDown -= dt;
}