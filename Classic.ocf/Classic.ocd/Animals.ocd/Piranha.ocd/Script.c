/*
 * Piranha
 *
 * Author: Marky, original from Clonk Rage
 */

#include Fish


// Damage per bite.
local BiteStrength = 4;

protected func Death()
{
	_inherited();
	ChangeDef(DeadPiranha);
}


private func FxIntAnimalActivityFight( object target, proplist effect)
{
	if (target != this) return;
	if (!Contained() && !InLiquid()) return;

	// Eat prey
	var found_prey;
	for (var prey in FindObjects(Find_Distance(150),
	  Find_Category(C4D_Living),
	  Find_NoContainer(),
	  Find_OCF(OCF_InLiquid),
	  Find_Func("IsClonk"),
	  Find_Not(Find_ID(GetID())),
	  Find_OCF(OCF_Alive),
	  Sort_Distance()))
	{
		var precision = 10;
		var distance = ObjectDistance(prey);
		var velocity = Distance(GetXDir(), GetYDir());
		var factor = precision * distance / velocity;
		found_prey = prey;
		SetCommand("MoveTo", 0, found_prey->GetX() + factor * found_prey->GetXDir() / precision,
		                        found_prey->GetY() + factor * found_prey->GetYDir() / precision, 0, true);
		break;
	}
	
	if (found_prey && ObjectDistance(found_prey) < 5) DoEat(prey);

	// Escape threats
	var found_threat = FindObject(Find_Distance(100), Find_Category(C4D_Object), Find_OCF(OCF_HitSpeed1), Find_NoContainer());
	if(found_threat != nil)
	{
		var xdir = BoundBy(GetX() - found_threat->GetX(), -1, 1);
		var ydir = BoundBy(GetY() - found_threat->GetY(), -1, 1);
		if(xdir == 0) xdir = Random(2) * 2 - 1;
		if(ydir == 0) ydir = Random(2) * 2 - 1;
		xdir = RandomX(5 * xdir, 10 * xdir);
		ydir = RandomX(5 * ydir, 10 * ydir);

		SetSpeed(xdir, ydir);
	}
}


func Attack(object target)
{
}

func DoEat(object obj)
{
	if (GetAction() != "Swim") return;
	BiteEffect();

	if (obj->GetAlive())
		obj->DoEnergy(-BiteStrength);

	hunger -= 20;
	if (hunger < 0) hunger = 0;
	
	DoEnergy(BiteStrength);
}

private func BiteEffect()
{
	Sound("Animals::Fish::Munch*");
	SetAction("Bite");
}



////////////////////////////////////////////////////////////////////////////////////////////////
//
// Properties

local Name="$Name$";
local MaxEnergy=40000;
local MaxBreath = 1440; // Piranha can breathe for 40 seconds on land.
local Description="$Description$";
local Collectible=1;
local NoBurnDecay=1;
local BreatheWater=1;
local BorderBound=5;

local ActMap = {

Bite={
		Prototype = Action,
		Name="Bite",
		Procedure = DFA_SWIM,
		Directions=2,
		FlipDir=1,
		Speed=100,
		Accel = 16,
		Decel = 16,
		Length=20,
		Delay=1,
		X=0,Y=24,Wdt=8,Hgt=6,
		NextAction="Swim",
},
};
