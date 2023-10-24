#include "GameObjects.h"
#include "GameInfo_Enums.h"
#include "GameObjectExtern.h"
#include "Character_Extern.h"

void Background::Background_Init(Engine* game)
{
	switch (Stages)
	{
	case Stage::Stage_Select:
	{

	}
	break;
	case Stage::Stage_Tutorial:
	{
		SpriteInit("Data/State/Prototype/Background.txt", game);
		BGSound_Init("Sound/Background/Battle_BGM.ogg");
	}
	break;
	}

}

void UI::UI_Init(Engine* game)
{
	SpriteInit("Data/Object/UI/UI.txt", game);
}

void Attack_Card::Card_Init(Engine* game)
{
	cd_type = CardType::Card_Attack;
	switch (char_type)
	{
	case Char_Beardur:
	{
		SpriteInit("Data/Character/Beardur/Attack_Card.txt", game);
		SoundEffect_Init("Sound/Effect/Sword_Drawing.mp3");
		attack_types = DamageTypes::DMTYPE_Normal;
	}
	break;
	}
}

void Defence_Card::Card_Init(Engine* game)
{
	cd_type = CardType::Card_Defence;
	switch (char_type)
	{
	case Char_Beardur:
	{
		SpriteInit("Data/Character/Beardur/Defence_Card.txt", game);
		defence_types = DefenceTypes::DFTYPE_Normal;
	}
	break;
	}
}

void Special_Card::Card_Init(Engine* game)
{
	cd_type = CardType::Card_Special;
	switch (char_type)
	{
	case Char_Beardur:
	{
		SpriteInit("Data/Character/Beardur/Special_Card.txt", game);
		special_types = DamageTypes::DMTYPE_Stun;
	}
	break;
	}
}

void Select_Card_1::Card_Init(Engine* game)
{
	cd_order = CardOrders::first;
	SpriteInit("Data/Object/UI/Select_Card_1.txt", game);
}

void Select_Card_2::Card_Init(Engine* game)
{
	cd_order = CardOrders::second;
	SpriteInit("Data/Object/UI/Select_Card_2.txt", game);
}

void Select_Card_3::Card_Init(Engine* game)
{
	cd_order = CardOrders::third;
	SpriteInit("Data/Object/UI/Select_Card_3.txt", game);
}

void Weapon_Card::Card_Init(Engine* game)
{
	/* Weapons...*/
}

void Item_Card::Card_Init(Engine* game)
{
	/* Items... */
}

void Cards::Card_Selecting(Engine* game)
{

	if (cd_type == CardType::Card_Special && Is_special_selected == false )
	{

		if (player_current_special_guage == 3)
		{
			CanSelect_Card = true;
			
		}
		else
		{
			CanSelect_Card = false;
		}
	}


	
	if (CanSelect_Card )
	{
		

		if (this->Is_mouse_collided())
		{
			if (game->getMouse().Is_Mouse_Downed(MouseButton::Left))
			{
				this->Change_Color(Colors::SKY_BLUE);
			}
			else if (game->getMouse().Is_Mouse_Clicked(MouseButton::Left))
			{
				if (this->SoundEffect_Name() != nullptr)
				{
					this->SoundEffect_Play();
				}
				for (unsigned int i = 0; i < 3; i++)
				{
					if (game_Cards[i] == CardType::Card_None)
					{
						if (cd_type == CardType::Card_Special)
						{
							Is_special_selected = true;
							CanSelect_Card = false;
						}
						game_Cards[i] = cd_type;
						break;
					}
				}
				this->Change_Color(Colors::WHITE);
			}
			else
			{
				this->Change_Color(Colors::GRAY);

			}
		}
		else
		{
			this->Change_Color(Colors::WHITE);
			if (cd_type == CardType::Card_Special)
			{
				this->Change_Color(Colors::GOLD);
			}
		}
	}
	else
	{
		this->Change_Color(Colors::BLACK);
	}
}

void Cards::Card_Select_Update()
{
	switch (game_Cards[cd_order])
	{
	case 0:
	{
		if (cd_order == 0)
		{
			this->SetPath("Texture/Cards/Card_1.png");
			this->Change_Color(Colors::WHITE_ALPHA);
		}
		else if (cd_order == 1)
		{
			this->SetPath("Texture/Cards/Card_2.png");
			this->Change_Color(Colors::WHITE_ALPHA);
		}
		else if (cd_order == 2)
		{
			this->SetPath("Texture/Cards/Card_3.png");
			this->Change_Color(Colors::WHITE_ALPHA);
		}
		break;
	}
	case 1:
	{
		this->SetPath("Texture/Cards/attack.png");
		this->Change_Color(Colors::WHITE);
		break;
	}
	case 2:
	{
		this->SetPath("Texture/Cards/defense.png");
		this->Change_Color(Colors::WHITE);
		break;
	}
	case 3:
	{
		this->SetPath("Texture/Cards/special.png");
		this->Change_Color(Colors::WHITE);
		break;
	}
	}

}

void Enemy_Showing_Card::Card_Init(Engine* game)
{

	SpriteInit("Data/Object/UI/Enemy_Select_Card_1.txt", game);

}


void Enemy_Showing_Card::Setup(CardType first)
{
	switch (first)
	{
	case CardType::Card_Attack:
	{
		this->SetPath("Texture/Cards/attack.png");
		break;
	}
	case CardType::Card_Defence:
	{
		this->SetPath("Texture/Cards/defense.png");
		break;
	}
	case CardType::Card_Special:
	{
		this->SetPath("Texture/Cards/Special.png");
		break;
	}
	case CardType::Card_Stunned:
	{
		this->SetPath("Texture/Cards/question_mark.png");
	}
	}
}

void Enemy_Showing_Card::Secret_Card_Init_Second(Engine* game)
{
	SpriteInit("Data/Object/UI/Veiled_Card2.txt", game);
}

void Enemy_Showing_Card::Secret_Card_Init_Third(Engine* game)
{
	SpriteInit("Data/Object/UI/Veiled_Card3.txt", game);
}

void Tuto_UI::ForTuto_UI_Init(Engine* game)
{
	SpriteInit("Data/State/Tutorial/Tuto_UI.txt", game);
}

void Tuto_UI::Tuto_UI_Explain_Card(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Explain_Card.txt", game);
}

void Tuto_UI::Tuto_UI_Explain_Character(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Explain_Character.txt", game);
}

void Tuto_UI::Tuto_UI_Explain_Enemy(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Explain_Enemy.txt", game);
}

void Tuto_UI::Tuto_UI_Explain_Health(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Explain_Health.txt", game);
}
void Tuto_UI::Tuto_UI_Explain_Item(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Explain_Item.txt", game);
}
void Tuto_UI::Tuto_UI_Explain_123(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Explain_123.txt", game);
}
void Tuto_UI::Tuto_UI_Explain_Weapon(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Explain_Weapon.txt", game);
}
void Tuto_UI::Tuto_UI_Explain_Next(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Explain_Next.txt", game);
}

void Tuto_Card::Tuto2_Card_Click(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Card_Click.txt", game);
}

void Tuto_Card::Tuto2_Card_Cancel(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Card_Cancel.txt", game);
}

void Tuto_Card::Tuto2_Card_Next(Engine* game)
{
	SpriteInit("Data/State/Tutorial/UI_Card_Next.txt", game);
}

void BloodSucking_Effects::Effect_Init(Engine* game)
{
	SpriteInit("Data/Object/Effects/EffectBloodSucking.txt", game);
}
