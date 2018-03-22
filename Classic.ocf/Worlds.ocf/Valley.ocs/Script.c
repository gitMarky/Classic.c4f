#include Library_Scenario

local homebase_locations, area_skylands, area_lake;


private func Initialize()
{
	homebase_locations = [{x = RandomX(95, 145), y = 825, used = false}, {x = RandomX(1275, 1335), y = 825, used = false}];
	area_skylands = Rectangle(0, 0, LandscapeWidth(), 869);
	area_lake = Rectangle(150, 870, LandscapeWidth()-300, LandscapeHeight()-870);
	_inherited(...);
}

private func Init_Goals()
{
	if (SCENPAR_Goal == 1) // Find the crown
	{
		var chest_a = CreateObject(Chest, 380, 200);
		var chest_b = CreateObject(Chest, 1000, 210);
		
		if (Random(2))
		{
			chest_a->CreateContents(Crown);
		}
		else
		{
			chest_b->CreateContents(Crown);
		}
		
		CreateObject(Goal_GetCrown);
	}
	else if (SCENPAR_Goal == 2) // Settlement
	{
		var goal = CreateObject(Goal_Construction);
		goal->AddConstruction(ClassicHutStone, 5);
		goal->AddConstruction(Sawmill, 1);
		goal->AddConstruction(ClassicFoundry, 1);
		goal->AddConstruction(ClassicWorkshop, 1);
		goal->AddConstruction(ClassicChemicalFactory, 1);
		goal->AddConstruction(ClassicCastle, 1);
	}
}

private func Init_Environment()
{
	AddAmbience_Time(17);

	Cloud->Place(15);
	Cloud->SetLightning(5 * SCENPAR_Difficulty);
	
	Earthquake->SetChance(2 * SCENPAR_Difficulty);
	Rockfall->SetChance(2 * SCENPAR_Difficulty);
	Rockfall->SetArea(Rectangle(50, 0, LandscapeWidth()-100, 50));
}

private func Init_Vegetation()
{
	PlaceGrass(85);

	Tree1->Place(2, area_skylands);
	Tree2->Place(4, area_skylands);
	Tree3->Place(5, area_skylands);
	
	Tree1->Place(6, area_lake);
	Tree2->Place(9, area_lake);
	Tree3->Place(9, area_lake);

	Seaweed->Place(25, area_lake);
	Coral->Place(5, area_lake);
	Branch->Place(20, area_skylands);
	Flower->Place(20);
}

private func Init_Animals()
{
	ClassicFish->Place(AdjustToMapSize(15), area_lake);
	Bird->Place(AdjustToMapSize(5), area_skylands);
}

private func Init_Material()
{
	var level = 50;
	var relative = 4;
	Rock->PlaceInEarth(1, relative, level);
	Gold->PlaceInEarth(1, relative, level);
	Flint->PlaceInEarth(1, relative, level);
	Loam->PlaceInEarth(1, relative, level);
}

private func Player_StartingMaterial(int player)
{
	SetWealth(player, 50 - (SCENPAR_Difficulty - 1) * 25);
	
	// Homebase location
	var i = Random(2);
	
	var location = nil;
	for (var i = 0; (!location || location.used == true); ++i)
	{
		location = homebase_locations[i % 2];
	}
	location.used = true;
	
	// Create homebase with flag
	var homeBase = CreateObject(ClassicHutStone, location.x, location.y, player);
	if (homeBase)
	{
		homeBase->SetOwner(player);
		homeBase->CreateContents(ClassicFlag);
		
		for (var i = 0; i < GetCrewCount(player); ++i)
		{
			GetCrew(player, i)->SetPosition(homeBase->GetX() + RandomX(-10, 10), homeBase->GetDefBottom() - 10);
		}
	}
}

private func Player_InitialKnowledge(int player)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));
	
	var myKnowledge = 
	[
		ClassicCatapult,
		Blimp,
		GunPowder,
		FireBomb
	];

	GivePlayerBasicKnowledge(player);
	GivePlayerSpecificKnowledge(player, [ClassicHutWooden, ClassicHutStone, ClassicCastle]);
	GivePlayerCraftingKnowledge(player);
	if (needs_power) GivePlayerPowerKnowledge(player);
	GivePlayerMiningKnowledge(player);
	GivePlayerPumpingKnowledge(player);
	GivePlayerChemicalKnowledge(player);
	GivePlayerSpecificKnowledge(player, myKnowledge);
	GivePlayerSpecificKnowledge(player, [WoodenBridge]);

	return true;
}
