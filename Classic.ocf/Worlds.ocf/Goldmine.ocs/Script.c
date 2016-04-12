/* Gold mine */

static const SCENARIO_LandscapeWidth_OnePlayer = 640;

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
	// Goal: Resource extraction, set to gold mining.
	var goal = CreateObject(Goal_ResourceExtraction);
	goal->SetResource("Gold", Min(100, 70 + 10 * difficulty));
}

func InitEnvironment(int difficulty)
{
	var time = CreateObject(Time);
	time->SetCycleSpeed(20);

	SetTime(ToSeconds(10));
}


func InitVegetation()
{
	PlaceGrass(85);

	var amount_tree1 = RandomX(50, 75); // 75 is original
	var amount_tree2 = RandomX(40, 50); // 50 is original
	var amount_tree3 = 30 + (75 - amount_tree1)/2; // 30 is original 
	var amount_tree4 = 25 + 50 - amount_tree2; // 25 is original
	
	AutoPlaceVegetation(Tree1, amount_tree1); // 100 == 4 trees with 1 player
	AutoPlaceVegetation(Tree2, amount_tree2); // 100 == 12 trees with 1 player
	AutoPlaceVegetation(Tree3, amount_tree3); // 100 == 7 trees with 1 player
	AutoPlaceVegetation(Tree4, amount_tree4); // 100 == 12 trees with 1 player
}

func InitAnimals(int map_size)
{
	// players are not initialized yet, but the map can expand. Cheat a little here :)
	PlaceAnimals(Bird, Max(1, LandscapeWidth()/SCENARIO_LandscapeWidth_OnePlayer), PLACEMENT_Air);
}

func InitMaterial(int map_size)
{
	// Some objects in the earth.	
	PlaceObjects(Rock, ConvertInEarthAmount(1),"Earth");
	PlaceObjects(Gold, ConvertInEarthAmount(1), "Earth");
	PlaceObjects(Flint, ConvertInEarthAmount(1), "Earth");
	PlaceObjects(Loam, ConvertInEarthAmount(1), "Earth");
}

func InitializePlayer(int player)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	SetWealth(player, 50 - (SCENPAR_Difficulty - 1) * 25); // 50; 25; 0
	
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

	var homeBase = FindObject(Find_ID(ClassicHutWooden), Find_Owner(NO_OWNER), Find_Distance(50, GetHiRank(player)->GetX(), GetHiRank(player)->GetY()));

	if (homeBase)
	{
		homeBase->SetOwner(player);
		homeBase->CreateContents(ClassicFlag);
	}

	return true;
}
