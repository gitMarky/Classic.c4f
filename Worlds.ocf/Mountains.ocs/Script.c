/* Mountain range */

func Initialize()
{
	SetSkyParallax(0,14,14, 0,0, nil, nil);

	// Goal: Resource extraction, set to gold mining.
	var goal = CreateObject(Goal_ResourceExtraction);
	goal->SetResource("Ore");

	var time = CreateObject(Environment_Time);
	time->SetCycleSpeed(20);

	SetTime(Time(10));
	
	AutoPlaceVegetation(Tree1, 5);
	AutoPlaceVegetation(Tree2, 25);
	AutoPlaceVegetation(Tree3, 15);
	AutoPlaceVegetation(Tree4, 100);
	
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

	return true;
}
