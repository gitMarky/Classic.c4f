/* Mountain range */

func Initialize()
{
	InitRules(SCENPAR_PowerNeed);
	InitGoals(SCENPAR_Difficulty);
	InitEnvironment(SCENPAR_Difficulty);
	InitVegetation();
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
	// Goal: Resource extraction, set to ore mining.
	var goal = CreateObject(Goal_ResourceExtraction);
	goal->SetResource("Ore", Min(100, 70 + 10 * difficulty));
}

func InitEnvironment(int difficulty)
{
	SetSkyParallax(0, 14, 14, 0, 0, nil, nil);

	var time = CreateObject(Time);
	time->SetCycleSpeed(20);

	SetTime(ToSeconds(10));

	// Disasters
	Meteor->SetChance(2 * difficulty);
	Volcano->SetChance(4 * difficulty);
	Earthquake->SetChance(2 * difficulty);
	
	// Clouds
	Cloud->Place(5);
	Cloud->SetPrecipitation("Water", 5 * difficulty);
}

func InitVegetation()
{
	AutoPlaceVegetation(Tree1, 5);
	AutoPlaceVegetation(Tree2, 25);
	AutoPlaceVegetation(Tree3, 15);
	AutoPlaceVegetation(Tree4, 100);
}

func InitMaterial(int map_size)
{
	//InEarth=Rock=5;Flint=10;Loam=2;Gold=1;

	PlaceObjects(Rock, ConvertInEarthAmount(5), "Earth");
	PlaceObjects(Flint, ConvertInEarthAmount(10), "Earth");
	PlaceObjects(Loam, ConvertInEarthAmount(2), "Earth");
	PlaceObjects(Gold, ConvertInEarthAmount(1), "Earth");
}

func InitializePlayer(int player)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	SetWealth(player, 50);
	
	var vehicleKnowledge=
	[
		Catapult,
		Balloon
	];
	
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
		[Catapult, 1]
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

	var homeBase = FindObject(Find_ID(ClassicHutStone), Find_Distance(50, GetHiRank(player)->GetX(), GetHiRank(player)->GetY()));

	if (homeBase)
	{
		homeBase->SetOwner(player);
		homeBase->CreateContents(ClassicFlag);
	}

	return true;
}
