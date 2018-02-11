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
	Tree1->PlaceByMapSize(1);
	Tree2->PlaceByMapSize(2);
	Tree3->PlaceByMapSize(1);
	Tree4->PlaceByMapSize(1);
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

private func Player_StartingMaterial(int player)
{
	SetWealth(player, 70);
	ClassicHutWooden->PlaceHomebase(player);
}
