#include Library_Scenario


private func Init_Goals()
{
	AddGoal_Resource(Ore, 70 + 10 * SCENPAR_Difficulty);
}

func Init_Environment()
{
	SetSkyParallax(0, 14, 14, 0, 0, nil, nil);

	AddAmbience_Time();
	
	Volcano->SetMinStrength(20);

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
	Tree1->Place(AdjustToMapSize(1));
	Tree2->Place(AdjustToMapSize(5));
	Tree3->Place(AdjustToMapSize(3));
	Tree4->Place(AdjustToMapSize(30));
	Flower->Place(AdjustToMapSize(5));
	Bone->PlaceOnSurface(AdjustToMapSize(RandomX(2, 7)));
	Skull->PlaceOnSurface(AdjustToMapSize(RandomX(2, 4)));
	PlaceGrass(30);
}

private func Init_Material()
{
	Rock->PlaceOnSurface(AdjustToMapSize(5));
	Rock->PlaceInEarth(5);
	Flint->PlaceInEarth(10);
	Loam->PlaceInEarth(2);
	Gold->PlaceInEarth(1);
}


private func Player_StartingMaterial(int player)
{
	SetWealth(player, 50);
	ClassicHutStone->PlaceHomebase(player);
}

private func Player_InitialKnowledge(int player)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	var vehicleKnowledge =
	[
		ClassicCatapult,
		Balloon
	];

	GivePlayerBasicKnowledge(player);	
	GivePlayerSpecificKnowledge(player, [ClassicHutWooden, ClassicHutStone]);
	GivePlayerCraftingKnowledge(player);
	if (needs_power) GivePlayerPowerKnowledge(player);
	GivePlayerMiningKnowledge(player);
	GivePlayerChemicalKnowledge(player);
	GivePlayerSpecificKnowledge(player, [WoodenBridge]);
	GivePlayerSpecificKnowledge(player, vehicleKnowledge);

	var myHomeBaseMaterial =
	[
		[Conkit, 5],
//		[Linekit, 8],
		[Pipe, 4],
		[Loam, 10],
		[Wood, 5],
		[Metal, 5],
//		[Concrete, 10],
		[Flint, 10],
//		[SuperFlint=2],
		[TFlint, 10],
//		[SuperTFlint=5],
		[ClassicDynamiteBox, 2],
		[ClassicFlag, 3],
		[ClassicClonk, 2],
		[ClassicLorry, 1],
		[ClassicCatapult, 1]
	];

	var myHomeBaseProduction = 
	[
		[Conkit, 2],
//		[Linekit, 8],
		[Pipe, 4],
		[Loam, 20],
		[Wood, 5],
		[Metal, 10],
//		[Concrete, 10],
		[Flint, 10],
//		[SuperFlint, 3],
		[TFlint, 15],
//		[SuperTFlint, 6],
//		[TeraFlint, 1],
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
