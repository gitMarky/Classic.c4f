#include Library_Scenario

private func Init_Goals()
{
	AddGoal_Wealth(100 + 50 * SCENPAR_Difficulty);
	AddGoal_Resource(Gold, 70 + 10 * SCENPAR_Difficulty);
	//AddGoal_Resource(Oil, 70 + 10 * SCENPAR_Difficulty);
}

private func Init_Environment()
{
	// Starting time & special sky color
	AddAmbience_Time(10).daycolour_global = [158, 65, 47];

	// Some dark clouds which rain few ashes.
	Cloud->Place(15);
	Cloud->SetPrecipitation("Ashes", 5 * SCENPAR_Difficulty);
	Cloud->SetCloudRGB(60, 35, 25);
	Cloud->SetLightning(5 + 5 * SCENPAR_Difficulty);

	// Some natural disasters
	Disaster(Earthquake, 2, 3);
	Disaster(Meteor, 2, 1);
	Disaster(Volcano, 2, 1, 2);
}

private func Init_Vegetation()
{
	var burned_trees_1 = Tree1->Place(32);
	var burned_trees_2 = Tree2->Place(32);
	var burned_trees_3 = Tree3->Place(32);
	
	for (var tree in burned_trees_1)
		tree->SetBurned();
	for (var tree in burned_trees_2)
		tree->SetBurned();
	for (var tree in burned_trees_3)
		tree->SetBurned();
	
	Tree2->Place(6);

	PlaceGrass(15);
	
	for (var grass in FindObjects(Find_ID(Grass)))
	{
		grass->SetClrModulation(RGB(225+Random(30), Random(30), Random(30)));
	}
}

private func Init_Animals()
{
	ClassicFish->PlaceByMapSize(7);
	Bird->PlaceByMapSize(5);
}

private func Init_Material()
{
	PlaceInEarth(Rock, 4);
	PlaceInEarth(Loam, 5);
	PlaceInEarth(Flint, 3);
	PlaceInEarth(Gold, 3);
}

private func Player_InitialKnowledge(int player)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	var itemKnowledge =
	[
		FireBomb,
//		Sailboat,
//		Balloon,
//		Dynamo,
//		Tower
		];

	GivePlayerBasicKnowledge(player);
	GivePlayerSpecificKnowledge(player, itemKnowledge);
	GivePlayerSpecificKnowledge(player, [ClassicHutWooden, ClassicHutStone, Sawmill, ClassicFoundry]);
	if (needs_power) GivePlayerPowerKnowledge(player);
	GivePlayerMiningKnowledge(player);
	GivePlayerPumpingKnowledge(player);	
	GivePlayerChemicalKnowledge(player);

	var myHomeBaseMaterial =
	[
		[Conkit, 3],
//		[Linekit, 6],
		[Pipe, 3],
		[Loam, 20],
		[Wood, 5],
		[Metal, 5],
//		[Concrete, 20],
		[Flint, 6],
		[TFlint, 7],
//		[SuperTFlint, 3],
		[ClassicDynamiteBox, 1],
		[FireBomb, 2],
		[GunPowder, 6],
		[MetalBarrel, 8],
		[ClassicFlag, 1],
		[ClassicClonk, 5],
		[ClassicLorry, 1],
		[ClassicCatapult, 1]
//		[Sailboat, 1]
	];
	var myHomeBaseProduction = 
	[
		[Conkit, 3],
//		[Linekit, 6],
		[Pipe, 3],
		[Loam, 12],
		[Wood, 18],
		[Metal, 5],
//		[Concrete, 8],
		[Flint, 6],
		[TFlint, 7],
//		[SuperTFlint, 5],
		[ClassicDynamiteBox, 3],
//		[TeraFlint, 1],
		[FireBomb, 2],
		[GunPowder, 10],
		[MetalBarrel, 3],
//		[BombArrowPack, 2],
		[ClassicFlag, 3],
		[ClassicClonk, 5]
	];

	for (var material in myHomeBaseMaterial)
	{
		DoBaseMaterial(player, material[0], material[1]);
	}
	for (var material in myHomeBaseProduction)
	{
		DoBaseProduction(player, material[0], material[1]);
	}
}

private func Player_StartingMaterial(int player)
{
	SetWealth(player, 100);
	
	var loc_lake = Loc_InRect(LandscapeWidth() / 2 - 150, 0, 300, LandscapeHeight());
	var homeBase = ClassicHutWooden->PlaceHomebase(player, {location = Loc_And(Loc_Sky(), Loc_Not(loc_lake))});

	homeBase->CreateContents(Wood, 3);
	homeBase->CreateContents(Rock, 5);
	homeBase->CreateContents(Conkit);
}
