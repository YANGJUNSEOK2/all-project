#pragma once
enum Phase
{
	Phase_Init,
	Phase_Choose,
	Phase_Compare,
	Phase_Battle,
	Phase_End
};

enum CharacterType
{
	Char_Beardur
};

enum Enemies
{
	Enemy_None,
	Enemy_Vampion	
};

enum CardType
{
	Card_None,
	Card_Attack,
	Card_Defence,
	Card_Special,
	Card_Weapon,
	Card_Item,
	Card_Stunned
};

enum CharacterStatus
{
	Stat_Normal,
	Stat_Stunned,
	Stat_Bleeding,
	Stat_Poisend,
	Stat_Frightened,
	Stat_Weakness,
	Stat_Died
	/*Poisned, Bleeding ... etc*/
};

enum Items
{
	Item_None,
	Item_Health_Potion,
	Item_Poision_Potion
};

enum Weapons
{
	Weapon_None,
	Weapon_Sword,
	Weapon_Luckey_Dagger
};

enum SpecialTypes
{
	Volatile,
	Gauge
};

enum CardOrders
{
	first,
	second,
	third
};

enum DamageTypes
{
	DMTYPE_Normal,
	DMTYPE_Stun,
	DMTYPE_Bleeding,
	DMTYPE_Poison,
	DMTYPE_Fear,
	DMTYPE_Weakness,
	DMTYPE_Magic,
	DMTYPE_BloodSucking
};

enum DefenceTypes
{
	DFTYPE_Normal,
	DFTYPE_Counter
};

enum Stage
{
	Stage_Select,
	Stage_Tutorial,
};

enum BattleStat
{
	Attack_VS_Attack,
	Attack_VS_Def,
	Attack_VS_Special,
	
	Def_VS_Attack,
	Def_VS_Def,
	Def_VS_Special,
	
	Special_VS_Attack,
	Special_VS_Def,
	Special_VS_Special,

	Attack_VS_None,
	DeF_VS_None,

	Battle_Done
};

enum CharacterActs
{
	Acts_None, /* If characters get stunned...*/
	Acts_Attack,
	Acts_Defence,
	Acts_Special,
	Acts_Items
};