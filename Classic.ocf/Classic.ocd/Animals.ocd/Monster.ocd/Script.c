/* -- Monster -- */

#include Library_AnimalControl
#include Library_AnimalReproduction

/* -- Reproduction -- */

private func AnimalReproductionRate(){    return 2000;}
private func AnimalReproductionMaxCount()       { return 4; }
public func AnimalInitialAction(){    return "Walk";}


// Special behaviour, e.g. monster eggs
private func AnimalReproductionCustom()
{
    if (!Random(AnimalReproductionRate()))
    {
		CreateContents(MonsterEgg)->Exit(0, 10);
	}
	return true;
}


/* -- Movement -- */

private func ContactLeft()
{
	AnimalTurnRight();
}

private func ContactRight()
{
	AnimalTurnLeft();
}

private func AnimalCanTurn(){ return !Stuck() && (GetAction() == "Walk" || GetAction() == "Swim"); }

private func HitCheck()
{
	var target = FindObject(Find_Func("IsPrey"), Find_AtPoint(), Find_NoContainer());
	if (target)
	{
		Punch(target, 10);
	}
}

public func DoJump()
{
	if (GetAction() == "Walk")
	{
		if (Random(2)) Sound("Animals::Monster::MonsterGrowl?");
		Jump();
	}
}

/* -- Engine callbacks -- */

private func Death()
{
	Sound("DeathGrowl");
	SetDir(DIR_Left);
	SetAction("Dead");
}

/* -- Activity -- */

private func FxIntAnimalActivityMovement(object target, proplist ai)
{
    if (target != this) return;
    
	// Do nothing
	if (Random(2) && (GetAction() == "Walk" || GetAction() == "Swim"))
	{
		if (GetAction == "Walk")
		{
			// Jump
			if (!Random(3)) return DoJump();
			
			// Look around
			if (!Random(8)) return SetAction("LookUp");
		}
		
		if (Random(2))
		{
			AnimalTurnRight();
		}
		else
		{
			AnimalTurnLeft();
		}
	}
}


/* -- Properties -- */

local Name = "$Name$";
local Description = "$Description$";

local MaxEnergy = 250000;
local MaxBreath = 720; // Monster can breathe for 20 seconds under water.
local NoBurnDecay = 1;
local ContactCalls = true;
local Collectible = true;
local BorderBound = 7;

/* -- Actions -- */

local ActMap = {
Walk = {
	Prototype = Action,
	Name = "Walk",
	Procedure = DFA_WALK,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 5,
	X = 0,
	Y = 0,
	Wdt = 48,
	Hgt = 34,
	Accel = 8,
	Decel = 48,
	Speed = 200,
	NextAction = "Walk",
	StartCall = "HitCheck",
	InLiquidAction = "Swim",
},

Turn = {
	Prototype = Action,
	Name = "Turn",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Length = 7,
	Delay = 2,
	X = 0,
	Y = 68,
	Wdt = 48,
	Hgt = 34,
	NextAction = "Walk",
},

Jump = {
	Prototype = Action,
	Name = "Jump",
	Procedure = DFA_FLIGHT,
	Directions = 2,
	FlipDir = 1,
	Length = 17,
	Delay = 1,
	X = 0,
	Y = 34,
	Wdt = 48,
	Hgt = 34,
	Speed = 200,
	Accel = 14,
	NextAction = "Hold",
	InLiquidAction = "Swim",
},

Swim = {
	Prototype = Action,
	Name = "Swim",
	Procedure = DFA_SWIM,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 5,
	X = 0,
	Y = 0,
	Wdt = 48,
	Hgt = 34,
	NextAction = "Swim",
	StartCall = "HitCheck",
},

LookUp = {
	Prototype = Action,
	Name = "LookUp",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Length = 12,
	Delay = 1,
	Attach = 8,
	X = 0,
	Y = 102,
	Wdt = 48,
	Hgt = 34,
	NextAction = "Look",
	InLiquidAction = "Swim",
},

Look = {
	Prototype = Action,
	Name = "Look",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Delay = 15,
	Attach = 8,
	X = 528,
	Y = 102,
	Wdt = 48,
	Hgt = 34,
	NextAction = "LookAway",
	InLiquidAction = "Swim",
},

LookAway = {
	Prototype = Action,
	Name = "LookAway",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Length = 12,
	Reverse = 1,
	Delay = 1,
	Attach = 8,
	X = 0,
	Y = 102,
	Wdt = 48,
	Hgt = 34,
	NextAction = "Walk",
	InLiquidAction = "Swim",
},

};
