/* Gold mine */

static g_highest_plr_count; // max number of players that were ever in the round

func Initialize()
{
	var area_skylands = Rectangle(0, 0, LandscapeWidth(), 869);
	var area_lake = Rectangle(150, 870, LandscapeWidth()-300, LandscapeHeight()-870);
	var area_lake = Rectangle(150, 870, LandscapeWidth()-300, LandscapeHeight()-870);

	InitRules(SCENPAR_PowerNeed);
	InitGoals();
	InitEnvironment(SCENPAR_Difficulty);
	InitVegetation(area_lake, area_skylands);
	InitMaterial();
	InitAnimals(SCENPAR_Difficulty, area_lake, area_skylands);
}

func InitRules(need_power)
{
	var rules = [Rule_TeamAccount, Rule_ZoomLimit, Rule_StartingEquipment];
	for (var rule in rules) CreateObject(rule);

	if (need_power == 2) CreateObject(Rule_NoPowerNeed);
}

func InitGoals()
{
	if (SCENPAR_Goal == 1) // find the crown
	{
		// TODO
	}
	else if (SCENPAR_Goal == 2) // settlement
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

func InitEnvironment(int difficulty)
{
	var time = CreateObject(Time);
	time->SetCycleSpeed(20);

	SetTime(ToSeconds(17));

	Cloud->Place(15);
	Cloud->SetLightning(5 * difficulty);
	Earthquake->SetChance(2 * difficulty);
	Rockfall->SetChance(2 * difficulty);
	Rockfall->SetArea(Rectangle(50, 0, LandscapeWidth()-100, 50));
}

func InitVegetation(proplist area_lake, proplist area_skylands)
{
	PlaceGrass(85);
	
	AutoPlaceVegetation(Tree1, 10, PLACEMENT_Amount_Relative, area_skylands);
	AutoPlaceVegetation(Tree2, 20, PLACEMENT_Amount_Relative, area_skylands);
	AutoPlaceVegetation(Tree3, 15, PLACEMENT_Amount_Relative, area_skylands);
	
	AutoPlaceVegetation(Tree1, 30, PLACEMENT_Amount_Relative, area_lake);
	AutoPlaceVegetation(Tree2, 45, PLACEMENT_Amount_Relative, area_lake);
	AutoPlaceVegetation(Tree3, 45, PLACEMENT_Amount_Relative, area_lake);

	Seaweed->Place(25, area_lake);
	Coral->Place(5, area_lake);
	Branch->Place(20, area_skylands);
	Flower->Place(20);
}

func InitAnimals(int difficulty, proplist area_lake, proplist area_skylands)
{
	PlaceAnimals(ClassicFish, 15, PLACEMENT_Liquid, Material("Water"), area_lake);
	PlaceAnimals(Bird, 5, PLACEMENT_Air, nil, area_skylands);
}

func InitMaterial()
{
	// Some objects in the earth.	
	PlaceObjects(Rock, ConvertInEarthAmount(1),"Earth");
	PlaceObjects(Gold, ConvertInEarthAmount(1), "Earth");
	PlaceObjects(Flint, ConvertInEarthAmount(1), "Earth");
	PlaceObjects(Loam, ConvertInEarthAmount(1), "Earth");
}


func InitializePlayer(int plr)
{
	SetWealth(plr, 50 - (SCENPAR_Difficulty - 1) * 25);
	
	var myHomeBaseMaterial =
	[
		[Conkit, 5],
		[Pipe, 3],
		[Loam, 6],
		[Wood, 4],
		[Metal, 5], 
		[Flint, 5], 
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
		[Pipe, 2],
		[Loam, 6], 
		[Wood, 5], 
		[Metal, 3], 
		[Flint, 5], 
		[Sulphur, 2], 
		[Barrel, 5], 
		[ClassicFlag, 3], 
		[ClassicClonk, 2], 
		[ClassicLorry, 1], 
		[Bread, 5]
	];

	for (var material in myHomeBaseMaterial)
	{
		DoBaseMaterial(plr, material[0], material[1]);
	}
	for (var material in myHomeBaseProduction)
	{
		DoBaseProduction(plr, material[0], material[1]);
	}


	var homeBase = FindObject(Find_ID(ClassicHutWooden), Find_Owner(NO_OWNER), Find_Distance(50, GetHiRank(plr)->GetX(), GetHiRank(plr)->GetY()));

	if (homeBase)
	{
		homeBase->SetOwner(plr);
		homeBase->CreateContents(ClassicFlag);
	}
	return true;
}
