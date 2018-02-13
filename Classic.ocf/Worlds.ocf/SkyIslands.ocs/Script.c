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
	Tree1->Place(AdjustToMapSize(1));
	Tree2->Place(AdjustToMapSize(2));
	Tree3->Place(AdjustToMapSize(1));
	Tree4->Place(AdjustToMapSize(1));
}

private func Init_Material()
{
	Flint->PlaceInEarth(AdjustToMapSize(1));
	Gold->PlaceInEarth(AdjustToMapSize(1));
	Loam->PlaceInEarth(AdjustToMapSize(1));
	Rock->PlaceInEarth(AdjustToMapSize(1));
}

private func Init_Animals()
{
	Bird->Place(AdjustToMapSize(3));
	// MonsterEgg->PlaceInEarth(AdjustToMapSize(7));
	ZapNest->PlaceInEarth(AdjustToMapSize(4));
}

private func Player_StartingMaterial(int player)
{
	SetWealth(player, 70);
	ClassicHutWooden->PlaceHomebase(player);
}
