#include Library_AnimalEgg
#include Library_CarryHeavy

/* -- Carry heavy stuff -- */

private func GetCarryTransform(clonk)
{
	if (GetCarrySpecial(clonk))
	{
		return Trans_Identity();
	}
	else
	{
		return Trans_Rotate(90, 0, 0, 1);
	}
}

private func GetCarryBone() { return "Main"; }
private func GetCarryPhase() { return 500; }

/* -- Properties -- */

private func GetEggColor() { return RGB(230, 78, 5); } // For particle effects

local Collectible = true;
local Name = "$Name$";
local Description = "$Description$";
