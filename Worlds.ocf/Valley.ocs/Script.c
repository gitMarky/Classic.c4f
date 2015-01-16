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

	return true;
}

func InitializePlayer(int plr)
{
	SetWealth(plr, 50);

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
