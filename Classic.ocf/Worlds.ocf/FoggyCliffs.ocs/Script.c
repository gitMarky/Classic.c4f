#include Library_Scenario

private func Init_Environment()
{
	//SetGamma(RGB(15, 15, 15), RGBa(118, 118, 118), RGBa(215, 215, 215), 2);
	SetSkyParallax(0, 15, 17, 0, 0, 0, 0); 
	
	AddAmbience_Time();
	
	SeaSounds(7);
	SeaGulls(4);

	Disaster(Meteor, 4, 1);
	Disaster(Earthquake, 2, 1);

	Cloud->Place(25);
	Cloud->SetLightning(1);

	//Nebel platzieren
	//for(var i;i<260;++i) 
	//	CreateParticle("Fog",Random(LandscapeWidth()),Random(LandscapeHeight()*2/3),RandomX(3,9),0,RandomX(1000,1500));
	//Wipfe platzieren
	/*
	while(pWipf=FindObject(WIPF,0,0,0,0,0,0,0,0,pWipf)) {
		iTimeout=0;
		while(Stuck(pWipf)||GetMaterial(GetX(pWipf),GetY(pWipf))!=Material("Tunnel")) {
			SetPosition(Random(LandscapeWidth()),RandomX(LandscapeHeight()*2/3,LandscapeHeight()),pWipf);
			if(iTimeout++ > 50000) { RemoveObject(pWipf); break; }
		}
	}
	*/
	//ScriptGo(1);
}


private func Init_Vegetation()
{
	// Shell, 1
	// Idol, 1
	Tree2->Place(AdjustToMapSize(17));
	Tree3->Place(AdjustToMapSize(25));

	Fern->Place(AdjustToMapSize(7));

	Branch->Place(AdjustToMapSize(7));
	PlaceGrass(60);

	Seaweed->Place(AdjustToMapSize(90));
	Coral->Place(AdjustToMapSize(20));
}

private func Init_Material()
{
	Gold->PlaceInEarth(AdjustToMapSize(3));
	Loam->PlaceInEarth(AdjustToMapSize(3));
	Rock->PlaceInEarth(AdjustToMapSize(3));
}

private func Init_Animals()
{
	ClassicFish->Place(AdjustToMapSize(25));
	Wipf->Place(AdjustToMapSize(6));
	// MonsterEgg->PlaceInEarth(AdjustToMapSize(1));
	ZapNest->PlaceInEarth(AdjustToMapSize(3));
}

private func Player_StartingMaterial(int player)
{
	SetWealth(player, 50);
	ClassicHutWooden->PlaceHomebase(player);
}

/*
func Script0()
{
	CreateParticle("Fog",0,Random(LandscapeHeight()*2/3),RandomX(3,9),0,RandomX(1000,1500)); 
}

func Script4()
{
	return(goto(0));
}
*/
//Sound-Objekte platzieren

private func SeaSounds(int amount)
{
	var ambience = Ambience_Sounds->PlaceByCriteria(amount, Loc_And(Loc_Material("Water"), Loc_Func(Scenario.Loc_SeaLevel), Loc_Func(Scenario.Loc_SeaSound)));
	
	for (var sound in ambience)
	{
		sound->SetSound("Ambience::Wave?")
		     ->SetInterval(35)
		     ->SetChance(RandomX(40, 80))
		     ->SetIcon(Water);
	}
}

private func SeaGulls(int amount)
{
	var ambience = Ambience_Sounds->PlaceByCriteria(amount, Loc_And(Loc_Material("Sky"), Loc_Func(Scenario.Loc_SeaGull), Loc_Func(Scenario.Loc_SeaSound)));
	
	for (var sound in ambience)
	{
		sound->SetSound("Ambience::SeaSounds1")
		     ->SetInterval(80)
		     ->SetChance(RandomX(60, 80))
		     ->SetIcon(Bird);
	}
}

private func Loc_SeaLevel(int x, int y)
{
	return !GBackSemiSolid(x, y - 5);
}

private func Loc_SeaGull(int x, int y)
{
	return (Material("Earth") == GetMaterial(x, y + 105)) && PathFree(x, y, x, y + 100);
}

private func Loc_SeaSound(int x, int y)
{
	return !FindObject(Find_ID(Ambience_Sounds), Find_Distance(LandscapeWidth() / 20, x, y));
}
