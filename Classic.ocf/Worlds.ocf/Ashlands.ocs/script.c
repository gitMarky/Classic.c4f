/* Mountain range */

func Initialize()
{
	// Goal: Resource extraction, set to gold mining.
	var goal = CreateObject(Goal_ResourceExtraction);
	goal->SetResource("Gold");
	
	// Goal: Resource extraction, set to oil extraction.
	//var goal2 = CreateObject(Goal_ResourceExtraction);
	//goal2->SetResource("Oil");
	
	// and gain some money
	var goal3 = CreateObject(Goal_Wealth);
	goal->SetWealthGoal(150);

	var time = CreateObject(Time);
	time->SetCycleSpeed(20);

	SetTime(ToSeconds(10));
	
	
	var burned_trees_1 = AutoPlaceVegetation(Tree1, 32);
	var burned_trees_2 = AutoPlaceVegetation(Tree2, 32);
	var burned_trees_3 = AutoPlaceVegetation(Tree3, 32);
	
	for (var tree in burned_trees_1)
		tree->SetGraphics("Burned");
	for (var tree in burned_trees_2)
		tree->SetGraphics("Burned");
	for (var tree in burned_trees_3)
		tree->SetGraphics("Burned");
	
	AutoPlaceVegetation(Tree2, 6);
	
	PlaceAnimals(ClassicFish, 7, PLACEMENT_Liquid, Material("Water"));
	PlaceAnimals(Bird, 5, PLACEMENT_Air);
	
	return true;
}



func InitializePlayer(int plr)
{
	SetWealth(plr, 100);
	
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
		homeBase->CreateContents(Conkit);
	}

	return true;
}
