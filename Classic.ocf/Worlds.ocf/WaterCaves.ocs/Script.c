#include Library_Scenario

private func Init_Goals()
{
	AddGoal_Wealth(1000); // TODO: Replace with value gain goal
}

func Init_Environment()
{
	//SetGamma(RGB(0,0,0),RGB(68,68,83),RGB(147,147,173));
	AddAmbience_Time();

	// Disasters
	Disaster(Meteor, 0, 2);
	Disaster(Volcano, 0, 4);
	Disaster(Earthquake, 0, 2);
	
	// Clouds
	Cloud->Place(5);
	Cloud->SetPrecipitation("Water", 5 * SCENPAR_Difficulty);
}

private func Init_Vegetation()
{
	Seaweed->Place(AdjustToMapSize(6));
	Coral->Place(AdjustToMapSize(2));
	
	LargeCaveMushroom->Place(AdjustToMapSize(3));
	Mushroom->Place(AdjustToMapSize(10));
	
	// Bush 1
	// Tree burned 2  2
}

private func Init_Material()
{
	Bone->PlaceInEarth(1);
	Rock->PlaceInEarth(4);
	Flint->PlaceInEarth(8);
	Gold->PlaceInEarth(1);
	Loam->PlaceInEarth(10);
}

private func Init_Animals()
{
	Wipf->Place(AdjustToMapSize(3));
	ClassicFish->Place(AdjustToMapSize(3));
	Shark->Place(AdjustToMapSize(2));
	//FireMonsterEgg->PlaceInEarth(4);
	//MonsterEgg->PlaceInEarth(5);
	ZapNest->PlaceInEarth(2);
	Bat->Place(AdjustToMapSize(5));
}

private func Player_StartingMaterial(int player)
{
	SetWealth(player, 30);
	ClassicHutStone->PlaceHomebase(player);
}

private func Player_InitialKnowledge(int player) // TODO
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	GivePlayerBasicKnowledge(player);	
	GivePlayerSpecificKnowledge(player, [ClassicHutWooden, ClassicHutStone]);
	GivePlayerCraftingKnowledge(player);
	if (needs_power) GivePlayerPowerKnowledge(player);
	GivePlayerMiningKnowledge(player);
	GivePlayerChemicalKnowledge(player);
	var myHomeBaseMaterial =
	[
		[Conkit, 5],
		[Pipe, 4],
		[Loam, 10],
		[Wood, 5],
		[Metal, 5],
		[Flint, 10],
		[TFlint, 10],
		[ClassicDynamiteBox, 2],
		[ClassicFlag, 3],
		[ClassicClonk, 2],
		[ClassicLorry, 1],
		[ClassicCatapult, 1]
	];

	var myHomeBaseProduction = 
	[
		[Conkit, 2],
		[Pipe, 4],
		[Loam, 20],
		[Wood, 5],
		[Metal, 10],
		[Flint, 10],
		[TFlint, 15],
		[ClassicDynamiteBox, 2],
		[ClassicClonk, 2],
		[ClassicLorry, 1]
	];

	for (var material in myHomeBaseMaterial)
	{
		DoBaseMaterial(player, material[0], material[1]);
	}
	for (var material in myHomeBaseProduction)
	{
		DoBaseProduction(player, material[0], material[1]);
	}

	return true;
}
