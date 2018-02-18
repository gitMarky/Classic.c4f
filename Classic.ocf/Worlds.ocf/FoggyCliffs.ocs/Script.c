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

	Cloud->Place(5);
	Cloud->SetLightning(1);

	var fog_interval = 150;
	var fog_start = -200; // Fog starts at this x position usually
	var fog_velocity = 5;
	var fog_range = (LandscapeWidth() + 2 * Abs(fog_start)) * 10 / fog_velocity; // the average fog particle needs this many frames to traverse the landscape
	for (var frame = 0; frame < fog_range; frame += fog_interval)
	{
		var pos = fog_start + frame * fog_velocity / 10;
		DoFog(PV_Random(pos - 50, pos + 50));
	}

	CreateEffect(FxFoggyCliffs, 1, fog_interval);
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
	
	// Place wipfs in tunnels
	for (var wipf in FindObjects(Find_ID(Wipf)))
	{
		if (wipf->GetMaterial() != Material("Tunnel"))
		{
			var location = FindLocation(Loc_Wall(CNAT_Bottom), Loc_Tunnel(), Loc_Space(wipf->GetDefHeight(), CNAT_Top));
			if (location)
			{
				wipf->SetPosition(location.x, location.y - wipf->GetBottom());
			}
		}
	}
}

private func Player_StartingMaterial(int player)
{
	SetWealth(player, 50);
	ClassicHutWooden->PlaceHomebase(player);
}


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

local FxFoggyCliffs = new Effect
{
	Timer = func ()
	{
		DoFog(-200);
	}
};

global func DoFog(x, int amount)
{
	var particles =
	{
		Prototype = Particles_Cloud(),
		Alpha = PV_Random(150, 50),
		Size = PV_Random(300, 500),
	};

	CreateParticle("Fog", x, Random(LandscapeHeight()*2/3), PV_Random(3,9), 0, 0, particles, amount); 
}
