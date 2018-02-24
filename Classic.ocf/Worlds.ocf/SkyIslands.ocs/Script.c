#include Library_Scenario


private func Init_Environment()
{
	//SetGamma(RGB(10, 9, 10), RGB(161, 157, 159), RGB(255, 254, 255), 2);
	AddAmbience_Time();
	
	// Bird song
	var birds = Ambience_Sounds->PlaceOnSurface(AdjustToMapSize(10), nil, {location = Loc_Space(30, CNAT_Top)});
	for (var bird in birds)
	{
		bird->SetSound("Ambience::BirdSong?")
		    ->SetInterval(25)
		    ->SetChance(13)
		    ->SetCondition(Global.IsDay)
		    ->Wait(RandomX(1, 10) * 25);
		bird->MovePosition(0, -30);
	}
	
	// Clouds
	Cloud->Place(5);
	Cloud->SetLightning(10 * SCENPAR_Difficulty);
}

private func Init_Vegetation()
{
	Tree1->Place(AdjustToMapSize(3));
	Tree2->Place(AdjustToMapSize(6));
	Tree3->Place(AdjustToMapSize(3));
	Tree4->Place(AdjustToMapSize(3));
	Vine->Place(AdjustToMapSize(5));
	Branch->Place(AdjustToMapSize(5));
	Flower->Place(AdjustToMapSize(5));
	PlaceGrass(90);
}

private func Init_Material()
{
	PlaceControl()->SetLevel(65);
	var relative = 4;
	var size = ConvertInMapAmount(65);
	var earth = "Earth";
	Flint->PlaceInMaterial(earth, 1, relative, size);
	Gold->PlaceInMaterial(earth, 1, relative, size);
	Loam->PlaceInMaterial(earth, 1, relative, size);
	Rock->PlaceInMaterial(earth, 1, relative, size);
}

private func Init_Animals()
{
	Bird->Place(AdjustToMapSize(3));
	var size = ConvertInMapAmount(60);
	MonsterEgg->PlaceInMaterial("Earth", 7, 11, size, 10);
	ZapNest->PlaceInMaterial("Earth", 4, 11, size, 10);
}

private func Player_StartingMaterial(int player)
{
	SetWealth(player, 70);
	ClassicHutWooden->PlaceHomebase(player);
}
