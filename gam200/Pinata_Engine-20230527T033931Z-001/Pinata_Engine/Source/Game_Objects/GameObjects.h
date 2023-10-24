#pragma once
#include "../Sprite/SpriteBatch/SpriteBatch.hpp"
#include "GameInfo_Enums.h"
#include "Colors.h"

class SpriteBatch;


class Background : public SpriteBatch
{
public:
	void Background_Init(Engine* game);
};

class UI : public SpriteBatch
{
public:
	void UI_Init(Engine* game);
};

class BloodSucking_Effects : public SpriteBatch
{
public:
	void Effect_Init(Engine* game);
	void Update_positions(float x, float y) { this->X = x, this->Y = y; }
};


class Cards: public SpriteBatch
{
public:
	void Card_Selecting(Engine* game);
    void Card_Select_Update();
protected:
	CardOrders cd_order;
	CardType cd_type;
	bool CanSelect_Card = true;
	bool Is_special_selected = false;
    int count = 0;

};

class Attack_Card: public Cards
{
public:
	void Card_Init(Engine* game);
private:
	DamageTypes attack_types;
};

class Defence_Card: public Cards
{
public:
	void Card_Init(Engine* game);
private:
	DefenceTypes defence_types;
};

class Special_Card: public Cards
{
public:
	void Card_Init(Engine* game);
	void Reset_Special_selected() { this->Is_special_selected = false; }
private:
	DamageTypes special_types;
};

class Select_Card_1 : public Cards
{
public:
    void Card_Init(Engine* game);
    void ChangePath(std::string path) { m_path = path; };
private:
    std::string m_path;
};

class Select_Card_2 : public Cards
{
public:
    void Card_Init(Engine* game);
private:
};

class Select_Card_3 : public Cards
{
public:
    void Card_Init(Engine* game);
private:
};

class Weapon_Card: public Cards
{
public:
	void Card_Init(Engine* game);
private:
	Weapons weapon_type;
};

class Item_Card: public Cards
{
public:
	void Card_Init(Engine* game);
};

class Enemy_Showing_Card: public Cards
{
public:
	void Card_Init(Engine* game);
	void Setup(CardType first);
	void Secret_Card_Init_Second(Engine* game);
	void Secret_Card_Init_Third(Engine* game);
};

class Tuto_UI: public SpriteBatch
{
public:
	void ForTuto_UI_Init(Engine* game);
	void Tuto_UI_Explain_Card(Engine* game);
	void Tuto_UI_Explain_Character(Engine* game);
	void Tuto_UI_Explain_Enemy(Engine* game);
	void Tuto_UI_Explain_Health(Engine* game);
	void Tuto_UI_Explain_Item(Engine* game);
	void Tuto_UI_Explain_123(Engine* game);
	void Tuto_UI_Explain_Weapon(Engine* game);
	void Tuto_UI_Explain_Next(Engine* game);
};

class Tuto_Card : public SpriteBatch
{
public:
	void Tuto2_Card_Click(Engine* game);
	void Tuto2_Card_Cancel(Engine* game);
	void Tuto2_Card_Next(Engine* game);
};

class Tuto_Battle : public SpriteBatch
{
public:
	
};
