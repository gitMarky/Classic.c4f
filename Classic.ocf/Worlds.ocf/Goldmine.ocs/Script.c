#include Library_Scenario

static const SCENARIO_LandscapeWidth_OnePlayer = 640;


private func Init_Goals()
{
	AddGoal_Resource(Gold, 70 + 10 * SCENPAR_Difficulty);
}

private func Init_Environment()
{
	AddAmbience_Time();
}


private func Init_Vegetation()
{
	PlaceGrass(85);

	Tree1->Place(AdjustToMapSize(4)); // 100 == 4 trees with 1 player
	Tree2->Place(AdjustToMapSize(12)); // 100 == 12 trees with 1 player
	Tree3->Place(AdjustToMapSize(7)); // 100 == 7 trees with 1 player
	Tree4->Place(AdjustToMapSize(12)); // 100 == 12 trees with 1 player
}

private func Init_Animals()
{
	// players are not initialized yet, but the map can expand. Cheat a little here :)
	Bird->Place(AdjustToMapSize(3));
}

private func Init_Material(int map_size)
{
	Rock->PlaceInEarth(AdjustToMapSize(1));
	Gold->PlaceInEarth(AdjustToMapSize(1));
	Flint->PlaceInEarth(AdjustToMapSize(1));
	Loam->PlaceInEarth(AdjustToMapSize(1));
}

private func Player_StartingMaterial(int player)
{
	SetWealth(player, 50 - (SCENPAR_Difficulty - 1) * 25); // 50; 25; 0
	ClassicHutWooden->PlaceHomebase(player);
}

private func Player_InitialKnowledge(int player)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	var myHomeBaseMaterial =
	[
		[Conkit, 5],
		[Loam, 6],
		[Wood, 4],
		[Metal, 5], 
		[Flint, 5],
		[TFlint, 5],
		[Sulphur, 3], 
		[Barrel, 5], 
		[ClassicFlag, 3], 
		[ClassicClonk, 3], 
		[ClassicLorry, 2], 
		[Bread, 5]
	];
	var myHomeBaseProduction = 
	[
		[Conkit, 5], 
		[Loam, 6], 
		[Wood, 5], 
		[Metal, 3], 
		[Flint, 5], 
		[TFlint, 5], 
		[Sulphur, 2], 
		[Barrel, 5], 
		[ClassicFlag, 3], 
		[ClassicClonk, 2], 
		[ClassicLorry, 1], 
		[Bread, 5]
	];

	for (var material in myHomeBaseMaterial)
	{
		DoBaseMaterial(player, material[0], material[1]);
	}
	for (var material in myHomeBaseProduction)
	{
		DoBaseProduction(player, material[0], material[1]);
	}
	
	GivePlayerBasicKnowledge(player);
	GivePlayerSpecificKnowledge(player, [TFlint]);
	GivePlayerSpecificKnowledge(player, [ClassicHutWooden, Sawmill, ClassicWorkshop, ClassicChemicalFactory]);
	if (needs_power) GivePlayerSpecificKnowledge(player, [ClassicWindmill]);
	GivePlayerMiningKnowledge(player);
	return true;
}
