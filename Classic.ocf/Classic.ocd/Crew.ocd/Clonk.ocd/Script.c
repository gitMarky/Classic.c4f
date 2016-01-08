/*
	Classic Clonk
	Author: Marky

	The protoganist of the game. Witty and nimble if skillfully controlled ;-)
*/

#include Clonk

/* Classic clonks do not have backpacks ;) */

func AttachBackpack()
{
}

func RemoveBackpack()
{
}


//private func DiggingProcess()
//{
//	SetXDir(this.dig_xdir,100); SetYDir(this.dig_ydir,100);
//	return true;
//}

func SetSkin(int new_skin)
{
	// Remember skin
	skin = new_skin;

	//Adventurer
	if(skin == 0)
	{	skin_name = nil;
		gender = 0;	}

	//Steampunk
	if(skin == 1)
	{	skin_name = "Steampunk";
		gender = 1; }

	//Alchemist
	if(skin == 2)
	{	skin_name = "Alchemist";
		gender = 0;	}
	
	//Farmer
	if(skin == 3)
	{	skin_name = "Farmer";
		gender = 1;	}
		
	var material_name = Format("Clonk%sClassic", skin_name ?? "");

	SetGraphics(skin_name, Clonk);
	SetMeshMaterial(material_name);
	if (skin == 2) SetMeshMaterial(material_name, 1);
	//RemoveBackpack(); //add a backpack
	//AttachBackpack();
	SetAction("Jump"); //refreshes animation

	return skin;
}


local ActMap = {
Jump = {
	Accel = 4,
},
WallJump = {
	Accel = 6,
},
Dive = {
	Accel = 2,
},
Dig = {
		Accel = 50,
		Delay = 15,
		PhaseCall="DiggingProcess",
},
};


