/* Ash lands */

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

func InitializePlayer(int player)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	SetWealth(player, 100);
	
	var itemKnowledge =
	[
		FireBomb,
//		Sailboat,
//		Balloon,
//		Dynamo,
//		Tower
		];
	
	GivePlayerSpecificKnowledge(player, itemKnowledge);
	GivePlayerSpecificKnowledge(player, [ClassicHutWooden, ClassicHutStone, Sawmill]);
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
		[Catapult, 1]
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
		DoBaseMaterial(player, material[0], material[1]);
	}
	for (var material in myHomeBaseProduction)
	{
		DoBaseProduction(player, material[0], material[1]);
	}

	CreateHomeBase(player);

	return true;
}

func CreateHomeBase(int player)
{
	var found_position = false;
	var x, y;

	while (!found_position)
	{
		x = 50 + Random(LandscapeWidth() - 100);
		// avoid lake?
	  	while(Inside(x, LandscapeWidth() / 2 - 150, LandscapeWidth() / 2 + 150)) 
	    	x = 50 + Random(LandscapeWidth() - 100);
		y = 0;
		while(!GBackSolid(x, y) && y < LandscapeHeight()) ++y;
		
		if (!FindObject(Find_ID(ClassicHutWooden), Find_Distance(50, x, y)))
		{
			found_position = true;
		}
	}

	var homeBase = CreateObjectAbove(ClassicHutWooden, x, y, player); //FindObject(Find_ID(ClassicHutWooden), Find_Distance(50, GetHiRank(player)->GetX(), GetHiRank(player)->GetY()));

	for (var i = 0; GetCrew(player, i); ++i)
    {
		GetCrew(player, i)->SetPosition(x + RandomX(-8,8), y - 10);
    }

	homeBase->CreateContents(Wood, 3);
	homeBase->CreateContents(Rock, 5);
	homeBase->CreateContents(ClassicFlag);
	homeBase->CreateContents(Conkit);
}
