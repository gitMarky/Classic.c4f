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


private func DiggingProcess()
{
	SetXDir(this.dig_xdir,100); SetYDir(this.dig_ydir,100);
	return true;
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


