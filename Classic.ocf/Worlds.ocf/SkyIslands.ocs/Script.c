#include Library_Scenario


private func Init_Environment()
{
	//SetGamma(RGB(10, 9, 10), RGB(161, 157, 159), RGB(255, 254, 255), 2);
	AddAmbience_Time();
	
	// Clouds
	Cloud->Place(5);
	Cloud->SetLightning(10 * SCENPAR_Difficulty);
}

private func Init_Vegetation()
{
	AutoPlaceVegetation(Tree1, 1);
	AutoPlaceVegetation(Tree2, 2);
	AutoPlaceVegetation(Tree3, 1);
	AutoPlaceVegetation(Tree4, 1);
}

private func Init_Material()
{
	PlaceInEarth(Flint, 1);
	PlaceInEarth(Gold, 1);
	PlaceInEarth(Loam, 1);
	PlaceInEarth(Rock, 1);
}

private func Init_Animals()
{
	Bird->PlaceByMapSize(3);
	// PlaceInEarth(MonsterEgg, 7);
	PlaceInEarth(ZapNest, 4);
}
