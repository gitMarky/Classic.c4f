#include Library_Scenario

private func Init_Environment()
{
	//SetGamma(RGB(15, 15, 15), RGBa(118, 118, 118), RGBa(215, 215, 215), 2);
	SetSkyParallax(0, 15, 17, 0, 0, 0, 0); 
	
	Meeresrauschen(170);
	Meeresrauschen(1100);
	Meeresrauschen(2060);
	Meeresrauschen(2900);
	Meeresrauschen(3800);
	Meeresrauschen(4800);
	Meeresrauschen(5700);
	Moewen(900);
	Moewen(2300);
	Moewen(3900);
	Moewen(5000);
	
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
	AutoPlaceVegetation(Tree2, 2);
	AutoPlaceVegetation(Tree3, 3);
}

private func Init_Material()
{
	PlaceInEarth(Gold, 1);
	PlaceInEarth(Loam, 1);
	PlaceInEarth(Rock, 1);
}

private func Init_Animals()
{
	ClassicFish->PlaceByMapSize(5);
	Wipf->PlaceByMapSize(6);
	// PlaceInEarth(MonsterEgg, 1);
	PlaceInEarth(ZapNest, 3);
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

private func Meeresrauschen(int x)
{
	//ObjectSetAction(CreateObject(SL9Z, x,LandscapeHeight()/2,-1),"Meer");
}
	
private func Moewen(int x)
{
	//ObjectSetAction(CreateObject(SL9Z, x,LandscapeHeight()/3,-1),"Moewen");
}
