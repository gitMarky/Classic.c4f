/* Gold mine */

static g_highest_plr_count; // max number of players that were ever in the round

static const SCENARIO_LandscapeWidth_OnePlayer = 640;

func Initialize()
{
	// Environment.
	PlaceGrass(85);

	// Goal: Resource extraction, set to gold mining.
	var goal = CreateObject(Goal_ResourceExtraction);
	goal->SetResource("Gold");


	var time = CreateObject(Time);
	time->SetCycleSpeed(20);

	SetTime(Time(10));
	
	var amount_tree1 = RandomX(50, 75); // 75 is original
	var amount_tree2 = RandomX(40, 50); // 50 is original
	var amount_tree3 = 30 + (75 - amount_tree1)/2; // 30 is original 
	var amount_tree4 = 25 + 50 - amount_tree2; // 25 is original
	
	AutoPlaceVegetation(Tree1, amount_tree1); // 100 == 4 trees with 1 player
	AutoPlaceVegetation(Tree2, amount_tree2); // 100 == 12 trees with 1 player
	AutoPlaceVegetation(Tree3, amount_tree3); // 100 == 7 trees with 1 player
	AutoPlaceVegetation(Tree4, amount_tree4); // 100 == 12 trees with 1 player
	
	// players are not initialized yet, but the map can expand. Cheat a little here :)
	PlaceAnimals(Bird, Max(1, LandscapeWidth()/SCENARIO_LandscapeWidth_OnePlayer), PLACEMENT_Air);

	return true;
}



func InitializePlayer(int plr)
{
	SetWealth(plr, 50);
	
	var myHomeBaseMaterial =
	[
		[Conkit,5],
		[Loam,6],
		[Wood,4],
		[Metal,5], 
		[Flint,5], 
		[Sulphur,3], 
		[Barrel,5], 
		[ClassicFlag,3], 
		[ClassicClonk,3], 
		[ClassicLorry,2], 
		[Bread,5]
	];
	var myHomeBaseProduction = 
	[
		[Conkit,5], 
		[Loam,6], 
		[Wood,5], 
		[Metal,3], 
		[Flint,5], 
		[Sulphur,2], 
		[Barrel,5], 
		[ClassicFlag,3], 
		[ClassicClonk,2], 
		[ClassicLorry,1], 
		[Bread,5]
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
	}

	// Update goal: More players need to mine more gold
	if (GetPlayerCount() > g_highest_plr_count)
	{
		g_highest_plr_count = GetPlayerCount();
		var goal = FindObject(Find_ID(Goal_Wealth));
		if (goal)
		{
			goal->SetWealthGoal(BoundBy(125+75*g_highest_plr_count, 225, 300));
		}
	}
	return true;
}
