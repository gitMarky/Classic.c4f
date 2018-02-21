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


/* -- Animal hunt goal -- */

private func IsAnimalType(type)
{
	return type == FireMonster
 	    || type == GOAL_AnimalType_Monster;
}

/* -- Birth -- */

private func CreateHatchling()
{
	var baby = CreateObjectAbove(FireMonster, 0, 0, GetOwner());
	baby->SetCon(20);
	return baby;
}

/* -- Properties -- */

private func GetEggColor() { return RGB(230, 78, 5); } // For particle effects

local Collectible = true;
local Name = "$Name$";
local Description = "$Description$";
