/* Mountain range */

func Initialize()
{
	InitRules(SCENPAR_PowerNeed);
	InitGoals(SCENPAR_Difficulty);
	InitEnvironment(SCENPAR_Difficulty);
	InitVegetation();
	InitAnimals(SCENPAR_MapSize);
	InitMaterial(SCENPAR_MapSize);
}

func InitRules(need_power)
{
	var rules = [Rule_TeamAccount, Rule_ZoomLimit, Rule_StartingEquipment];
	for (var rule in rules) CreateObject(rule);
	
	if (need_power == 2) CreateObject(Rule_NoPowerNeed);
}

func InitGoals(int difficulty)
{
	// Show wealth in HUD.
	GUI_Controller->ShowWealth();
	
	// Goal: Resource extraction, set to oil extraction.
	//var goal2 = CreateObject(Goal_ResourceExtraction);
	//goal2->SetResource("Oil");
	
	// gain some money
	var goal = CreateObject(Goal_Wealth);
	goal->SetWealthGoal(100 + 50 * difficulty);

	// Goal: Resource extraction, set to gold mining.
	var goal3 = CreateObject(Goal_ResourceExtraction);
	goal3->SetResource("Gold", Min(100, 70 + 10 * difficulty));

}

func InitEnvironment(int difficulty)
{
	var time = CreateObject(Time);
	time.daycolour_global = [158, 65, 47];
	time->SetCycleSpeed(20);

	SetTime(ToSeconds(10));

	// Some dark clouds which rain few ashes.
	Cloud->Place(15);
	Cloud->SetPrecipitation("Ashes", 5 * difficulty);
	Cloud->SetCloudRGB(60, 35, 25);
	Cloud->SetLightning(5 + 5 * difficulty); // default: 15%

	// Some natural disasters, earthquakes, volcanos, meteorites.
	Earthquake->SetChance(5 * difficulty); // default: 10%
	Meteor->SetChance(2 + 3 * difficulty); // default: 8%
	if (difficulty >= 2) Volcano->SetChance(2 + 3 * difficulty);	// default: 8%
}

func InitVegetation()
{
	var burned_trees_1 = AutoPlaceVegetation(Tree1, 32);
	var burned_trees_2 = AutoPlaceVegetation(Tree2, 32);
	var burned_trees_3 = AutoPlaceVegetation(Tree3, 32);
	
	for (var tree in burned_trees_1)
		tree->SetBurned();
	for (var tree in burned_trees_2)
		tree->SetBurned();
	for (var tree in burned_trees_3)
		tree->SetBurned();
	
	AutoPlaceVegetation(Tree2, 6);
	
	PlaceGrass(15);
	
	for (var grass in FindObjects(Find_ID(Grass)))
	{
		grass->SetClrModulation(RGB(225+Random(30), Random(30), Random(30)));
	}
}

func InitAnimals(int map_size)
{
	PlaceAnimals(ClassicFish, 7, PLACEMENT_Liquid, Material("Water"));
	PlaceAnimals(Bird, 5, PLACEMENT_Air);
}

func InitMaterial(map_size)
{
	// Some objects in the earth.	
	PlaceObjects(Rock, ConvertInEarthAmount(4),"Earth");
	PlaceObjects(Loam, ConvertInEarthAmount(5), "Earth");
	PlaceObjects(Flint, ConvertInEarthAmount(3), "Earth");
	PlaceObjects(Gold, ConvertInEarthAmount(3), "Earth");
}

func InitializePlayer(int plr)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	SetWealth(plr, 100);
	
	var itemKnowledge =
	[
		FireBomb,
//		Sailboat,
//		Balloon,
//		Dynamo,
//		Tower
		];
	
	GivePlayerSpecificKnowledge(plr, itemKnowledge);
	GivePlayerSpecificKnowledge(plr, [ClassicHutWooden, ClassicHutStone, Sawmill]);
	if (needs_power) GivePlayerPowerKnowledge(plr);
	GivePlayerMiningKnowledge(plr);
	GivePlayerPumpingKnowledge(plr);	
	GivePlayerChemicalKnowledge(plr);
	
	var myHomeBaseMaterial =
	[
		[Conkit, 3],
//		[Linekit, 6],
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
		[Catapult, 1]
//		[Sailboat, 1]
	];
	var myHomeBaseProduction = 
	[
		[Conkit, 3],
//		[Linekit, 6],
		[Loam, 12],
		[Wood, 18],
		[Metal, 5],
//		[Concrete, 8],
		[Flint, 6],
		[TFlint, 7],
//		[SuperTFlint, 5],
		[ClassicDynamiteBox, 3],
//		[TeraFlint,1],
		[FireBomb, 2],
		[GunPowder, 10],
		[MetalBarrel, 3],
//		[BombArrowPack, 2],
		[ClassicFlag, 3],
		[ClassicClonk, 5]
	];
	
	for (var material in myHomeBaseMaterial)
	{
		DoBaseMaterial(plr, material[0], material[1]);
	}
	for (var material in myHomeBaseProduction)
	{
		DoBaseProduction(plr, material[0], material[1]);
	}

	var homeBase = FindObject(Find_ID(ClassicHutWooden), Find_Distance(50, GetHiRank(plr)->GetX(), GetHiRank(plr)->GetY()));

	if (homeBase)
	{
		homeBase->SetOwner(plr);
		homeBase->CreateContents(ClassicFlag);
		homeBase->CreateContents(Conkit);
	}

	return true;
}
