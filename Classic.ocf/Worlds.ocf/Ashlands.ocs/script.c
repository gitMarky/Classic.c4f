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
	
	Stalactite->Place(AdjustToMapSize(10));
}

private func Init_Vegetation()
{
	CallForEach(Tree1->Place(10), "SetBurned");
	CallForEach(Tree2->Place(10), "SetBurned");
	CallForEach(Tree3->Place(10), "SetBurned");
	
	Tree2->Place(6);

	PlaceGrass(55);
	
	for (var grass in FindObjects(Find_ID(Grass)))
	{
		grass->SetClrModulation(RGB(225+Random(30), Random(30), Random(30)));
	}
	
	Skull->PlaceOnSurface(AdjustToMapSize(5));
	Bone->PlaceOnSurface(AdjustToMapSize(15));
	Coal->PlaceOnSurface(AdjustToMapSize(7));
	
	LargeCaveMushroom->Place(7);
}

private func Init_Animals()
{
	ClassicFish->Place(AdjustToMapSize(7));
	Bird->Place(AdjustToMapSize(5));

	var relative = 7;
	var level = 48;
	MonsterEgg->PlaceInEarth(1, relative, level, 10);
	FireMonsterEgg->PlaceInEarth(2, relative, level, 10);
	ZapNest->PlaceInEarth(4, relative, level, 10);
}

private func Init_Material()
{
	var relative = 15;
	var level = 48;
	Rock->PlaceInEarth(4, relative, level);
	Loam->PlaceInEarth(5, relative, level);
	Flint->PlaceInEarth(3, relative, level);
	Gold->PlaceInEarth(3, relative, level);
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
