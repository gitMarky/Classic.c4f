/* The chasm */


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

	// gain some money
	var goal = CreateObject(Goal_Wealth);
	goal->SetWealthGoal(100 + 50 * difficulty);

	// Goal: Resource extraction, set to gold mining.
	var goal2 = CreateObject(Goal_ResourceExtraction);
	goal2->SetResource("Gold", Min(100, 30 + 20 * difficulty));
 
}

func InitEnvironment(int difficulty)
{
	var time = CreateObject(Time);
	//time.daycolour_global = [158, 65, 47];
	time->SetCycleSpeed(20);
	
	//SetGamma(RGB(3, 1, 0), RGB(95, 83, 68), RGB(213, 212, 187));
	SetSkyParallax(0, 33, 57, 0, 0, 0, 0); 

	SetTime(ToSeconds(12));

	// Some dark clouds which rain few ashes.
	Cloud->Place(15);
	Cloud->SetPrecipitation("Ashes", 5 * difficulty);
	Cloud->SetCloudRGB(60, 35, 25);
	Cloud->SetLightning(0 + 1 * difficulty); // default: 2%

	// Some natural disasters, earthquakes, volcanos, meteorites.
	if (difficulty >= 2) Meteor->SetChance(4 + 4 * difficulty); // default: 12%
	Volcano->SetChance(3 + 6 * difficulty);	// default: 15%
	Volcano->SetMaterial("DuroLava");
	Earthquake->SetChance(4 * difficulty); // default: 8%
}

func InitVegetation()
{
	var burned_trees_1 = AutoPlaceVegetation(Tree1, 6);

	for (var tree in burned_trees_1)
		tree->~SetBurned();

	AutoPlaceVegetation(Tree1, 15);
	AutoPlaceVegetation(Tree2, 9);
	AutoPlaceVegetation(Tree3, 12);

	PlaceGrass(15);
	
	for (var grass in FindObjects(Find_ID(Grass)))
	{
		grass->SetClrModulation(RGB(225+Random(30), Random(30), Random(30)));
	}
}

func InitAnimals(int map_size)
{
	PlaceAnimals(Bird, 3, PLACEMENT_Air);
	// 2 monster eggs
	// 1 zap nest
	// 4 fire monster eggs
}

func InitMaterial(map_size)
{
	// Some objects in the earth.	
	PlaceObjects(Bone, ConvertInEarthAmount(2),"Earth");
	PlaceObjects(Flint, ConvertInEarthAmount(7), "Earth");
	PlaceObjects(Gold, ConvertInEarthAmount(4), "Earth");
	PlaceObjects(Loam, ConvertInEarthAmount(5), "Earth");
	PlaceObjects(Skull, ConvertInEarthAmount(1),"Earth");
}

func InitializePlayer(int player)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	SetWealth(player, 80);
	
	
	GivePlayerBasicKnowledge(player);
	GivePlayerSpecificKnowledge(player, [ClassicHutWooden, ClassicHutStone]);
	if (needs_power) GivePlayerPowerKnowledge(player);
	GivePlayerCraftingKnowledge(player);
	GivePlayerMiningKnowledge(player);
	GivePlayerPumpingKnowledge(player);	
	GivePlayerChemicalKnowledge(player);
	
	var myHomeBaseMaterial =
	[
		[Conkit, 3],
		[Pipe, 5],
		[Loam, 11],
		[Wood, 12],
		[Metal, 8],
		[Concrete, 9],
		[Flint, 9],
		[TFlint, 14],
		[ClassicDynamiteBox, 1],
		[GunPowder, 1],
		[MetalBarrel, 2],
		[Torch, 4],
		[ClassicFlag, 1],
		[ClassicClonk, 6]
	];
	var myHomeBaseProduction = 
	[
		[Conkit, 3],
		[Pipe, 5],
		[Loam, 11],
		[Metal, 8],
		[Concrete, 9],
		[Flint, 10],
		[TFlint, 10],
		[ClassicDynamiteBox, 1],
		[GunPowder, 11],
		[MetalBarrel, 2],
		[ClassicFlag, 2],
		[ClassicClonk, 3]
	];
	
	for (var material in myHomeBaseMaterial)
	{
		DoBaseMaterial(player, material[0], material[1]);
	}
	for (var material in myHomeBaseProduction)
	{
		DoBaseProduction(player, material[0], material[1]);
	}
	
	var trees = FindObjects(Find_Func("IsTree"));
	var start = trees[Random(GetLength(trees))];
	
	for (var crew in FindObjects(Find_Category(OCF_CrewMember), Find_Owner(player)))
	{
		crew->SetPosition(start->GetX(), start->GetY());
	}

	return true;
}
