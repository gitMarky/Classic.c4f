/* Gold mine */

static g_highest_plr_count; // max number of players that were ever in the round

func Initialize()
{
	// Environment.
	PlaceGrass(85);

	// Goal: Resource extraction, set to gold mining.
	var goal = CreateObject(Goal_ResourceExtraction);
	goal->SetResource("Gold");


	// Ambient clouds
	//Cloud->Place(1);


	var time = CreateObject(Environment_Time);
	//time->SetTime(Time(17));//SetTime(60*12);
	time->SetCycleSpeed(20);

	SetTime(Time(17));

	//var bird = CreateObject(Bird, LandscapeWidth()/2, 100, -1);
	
	//Vegetation=Tree1=3;Tree2=5;Tree3=5;
	PlaceVegetationEx(Tree1, 3 * 3, nil, nil, nil, false, false, [0, 100], [-30, 30]);
	PlaceVegetationEx(Tree2, 3 * 5, nil, nil, nil, false, false, [0, 100], [-30, 30]);
	PlaceVegetationEx(Tree3, 3 * 5, nil, nil, nil, false, false, [0, 100], [-30, 30]);

	return true;
}

func InitializePlayer(int plr)
{
	SetWealth(plr, 50);
	
	var myHomeBaseMaterial =
	[
		[Conkit,5],
		[Pipe,3],
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
		[Pipe,2],
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
