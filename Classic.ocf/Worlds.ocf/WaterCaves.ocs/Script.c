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
	Disaster(Earthquake, 12, 4);
	
	// Clouds
	Cloud->Place(5);
	Cloud->SetPrecipitation("Water", 5 * SCENPAR_Difficulty);

	// Other
	Stalactite->Place(AdjustToMapSize(25));
	
	// Sounds
	for (var y = 0; y < LandscapeHeight(); y += 510)
	for (var x = 0; x < LandscapeWidth(); x += 530)
	{
		var drip = CreateObject(Ambience_Sounds, x, y, NO_OWNER);
		drip->SetSound("Ambience::CaveDrip?")
            ->SetInterval(800)
            ->SetChance(100)
            ->Wait(RandomX(1, 4) * 50);
	}
}

private func Init_Vegetation()
{
	Seaweed->Place(AdjustToMapSize(70));
	Coral->Place(AdjustToMapSize(10));

	LargeCaveMushroom->Place(AdjustToMapSize(10), nil, {terraform = false});
	Mushroom->Place(AdjustToMapSize(25));

	Branch->Place(AdjustToMapSize(50));
	
	CallForEach(Grass->PlaceOnSurface(AdjustToMapSize(70)), Grass.Randomize, [1, 1, 1, 1, 100, 100, 500, 1000], 50, 200);
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
	ClassicFish->Place(AdjustToMapSize(30));
	Shark->Place(AdjustToMapSize(2));
	//FireMonsterEgg->PlaceInEarth(AdjustToMapSize(4));
	//MonsterEgg->PlaceInEarth(AdjustToMapSize(5));
	ZapNest->PlaceInEarth(AdjustToMapSize(2));
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
