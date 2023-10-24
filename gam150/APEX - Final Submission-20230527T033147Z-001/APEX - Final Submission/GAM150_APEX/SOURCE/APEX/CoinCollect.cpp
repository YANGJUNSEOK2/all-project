/************************************************************************
*	File name : CoinCollect.cpp
*	Project name : APEX
*	Author	    Primary author : Jookyung Lee
*			        Secondary author : Haewon Shon
*			        Others : Junseok Yang, Wonju cho
*
*			        Functions for Coin Collection Mode & data for platform and spring in each stage
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "CommonLevel.h"
#include "Utils.h"
#include "CoinCollect.h"

const int platformCount1 = 7;
const int platformCount2 = 6;
const int platformCount3 = 14;

const int springCount1 = 4;
const int springCount2 = 3;
const int springCount3 = 3;
platformInfoCoinCollect platformInfos1[platformCount1] =
{
{ {-600.f, 300.f}, 300.f, 30.f },
{ {-600.f, 0.f}, 300.f, 30.f},
{ {-600.f, -200.f}, 300.f, 30.f},
{ {0.f, -400.f}, 1920.f, 30.f},
{ {600.f, 300.f }, 300.f, 30.f },
{ {600.f, 0.f}, 300.f, 30.f},
{ {600.f, -200.f}, 300.f, 30.f }
};
b2Vec2 coinSpringInfo1[springCount1] = { {-700.f, 20.f}, {-200.f, -380.f}, {200.f, -380.f}, {700.f, 20.f} };


platformInfoCoinCollect platformInfos2[platformCount2] =
{
    {{0.f,0.f},1920.f,30.f},
    {{0.f,-300.f},1920.f,30.f},
    {{-400.f, 0.f}, 3.f, 3.f},
    {{400.f, 0.f}, 3.f, 3.f},
    {{-400.f, -300.f}, 3.f, 3.f},
    {{400.f, -300.f}, 3.f, 3.f},
};
b2Vec2 coinSpringInfo2[springCount2] = { {0.f, -270.f}, {-700.f, -270.f}, {700.f, -270.f} };

platformInfoCoinCollect platformInfos3[platformCount3] =
{
    { {0.f, -450.f}, 250.f, 30 },
    { {-600.f, -450.f}, 250.f, 30.f },
    { {600.f, -450.f}, 250.f, 30.f },
    { {-350.f, -300.f}, 300.f, 30.f },
    { {350.f, -300.f}, 300.f, 30.f },
    { {-700.f, -150.f}, 300.f, 30.f },
    { {700.f, -150.f}, 300.f, 30.f },
    {{0.f,-150.f},300.f,30.f},
    {{500.f,100.f},400.f,30.f},
    {{-500.f,100.f},400.f,30.f},
    {{300.f,250.f},300.f,30.f},
    {{-300.f,250.f},300.f,30.f},
    {{800.f,250.f},300.f,30.f},
    {{-800.f,250.f},300.f,30.f}
};
b2Vec2 coinSpringInfo3[springCount3] = { {-700, -120}, {700, -120}, {0, -120} };

void CoinCollectLevel::Initialize()
{
	/*
	 * Common Initialization
	*/
	m_backgroundColor.r = 255, m_backgroundColor.g = 255,
		m_backgroundColor.b = 255;
    
	camera.position.Set(0.f, 0.f, 150.f);

	m_useBuiltInPhysics = false;

	mainFont = TTF_OpenFont("font/JaykopDot.ttf", 256);

	b2Vec2 gravity(0.f, -40.f);
	SetCustomPhysicsWorld(gravity);

    switch (m_game->roundCount)
    {
    case 1:
        platformInfos = platformInfos1;
        platformCount = platformCount1;
        springPosition = coinSpringInfo1;
        springCount = springCount1;
        break;
    case 2:
        platformInfos = platformInfos2;
        platformCount = platformCount2;
        springPosition = coinSpringInfo2;
        springCount = springCount2;
        break;
    case 3:
        platformInfos = platformInfos3;
        platformCount = platformCount3;
        springPosition = coinSpringInfo3;
        springCount = springCount3;
        break;
    }

	player1.CreatePlayerObject(&player2, { -100.f, 100.f }, m_game->p1Character, 1);
	player2.CreatePlayerObject(&player1, { 100.f, 100.f }, m_game->p2Character, 2);

	player1.AllocateBody(GetCustomPhysicsWorld());
	AddObject(&player1.GetObject());
	AddCustomPhysicsComponent(&player1.GetObject());
	player2.AllocateBody(GetCustomPhysicsWorld());
	AddObject(&player2.GetObject());
	AddCustomPhysicsComponent(&player2.GetObject());

    hit_sound.SetName("hit_sound");
    hit_sound.sound.LoadSound("sound/hit_sound.wav");
    fail_sound.SetName("fail_sound");
    fail_sound.sound.LoadSound("sound/fail.wav");
    item_sound.SetName("item_sound");
    item_sound.sound.LoadSound("sound/eat_item.wav");
    trap_sound.SetName("trap");
    trap_sound.sound.LoadSound("sound/put_trap.wav");
    spring_sound.SetName("spring_sound");
    spring_sound.sound.LoadSound("sound/spring.wav");
    respawn_sound.SetName("respawn_sound");
    respawn_sound.sound.LoadSound("sound/respawn.wav");
    coin_sound.SetName("coin_sound");
    coin_sound.sound.LoadSound("sound/eat_coin.wav");

    background_sound.SetName("background_sound");
    background_sound.sound.LoadSound("sound/coinmusic.wav");

    background_sound.sound.Play();

    CreateCommonUI();

	/*
	 * Level Initializatinon
	*/
    for (int i = 0; i < platformCount; i++)
    {
        GeneratePlatform(platformInfos[i].position.x, platformInfos[i].position.y, platformInfos[i].width, platformInfos[i].height, i);
    }
    for (int i = 0; i < springCount; i++)
    {
        GenerateSpring(springPosition[i].x, springPosition[i].y, i);
    }
	UI_initialize();

    playTime = 0.f;
}

void CoinCollectLevel::Update(float dt)
{
    /* pause */
    if (m_input->IsTriggered(SDL_SCANCODE_ESCAPE))
    {
        m_game->Pause();
    }

    PrintCount();
    Score_UI();
	/******************* State ******************/
	if (EndCheck() == false && playTime >= 3.f)
	{
		player1.PlayerMovement(dt);
		player2.PlayerMovement(dt);
		CoinCheck(dt);
        Item(dt);
        Item2(dt);
        Spring();
	}

    player1.SetPlayerMovingAndStatus(dt);
    player2.SetPlayerMovingAndStatus(dt);
    player1.SetCollisionMoving();
    player2.SetCollisionMoving();
    CheckRespawn();
    IsPlayerStickToSide();

	player1.AnimationUpdate(dt);
	player2.AnimationUpdate(dt);
    AttackEffect(player1, dt);
    AttackEffect(player2, dt);
    ItemEffect(player1, dt);
    ItemEffect(player2, dt);

    CheckTrapCollision();
    CheckSetTrap();
    TrapCooldownAnimation(dt);

    playTime += dt;

	// Must be one of the last functions called at the end of State Update
	UpdateCustomPhysics(dt);
	Render(dt);
}

void CoinCollectLevel::Close()
{
    playTime = 0.f;
    p1Score = 0; 
    p2Score = 0;
    isItemAvaliable = false;
    isItemAvaliable2 = false;

    /* remove "object" only*/
    hit_sound.sound.Free();
    fail_sound.sound.Free();
    item_sound.sound.Free();
    background_sound.sound.Free();

    trap_sound.sound.Free();
    spring_sound.sound.Free();
    respawn_sound.sound.Free();
    coin_sound.sound.Free();

    RemoveObject(&hit_sound);
    RemoveObject(&fail_sound);
    RemoveObject(&item_sound);
    RemoveObject(&background_sound);
    RemoveObject(&trap_sound);
    RemoveObject(&spring_sound);
    RemoveObject(&respawn_sound);
    RemoveObject(&coin_sound);

    RemoveObject(&count);
    RemoveObject(&p1Score_UI);
    RemoveObject(&p2Score_UI);
    RemoveObject(&p1_scoretext);
    RemoveObject(&p2_scoretext);
    RemoveObject(&p1);
    RemoveObject(&p2);
    RemoveObject(&p1_trapImage);
    RemoveObject(&p2_trapImage);
    RemoveObject(&p1_trapcooldown_ui);
    RemoveObject(&p2_trapcooldown_ui);
    RemoveObject(&p1_score_1);
    RemoveObject(&p1_score_2);
    RemoveObject(&p2_score_1);
    RemoveObject(&p2_score_2);

    if (player1.effect.physics.GetBody() != nullptr)
    {
        RemoveObject(&player1.effect);
    }
    if (player2.effect.physics.GetBody() != nullptr)
    {
        RemoveObject(&player2.effect);
    }
    if (player1.itemEffect.sprite.GetTexture() != nullptr)
    {
        player1.itemEffect.sprite.Free();
        RemoveObject(&player1.itemEffect);
    }
    if (player2.itemEffect.sprite.GetTexture() != nullptr)
    {
        player2.itemEffect.sprite.Free();
        RemoveObject(&player2.itemEffect);
    }

    if (p1_respawnText.text.GetTexture() != nullptr)
    {
        p1_respawnText.sprite.Free();
        RemoveObject(&p1_respawnText);
    }
    if (p2_respawnText.text.GetTexture() != nullptr)
    {
        p2_respawnText.sprite.Free();
        RemoveObject(&p2_respawnText);
    }
    if (roundEndText.text.GetTexture() != nullptr)
    {
        RemoveObject(&roundEndText);
    }
    /* Remove "custom" objects */
    RemoveCustomPhysicsWorld();
    // Wrap up state
    ClearBaseState();
}

void CoinCollectLevel::GeneratePlatform(float posX, float posY, float sizeX, float sizeY, int platformNumber)
{
	platform[platformNumber].SetName("platform");
	platform[platformNumber].transform.position.Set(posX, posY, 0.f);
	platform[platformNumber].transform.SetScale(sizeX, sizeY);
	// Set the rotation of the object
	platform[platformNumber].transform.rotation = 0;
	platform[platformNumber].sprite.color = SDL_Color{ 255, 255, 255, 255 };
	platform[platformNumber].sprite.LoadImage("texture/platform_image/platformer.png", m_renderer);

	platform[platformNumber].customPhysics.pOwnerTransform = &platform[platformNumber].transform;
	platform[platformNumber].customPhysics.bodyType = CustomPhysics::STATIC;
	platform[platformNumber].customPhysics.AllocateBody(GetCustomPhysicsWorld());

	AddObject(&platform[platformNumber]);
	AddCustomPhysicsComponent(&platform[platformNumber]);
}

void CoinCollectLevel::CreateCommonUI()
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

void CoinCollectLevel::CreateScoreUI()
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

void CoinCollectLevel::PrintCount()
{
    if (playTime == 0.f)
    {
        count.SetName("count");
        count.transform.position.Set(0.f, 0.f, 0.f);
        count.transform.SetScale(300, 500);

        count.transform.rotation = 0;
        count.sprite.color = SDL_Color{ 255, 255, 255, 255 };
        count.sprite.LoadImage("texture/Utils/countdown.png", State::m_renderer);
        count.sprite.activeAnimation = true;
        count.sprite.SetFrame(3);
        count.sprite.SetSpeed(1.f);
        AddObject(&count);
        IsCountOn = true;
    }

    if (playTime > 3.f && IsCountOn == true)
    {
        count.sprite.Free();
        RemoveObject(&count);
        IsCountOn = false;
    }
}

void CoinCollectLevel::Restart()
{
    p1Score = 0;
    p2Score = 0;
    m_game->Restart();
}

void CoinCollectLevel::CheckRespawn()
{
    // Check for p1
    if (player1.GetObject().transform.position.y < camera.position.y - m_height / 2.f - 200 && p1_respawnText.text.GetTexture() == nullptr)
    {
        fail_sound.sound.Play();
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
        respawn_sound.sound.Play();
        RemoveObject(&p1_respawnText);

        player1.GetObject().RemoveCustomPhysicsComponent();
        RemoveObject(&player1.GetObject());
        b2Vec3 pos = platform[GetRandomNumber(0, platformCount)].transform.position;
        player1.CreatePlayerObject(&player2, { pos.x, pos.y + 200 }, m_game->p1Character, 1);
        player1.AllocateBody(GetCustomPhysicsWorld());
        AddObject(&player1.GetObject());
        AddCustomPhysicsComponent(&player1.GetObject());
    }
    // Check for p2
    if (player2.GetObject().transform.position.y < camera.position.y - m_height / 2.f - 200 && p2_respawnText.text.GetTexture() == nullptr)
    {
        fail_sound.sound.Play();

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
        respawn_sound.sound.Play();
        RemoveObject(&p2_respawnText);

        player2.GetObject().RemoveCustomPhysicsComponent();
        RemoveObject(&player2.GetObject());
        b2Vec3 pos = platform[GetRandomNumber(0, platformCount)].transform.position;
        player2.CreatePlayerObject(&player1, { pos.x, pos.y + 200 }, m_game->p2Character, 2);
        player2.AllocateBody(GetCustomPhysicsWorld());
        AddObject(&player2.GetObject());
        AddCustomPhysicsComponent(&player2.GetObject());
    }
}

void CoinCollectLevel::IsPlayerStickToSide()
{
    player1.SetIsStickSide(false);
    player2.SetIsStickSide(false);

    b2Vec3 p1Pos = player1.GetObject().transform.position;
    b2Vec3 p2Pos = player2.GetObject().transform.position;
    b2Vec2 p1Scale = player1.GetObject().transform.GetScale();
    b2Vec2 p2Scale = player2.GetObject().transform.GetScale();

    for (int i = 0; i < platformCount; i++)
    {
        // test for p1
        if (platformInfos[i].position.x - 1 - platformInfos[i].width / 2.f >= p1Pos.x - p1Scale.x / 2.f
            && platformInfos[i].position.x - 1 - platformInfos[i].width / 2.f <= p1Pos.x + p1Scale.x / 2.f
            &&platformInfos[i].position.y + platformInfos[i].height / 2.f >= p1Pos.y - p1Scale.y / 2.f
            && platformInfos[i].position.y + platformInfos[i].height / 2.f <= p1Pos.y + p1Scale.y / 2.f)
        {
            player1.SetIsStickSide(true);
        }
        if (platformInfos[i].position.x + 1 + platformInfos[i].width / 2.f >= p1Pos.x - p1Scale.x / 2.f
            && platformInfos[i].position.x + 1 + platformInfos[i].width / 2.f <= p1Pos.x + p1Scale.x / 2.f
            &&platformInfos[i].position.y + platformInfos[i].height / 2.f >= p1Pos.y - p1Scale.y / 2.f
            && platformInfos[i].position.y + platformInfos[i].height / 2.f <= p1Pos.y + p1Scale.y / 2.f)
        {
            player1.SetIsStickSide(true);
        }
        if (platformInfos[i].position.x - 1 - platformInfos[i].width / 2.f >= p1Pos.x - p1Scale.x / 2.f
            && platformInfos[i].position.x - 1 - platformInfos[i].width / 2.f <= p1Pos.x + p1Scale.x / 2.f
            &&platformInfos[i].position.y - platformInfos[i].height / 2.f >= p1Pos.y - p1Scale.y / 2.f
            && platformInfos[i].position.y - platformInfos[i].height / 2.f <= p1Pos.y + p1Scale.y / 2.f)
        {
            player1.SetIsStickSide(true);
        }
        if (platformInfos[i].position.x + 1 + platformInfos[i].width / 2.f >= p1Pos.x - p1Scale.x / 2.f
            && platformInfos[i].position.x + 1 + platformInfos[i].width / 2.f <= p1Pos.x + p1Scale.x / 2.f
            &&platformInfos[i].position.y - platformInfos[i].height / 2.f >= p1Pos.y - p1Scale.y / 2.f
            && platformInfos[i].position.y - platformInfos[i].height / 2.f <= p1Pos.y + p1Scale.y / 2.f)
        {
            player1.SetIsStickSide(true);
        }

        // test for p2
        if (platformInfos[i].position.x - 1 - platformInfos[i].width / 2.f >= p2Pos.x - p2Scale.x / 2.f
            && platformInfos[i].position.x - 1 - platformInfos[i].width / 2.f <= p2Pos.x + p2Scale.x / 2.f
            &&platformInfos[i].position.y + platformInfos[i].height / 2.f >= p2Pos.y - p2Scale.y / 2.f
            && platformInfos[i].position.y + platformInfos[i].height / 2.f <= p2Pos.y + p2Scale.y / 2.f)
        {
            player2.SetIsStickSide(true);
        }
        if (platformInfos[i].position.x + 1 + platformInfos[i].width / 2.f >= p2Pos.x - p2Scale.x / 2.f
            && platformInfos[i].position.x + 1 + platformInfos[i].width / 2.f <= p2Pos.x + p2Scale.x / 2.f
            &&platformInfos[i].position.y + platformInfos[i].height / 2.f >= p2Pos.y - p2Scale.y / 2.f
            && platformInfos[i].position.y + platformInfos[i].height / 2.f <= p2Pos.y + p2Scale.y / 2.f)
        {
            player2.SetIsStickSide(true);
        }
        if (platformInfos[i].position.x - 1 - platformInfos[i].width / 2.f >= p2Pos.x - p2Scale.x / 2.f
            && platformInfos[i].position.x - 1 - platformInfos[i].width / 2.f <= p2Pos.x + p2Scale.x / 2.f
            &&platformInfos[i].position.y - platformInfos[i].height / 2.f >= p2Pos.y - p2Scale.y / 2.f
            && platformInfos[i].position.y - platformInfos[i].height / 2.f <= p2Pos.y + p2Scale.y / 2.f)
        {
            player2.SetIsStickSide(true);
        }
        if (platformInfos[i].position.x + 1 + platformInfos[i].width / 2.f >= p2Pos.x - p2Scale.x / 2.f
            && platformInfos[i].position.x + 1 + platformInfos[i].width / 2.f <= p2Pos.x + p2Scale.x / 2.f
            &&platformInfos[i].position.y - platformInfos[i].height / 2.f >= p2Pos.y - p2Scale.y / 2.f
            && platformInfos[i].position.y - platformInfos[i].height / 2.f <= p2Pos.y + p2Scale.y / 2.f)
        {
            player2.SetIsStickSide(true);
        }
    }
}

void CoinCollectLevel::Item(float dt)
{

    if (regenDelay < 0.f)
    {
        if (isItemAvaliable == false)
        {
            MakeNewItem();
            isItemAvaliable = true;
        }

        regenDelay = 6.f;
    }
    else if (isItemAvaliable == true)
    {
        if (player1.GetObject().customPhysics.IsCollidingWith(&item) && player1.GetItemDuration() < 0.f)
        {
            item_sound.sound.Play();
            std::string itemName = item.GetName();
            if (itemName == "SpeedUp")
            {
                player1.AddSpeed(500);
            }
            if (itemName == "PowerUp")
            {
                player1.AddPower(20);
            }
            if (itemName == "StanceUp")
            {
                player1.AddStance(0.3f);
            }
            player1.SetItemDuration(5.f);
            item.RemoveCustomPhysicsComponent();
            RemoveObject(&item);
            isItemAvaliable = false;
        }
        if (player2.GetObject().customPhysics.IsCollidingWith(&item) && player2.GetItemDuration() < 0.f)
        {
            item_sound.sound.Play();
            std::string itemName = item.GetName();
            if (itemName == "SpeedUp")
            {
                player2.AddSpeed(300);
            }
            if (itemName == "PowerUp")
            {
                player2.AddPower(20);
            }
            if (itemName == "StanceUp")
            {
                player2.AddStance(0.3f);
            }
            player2.SetItemDuration(5.f);
            item.RemoveCustomPhysicsComponent();
            RemoveObject(&item);
            isItemAvaliable = false;
        }
    }
    regenDelay -= dt;
}

void CoinCollectLevel::MakeNewItem()
{
    item.SetName("item");
    int random = GetRandomNumber(0, 2);
    switch (random)
    {
    case 0:
        item.SetName("SpeedUp");
        item.sprite.LoadImage("texture/items/Shoes.png", m_renderer);
        break;
    case 1:
        item.SetName("PowerUp");
        item.sprite.LoadImage("texture/items/strong.png", m_renderer);
        break;
    case 2:
        item.SetName("StanceUp");
        item.sprite.LoadImage("texture/items/superarmor.png", m_renderer);
        break;
    default:
        break;
    }

    b2Vec3 pos;
    do
    {
        pos = platform[GetRandomNumber(0, platformCount - 1)].transform.position;
    } while (IsItemOverlapped(pos));
    item.transform.position.Set(pos.x, pos.y + 50, pos.z);
    item.transform.SetScale(100, 100);
    // Set the rotation of the object
    item.transform.rotation = 0;
    item.sprite.color = SDL_Color{ 255, 255, 255, 255 };

    item.customPhysics.pOwnerTransform = &item.transform;
    item.customPhysics.bodyType = CustomPhysics::STATIC;
    item.customPhysics.AllocateBody(GetCustomPhysicsWorld());

    item.customPhysics.ActiveGhostCollision(false);

    AddObject(&item);
    AddCustomPhysicsComponent(&item);
}

void CoinCollectLevel::Item2(float dt)
{
    if (regenDelay2 < 0.f)
    {
        if (isItemAvaliable2 == false)
        {
            MakeNewItem2();
            isItemAvaliable2 = true;
        }

        regenDelay2 = 7.f;
    }
    else if (isItemAvaliable2 == true)
    {
        if (player1.GetObject().customPhysics.IsCollidingWith(&item2) && player1.GetItemDuration() < 0.f)
        {
            item_sound.sound.Play();
            std::string itemName = item2.GetName();
            if (itemName == "SpeedUp")
            {
                player1.AddSpeed(500);
            }
            if (itemName == "PowerUp")
            {
                player1.AddPower(20);
            }
            if (itemName == "StanceUp")
            {
                player1.AddStance(0.3f);
            }
            player1.SetItemDuration(5.f);
            item2.RemoveCustomPhysicsComponent();
            RemoveObject(&item2);
            isItemAvaliable2 = false;
        }
        if (player2.GetObject().customPhysics.IsCollidingWith(&item2) && player2.GetItemDuration() < 0.f)
        {
            item_sound.sound.Play();
            std::string itemName = item2.GetName();
            if (itemName == "SpeedUp")
            {
                player2.AddSpeed(300);
            }
            if (itemName == "PowerUp")
            {
                player2.AddPower(20);
            }
            if (itemName == "StanceUp")
            {
                player2.AddStance(0.3f);
            }
            player2.SetItemDuration(5.f);
            item2.RemoveCustomPhysicsComponent();
            RemoveObject(&item2);
            isItemAvaliable2 = false;
        }
    }
    regenDelay2 -= dt;
}

void CoinCollectLevel::MakeNewItem2()
{
    item2.SetName("item2");
    int random2 = GetRandomNumber(3, 5);
    switch (random2)
    {
    case 3:
        item2.SetName("SpeedUp");
        item2.sprite.LoadImage("texture/items/Shoes.png", m_renderer);
        break;
    case 4:
        item2.SetName("PowerUp");
        item2.sprite.LoadImage("texture/items/strong.png", m_renderer);
        break;
    case 5:
        item2.SetName("StanceUp");
        item2.sprite.LoadImage("texture/items/superarmor.png", m_renderer);
        break;
    default:
        break;
    }
    b2Vec3 pos;
    do
    {
        pos = platform[GetRandomNumber(0, platformCount - 1)].transform.position;
    } while (IsItemOverlapped(pos));
    item2.transform.position.Set(pos.x, pos.y + 50.f, pos.z);
    item2.transform.SetScale(100, 100);
    // Set the rotation of the object
    item2.transform.rotation = 0;
    item2.sprite.color = SDL_Color{ 255, 255, 255, 255 };

    item2.customPhysics.pOwnerTransform = &item2.transform;
    item2.customPhysics.bodyType = CustomPhysics::STATIC;
    item2.customPhysics.AllocateBody(GetCustomPhysicsWorld());

    item2.customPhysics.ActiveGhostCollision(false);

    AddObject(&item2);
    AddCustomPhysicsComponent(&item2);
}

bool CoinCollectLevel::IsItemOverlapped(const b2Vec3 position)
{
    if(item.customPhysics.HasBody())
    {
        if (item.transform.position.x == position.x && item.transform.position.y == position.y + 50.f)
        {
            return true;
        }
    }
    if (item2.customPhysics.HasBody())
    {
        if (item2.transform.position.x == position.x && item2.transform.position.y == position.y + 50.f)
        {
            return true;
        }
    }
    if (coin.transform.position.x == position.x && coin.transform.position.y == position.y + 50.f)
    {
        if(coin.transform.position.x== position.x && coin.transform.position.y == position.y + 50.f)
        {
            return true;
        }
    }
    return false;
}

void CoinCollectLevel::CheckSetTrap()
{
    if (State::m_input->IsTriggered(SDL_SCANCODE_J))
    {
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

void CoinCollectLevel::CheckTrapCollision()
{
    if (player2.GetObject().customPhysics.IsCollidingWith(&player1.trap))
    {
        trap_sound.sound.Play();
        if (player2.GetDirection() == Player::Direction::RIGHT)
        {
            player2.GetObject().customPhysics.SetVelocity(-100.f, 40.f);
            player2.SetKnockBackDelay(0.4f);
        }
        else
        {
            player2.GetObject().customPhysics.SetVelocity(100.f, 40.f);
            player2.SetKnockBackDelay(0.4f);
        }
        player1.trap.RemoveCustomPhysicsComponent();
        RemoveObject(&player1.trap);
    }
    if (player1.GetObject().customPhysics.IsCollidingWith(&player2.trap))
    {
        trap_sound.sound.Play();
        if (player2.GetDirection() == Player::Direction::RIGHT)
        {
            player1.GetObject().customPhysics.SetVelocity(-100.f, 40.f);
            player1.SetKnockBackDelay(0.4f);
        }
        else
        {
            player1.GetObject().customPhysics.SetVelocity(100.f, 40.f);
            player1.SetKnockBackDelay(0.4f);
        }
        player2.trap.RemoveCustomPhysicsComponent();
        RemoveObject(&player2.trap);
    }
}

void CoinCollectLevel::TrapCooldownAnimation(float dt)
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

void CoinCollectLevel::GenerateSpring(float posX, float posY, int springNumber)
{
    spring[springNumber].SetName("spring");
    spring[springNumber].transform.position.Set(posX, posY, 0.f);
    spring[springNumber].transform.SetScale(50, 32);
    // Set the rotation of the object
    spring[springNumber].transform.rotation = 0;
    spring[springNumber].sprite.color = SDL_Color{ 255, 255, 255, 255 };
    spring[springNumber].sprite.LoadImage("texture/items/Spring_Animation.png", m_renderer);

    spring[springNumber].sprite.activeAnimation = true;
    spring[springNumber].sprite.SetFrame(3);
    spring[springNumber].sprite.SetSpeed(12.f);

    spring[springNumber].customPhysics.pOwnerTransform = &spring[springNumber].transform;
    spring[springNumber].customPhysics.bodyType = CustomPhysics::STATIC;
    spring[springNumber].customPhysics.AllocateBody(GetCustomPhysicsWorld());

    AddObject(&spring[springNumber]);
    AddCustomPhysicsComponent(&spring[springNumber]);
}

void CoinCollectLevel::Spring()
{
    for (int springNum = 0; springNum < springCount; springNum++)
    {
        if (player1.GetObject().customPhysics.IsCollidingWith(&spring[springNum]))
        {
            spring_sound.sound.Play();
            player1.GetObject().customPhysics.SetVelocity(0.f, 45.f);
        }

        if (player2.GetObject().customPhysics.IsCollidingWith(&spring[springNum]))
        {
            spring_sound.sound.Play();
            player2.GetObject().customPhysics.SetVelocity(0.f, 45.f);
        }
    }
}

/*
 * Effects
 */
void CoinCollectLevel::AttackEffect(Player& player, float dt)
{
    if (player.isAttack == true && player.effectLifeTime < 0.f)
    {
        hit_sound.sound.Play();
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

void CoinCollectLevel::ItemEffect(Player& player, float dt)
{
    dt;
    if (player.GetItemDuration() > 0 && (player.itemEffect.sprite.GetTexture() == nullptr))
    {
        player.itemEffect.SetName("attackEffect");
        player.itemEffect.transform.position.Set(player.GetObject().transform.position.x, player.GetObject().transform.position.y + 65.f, 0.f);
        player.itemEffect.transform.SetScale(50.f, 50.f);
        player.itemEffect.transform.rotation = 0;
        player.itemEffect.sprite.color = SDL_Color{ 255, 255, 255, 255 };
        player.effect.sprite.activeAnimation = false;

        if (player.GetItemName() == "SpeedUp")
        {
            player.itemEffect.sprite.LoadImage("texture/items/Shoes.png", m_renderer);
        }
        else if (player.GetItemName() == "PowerUp")
        {
            player.itemEffect.sprite.LoadImage("texture/items/strong.png", m_renderer);
        }
        else if (player.GetItemName() == "StanceUp")
        {
            player.itemEffect.sprite.LoadImage("texture/items/superarmor.png", m_renderer);
        }
        AddObject(&player.itemEffect);
    }
    else if (player.GetItemDuration() > 0.f)
    {
        b2Vec3 pos = player.GetObject().transform.position;
        player.itemEffect.transform.position.Set(player.GetObject().transform.position.x, player.GetObject().transform.position.y + 70.f, 0.f);
    }
    else if (player.itemEffect.sprite.GetTexture() != nullptr)
    {
        player.itemEffect.sprite.Free();
        RemoveObject(&player.itemEffect);
    }
}

/*
 * Coin Collect
 */
void CoinCollectLevel::Score_UI()
{
	std::string convert1 = std::to_string(p1Score);
	std::string convert2 = std::to_string(p2Score);
	char const *score_p1 = convert1.c_str();
	char const *score_p2 = convert2.c_str();

	RemoveObject(&p1Score_UI);
	p1Score_UI.SetName("p1score_ui");
	p1Score_UI.transform.position.Set(-70, m_height / 2.f - 70, 0.f);
	p1Score_UI.transform.SetScale(40.f , 40.f);
	p1Score_UI.text.SetText(m_renderer, score_p1, mainFont);
	p1Score_UI.text.color = SDL_Color{ 255,0,0,255 };
	p1Score_UI.text.isHud = true;
	AddObject(&p1Score_UI);

	RemoveObject(&p2Score_UI);
	p2Score_UI.SetName("p2score_ui");
	p2Score_UI.transform.position.Set(70, m_height / 2.f - 70, 0.f);
	p2Score_UI.transform.SetScale(40.f, 40.f);
	p2Score_UI.text.SetText(m_renderer, score_p2, mainFont);
	p2Score_UI.text.color = SDL_Color{ 0,0,255,255 };
	p2Score_UI.text.isHud = true;
	AddObject(&p2Score_UI);
}

void CoinCollectLevel::UI_initialize()
{
	p1_scoretext.SetName("p1score_ui");
	p1_scoretext.transform.position.Set(-70.f, m_height / 2.f- 30.f, 0.f);
	p1_scoretext.transform.SetScale(100.f, 50.f);
	p1_scoretext.text.SetText(m_renderer, "P1 Score", mainFont);
	p1_scoretext.text.color = SDL_Color{ 0,0,0,255 };
	p1_scoretext.text.isHud = true;
	AddObject(&p1_scoretext);

	p2_scoretext.SetName("p2score_ui");
	p2_scoretext.transform.position.Set(70.f, m_height / 2.f - 30.f, 0.f);
	p2_scoretext.transform.SetScale(100.f, 50.f);
	p2_scoretext.text.SetText(m_renderer, "P2 Score", mainFont);
	p2_scoretext.text.color = SDL_Color{ 0,0,0,255 };
	p2_scoretext.text.isHud = true;
	AddObject(&p2_scoretext);
}

bool CoinCollectLevel::EndCheck()
{
    if (!isGameEnd)
    {
        if (p1Score == 10)
        {
            player1.SetWin();
            player1.GetObject().physics.SetVelocity(0.f, 0.f);
            isGameEnd = true;
            m_game->p1WinCount += 1;
            m_game->roundCount++;
            RemoveObject(&p1_score_1);
            RemoveObject(&p1_score_2);
            RemoveObject(&p2_score_1);
            RemoveObject(&p2_score_2);
            CreateScoreUI();
        }
        else if (p2Score == 10)
        {
            player2.SetWin();
            player2.GetObject().physics.SetVelocity(0.f, 0.f);
            isGameEnd = true;
            m_game->p2WinCount += 1;
            m_game->roundCount++;
            RemoveObject(&p1_score_1);
            RemoveObject(&p1_score_2);
            RemoveObject(&p2_score_1);
            RemoveObject(&p2_score_2);
            CreateScoreUI();
        }
    }
    else
    {
        /* After Win */
        if (roundEndText.text.GetTexture() != nullptr)
        {
            roundEndText.text.Free();
        }
        roundEndText.SetName("roundEndText");
        roundEndText.text.SetText(m_renderer, "SPACE to continue", mainFont);
        roundEndText.text.color = SDL_Color{ 0,0,0 , 255 };
        roundEndText.transform.SetScale(450, 100);
        roundEndText.transform.position.Set(0, -m_height/2.f + 100.f, 0);
        roundEndText.sprite.isHud = true;
        AddObject(&roundEndText);

        if (m_input->IsTriggered(SDL_SCANCODE_SPACE))
        {
            isGameEnd = false;
            // if one of player won twice, go to showing winner level
            if (m_game->p1WinCount == 2 || m_game->p2WinCount == 2)
            {
                m_game->roundCount = 1;
                m_game->Change(LV_Ending);
            }
            else
            {
                Restart();
            }
        }
    }
    return isGameEnd;
}

void CoinCollectLevel::CoinCheck(float dt)
{
    if (coinRegenDelay < 0.f)
    {
        if (isCoinAvaliable == false)
        {
            CoinGenerate(dt);
            isCoinAvaliable = true;
        }

        coinRegenDelay = 3.f;
    }
    else if (isCoinAvaliable == true)
    {
        if (player1.GetObject().customPhysics.IsCollidingWith(&coin))
        {
            coin_sound.sound.Play();

            p1Score++;

            coin.RemoveCustomPhysicsComponent();
            RemoveObject(&coin);
            isCoinAvaliable = false;
        }
        if (player2.GetObject().customPhysics.IsCollidingWith(&coin))
        {
            coin_sound.sound.Play();

            p2Score++;

            coin.RemoveCustomPhysicsComponent();
            RemoveObject(&coin);
            isCoinAvaliable = false;
        }
    }
    coinRegenDelay -= dt;
}

void CoinCollectLevel::CoinGenerate(float /*dt*/)
{
    coin.SetName("coin");
    coin.sprite.LoadImage("texture/items/coin.png", m_renderer);

    b2Vec3 pos;
    do
    {
        pos = platform[GetRandomNumber(0, platformCount - 1)].transform.position;
    } while (IsItemOverlapped(pos));
    coin.transform.position.Set(pos.x, pos.y + 50, pos.z);
    coin.transform.SetScale(100, 100);
    // Set the rotation of the object
    coin.transform.rotation = 0;
    coin.sprite.color = SDL_Color{ 255, 255, 255, 255 };

    coin.sprite.activeAnimation = true;
    coin.sprite.SetFrame(4);
    coin.sprite.SetSpeed(3.f);

    coin.customPhysics.pOwnerTransform = &coin.transform;
    coin.customPhysics.bodyType = CustomPhysics::STATIC;
    coin.customPhysics.AllocateBody(GetCustomPhysicsWorld());

    coin.customPhysics.ActiveGhostCollision(false);

    AddObject(&coin);
    AddCustomPhysicsComponent(&coin);
}