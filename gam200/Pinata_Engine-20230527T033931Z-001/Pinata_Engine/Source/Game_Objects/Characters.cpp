#include "Characters.h"
#include "Colors.h"

void Characters::Damaged(float damage, int order, DamageTypes dmgtype)
{
	if (char_act[0] == CharacterActs::Acts_Defence&& dmgtype != DamageTypes::DMTYPE_BloodSucking)
	{
		switch (order)
		{
		case 0:
			damage *= defence_percentage;
			break;
		case 1:
			damage *= 0.5f;
			break;
		case 2:
			damage *= 0.3f;
			break;
		}
	}
	
    if (this->health_ui.X > 0 )
    {
        this->health_ui.X += 2 * damage;
    }

	health -= damage;
    this->health_ui.Width = this->health*2;



	this->Change_Color(Colors::PINK_RED);
	if (health <= 0.f)
	{
		char_stat == CharacterStatus::Stat_Died;
	}
	else
	{
		switch (dmgtype)
		{ // In this algorithm, Player can have only 1 conditions
		case DMTYPE_Stun:
			char_stat = CharacterStatus::Stat_Stunned;
			break;
		case DMTYPE_Bleeding:
			char_stat = CharacterStatus::Stat_Bleeding;
			break;
		case DMTYPE_Poison:
			char_stat = CharacterStatus::Stat_Poisend;
			break;
		case DMTYPE_Fear:
			char_stat = CharacterStatus::Stat_Frightened;
			break;
		case DMTYPE_Weakness:
			char_stat = CharacterStatus::Stat_Weakness;
			break;
		}
	}
	char_act[0] = CharacterActs::Acts_None;
}

void Characters::Healed(float heal) //must fix this code
{
	health += heal;

	if (health > 100)
	{
		health = 100.f;
		this->health_ui.X = 400;
		this->health_ui.Width = 200;
	}
	else
	{
		this->health_ui.X -= 2 * heal;
		this->health_ui.Width += 2 * heal;
	}
}

void Characters::Attack(int delay,Characters& opponents,int order)
{

	if(delay == 99)
	{
		opponents.Change_Color(Colors::WHITE);
		this->Y -= (delay % 50) * 0.05f;
	}
	else if (delay == 50)
	{
		this->Y += (delay) * 0.05f;
		float damage = this->attack_damage;
		switch (order)
		{
		case 1:
			damage * 1.3f;
			break;
		case 2:
			damage * 1.6f;
			break;
		}
		opponents.Damaged(damage,order);
	}
	else if( delay > 50)
	{
		this->Y -= (delay % 50) * 0.05f;
	}
	else
	{
		this->Y += (delay) * 0.05f;
	}	
}

void Characters::Defence(int delay)
{
	this->char_act[0] = CharacterActs::Acts_Defence;
	int norm_X = static_cast<int>(this->X / std::abs(this->X));
	if (delay > 50)
	{
		this->X -= (delay % 50) * 0.05f*norm_X;
	}
	else
	{
		this->X += (delay) * 0.05f * norm_X;
	}
}

bool Characters::SetActs(CharacterActs acts, int order)
{
	if (order >= 0 && order < 3)
	{
		char_act[order] = acts;
		return true; 
	}
	return false;
}

bool Player::GetItem(Items name)
{
	for (unsigned int i =0;i <9 ; ++i)
	{
		if(game_item[i] == Items::Item_None)
		{
			game_item[i] = name;
			return true;
		}
	}
	return false;
}

//Function which init the character's status and datas. 
void Player::Init(Engine* game)
{
	char_stat = CharacterStatus::Stat_Normal;
	stun_effects.SpriteInit("Data/Object/Effects/EffectStun.txt", game);
	health_ui.SpriteInit("Data/Object/UI/Player_Health_UI.txt", game);

	switch (char_type)
	{
	case Char_Beardur:
	{		
		health = player_current_health;
		gauge = 3;
		current_gauge = player_current_special_guage;
		attack_damage = 5.f;
		defence_percentage = 0.7f;
		SpriteInit("Data/Character/Beardur/Beardur.txt", game);
	}
	break;
	}
	stun_effects.X = this->X+ 50.f;
	stun_effects.Y = this->Y + this->Height;
}

void Player::Special(int delay, Characters& opponents)
{
	switch (char_type)
	{
	case Char_Beardur:
	{
		if (delay < 25)
		{
			this->X += 15;
			this->Y+= 4;
		}
		else if (delay >= 25 && delay < 50)
		{
			this->X +=15;
			this->Y -= 4;
		}
		else if (delay >= 50 && delay < 75)
		{
			if (delay == 50)
			{
	
				opponents.Damaged(this->attack_damage * 3.f, 0, DamageTypes::DMTYPE_Stun);
			}
			this->X -= 15;
			//this->Y -= 2;
		}
		else
		{
			if (delay == 75)
			{
				opponents.Change_Color(Colors::WHITE);
			}
			
			this->X -= 15;
			//this->Y -= 2;
		}
		player_current_special_guage = 0;
	}
		break;
	}
}

//Function which init the enemy's status and datas. 
void Enemy::Init(Engine* game)
{
	srand((unsigned int)time(nullptr));
	char_stat = CharacterStatus::Stat_Normal;
	stun_effects.SpriteInit("Data/Object/Effects/EffectStun.txt", game);
	health_ui.SpriteInit("Data/Object/UI/Enemy_Health_UI.txt", game);

	switch (enem_type)
	{
	case Enemy_None:
	{
	}
	break;
	case Enemy_Vampion:
	{
		health = 100.f;
		gauge = 5;
		attack_damage = 5.f;
		defence_percentage = 0.7f;
		SpriteInit("Data/Enemy/Vampion/Vampion.txt", game);
	}
	break;
	}
	stun_effects.X = this->X+ 20.f;
	stun_effects.Y = this->Y + this->Height;
}

void Enemy::Settings(CardType* acts)
{
	if (current_gauge < Gauge)
	{
		current_gauge++;
		is_char_can_use_special = false;
	}
	else
	{
		is_char_can_use_special = true;
	}
		

	if(is_char_can_use_special)
	{
        current_gauge = 0;
		acts[0] = Card_Special;
		acts[1] = static_cast<CardType>(rand() % 2+1);
		acts[2] = static_cast<CardType>(rand() % 2+1);
	}
	else
	{
		acts[0] = static_cast<CardType>(rand() % 2 + 1);
		acts[1] = static_cast<CardType>(rand() % 2 + 1);
		acts[2] = static_cast<CardType>(rand() % 2 + 1);
	}

	if (char_stat == CharacterStatus::Stat_Stunned)
	{
		acts[2] = CardType::Card_Stunned;
	}
}

void Enemy::Special(int delay, Characters& opponents)
{
	switch (enem_type)
	{
	case Enemies::Enemy_Vampion:
		if (delay == 10)
		{
			is_using_special = true;
			float stealed_health = opponents.GetHP() * 0.3f;
			opponents.Damaged(stealed_health, 0, DMTYPE_BloodSucking);
			Healed(stealed_health);
		}
		

		break;
	}

	if (delay == 70)
	{
		is_using_special = false;
		opponents.Change_Color(Colors::WHITE);
	}
}



