#pragma once
#include <cstdlib>
#include <ctime>
#include "GameInfo_Enums.h"
#include "Character_Extern.h"
#include "GameObjectExtern.h"
#include "..//Sprite/SpriteBatch/SpriteBatch.hpp"

class SpriteBatch;

class Characters : public SpriteBatch
{
public:
	Characters() = default;
	~Characters() {}

	//Functions which init the character's status and datas. 
	virtual void Init(Engine* game) = 0;

	//Functions which calculate the damage and heal. 
	void Damaged(float damage,int order, DamageTypes dmgtype = DamageTypes::DMTYPE_Normal);
	void Healed(float heal);

	//Functions which calculate the attack, defence and special skill. 
	void Attack(int delay, Characters& opponents, int order);
	void Defence(int delay);
	virtual void Special(int delay, Characters& opponents) = 0;

	//Get the character's data by using get functions.
	float GetHP() const { return health; }
	const CharacterStatus GetCharStat() { return char_stat; }
	SpriteBatch GetHealthUI() { return health_ui; }
	SpriteBatch& GetStunnEffect() { return this->stun_effects; }
	const CharacterActs& GetActs() { return *char_act; }
	const CharacterActs GetActs(int order) { return char_act[order]; }

	//Set the character's data by using setb functions.
	void ResetStat() { char_stat = CharacterStatus::Stat_Normal; }
	void ResetActs() { for (int i = 0; i < 3; ++i) { char_act[i] = CharacterActs::Acts_None; } }
	bool SetActs(CharacterActs acts, int order);

protected:
	//variables for character class.
	float health;
	int gauge;
	int current_gauge;
	float attack_damage;
	float defence_percentage;
	bool is_char_can_use_special = false;

	//Enums for character class.
	CharacterStatus char_stat;
	CharacterActs char_act[3] = { CharacterActs::Acts_None };

	//Objects for effect
	SpriteBatch stun_effects;

	//Objects for UI.
	SpriteBatch health_ui;
private:

};

class Player : public Characters
{
public:	
	bool GetItem(Items name);
	void Init(Engine* game) override;
	void Special(int delay, Characters& opponents) override;

protected:

private:

};

class Enemy : public Characters
{
public:
	void Init(Engine* game) override;
	void Settings(CardType* acts);
	void Special(int delay, Characters& opponents) override;
	bool GetSpecialStatus() { return is_using_special; }

protected:

private:
	bool is_using_special = false;
};
