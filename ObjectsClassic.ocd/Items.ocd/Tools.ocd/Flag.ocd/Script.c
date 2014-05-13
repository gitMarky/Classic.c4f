/*
	Flag
	Author: Marky

	High resolution version of the original flag :)
*/

public func IsBaseFlag(){ return true; } // Can mark a home base


private func Flying()
{
	SetDir(BoundBy(GetWind()/10+4,0,8));
	if (!GetActTime() && GetActionTarget())
	{
		SetCategory(31 & GetActionTarget()->GetCategory());
	}
}

func ResetCategory()
{
	SetCategory(C4D_Object);
}

func OnOwnerChanged(int new_owner, int old_owner)
{
	// Flag lost its owner? Fall down!
	if (new_owner == NO_OWNER) SetAction("Idle");
}


public func SetBase(object homebase)
{
	if(Contained()) Exit();
	homebase->SetOwner(GetOwner());
	SetAction("FlyBase",homebase);
	AddEffect("IntBaseCheck", homebase, 50, 1, this);

	this.Collectible = 0;
}

public func LostBase()
{
	this.Collectible = 1;
}

private func FxIntBaseCheckTimer(object target)
{
	if(!target)
	{
		SetAction("Idle");
		LostBase();
		return -1;
	}

	if(ActIdle())
	{
		target->~OnFlagLost();
		LostBase();
		return -1;
	}
}


local ActMap = {
FlyBase = {
	Prototype = Action,
	Name = "FlyBase",
	Procedure = DFA_ATTACH,
	Directions = 9,
	FlipDir = 5,
	Length = 6,
	Delay = 3,
	X = 0,
	Y = 12,
	Wdt = 24,
	Hgt = 12,
	NextAction = "FlyBase",
	StartCall = "Flying",
	AbortCall = "ResetCategory",
},
};


local Collectible = 1;
local Name = "$Name$";
local Description = "$Description$";
local UsageHelp = "$UsageHelp$";
local Rebuy = true;
