/*
 * Fish
 *
 * Author: Marky, original from Clonk Rage
 */

#include Library_AnimalControl
#include Library_AnimalReproduction
#include Library_AnimalFighting

////////////////////////////////////////////////////////////////////////////////////////////////
//
// Turning

private func FxIntAnimalTurnTimer(object target, proplist effect)
{
	if (target != this) return;

	// Swimming backwards? Turn around!
	if (GetXDir()>0 && GetDir() == DIR_Left)  return AnimalTurnRight();
	if (GetXDir()<0 && GetDir() == DIR_Right) return AnimalTurnLeft();

}

private func AnimalCanTurn(){ return !Stuck() && GetAction() == "Swim"; }
private func AnimalOnTurnLeft()
{
	SetAction("Turn");
}
private func AnimalOnTurnRight()
{
	SetAction("Turn");
}

/* Contact with the landscape */

protected func ContactLeft()
{
	AnimalTurnRight();
}

protected func ContactRight()
{
	AnimalTurnLeft();
}

protected func ContactTop()
{
	SetComDir(COMD_Down);
}

protected func ContactBottom()
{
	if (GetAction() != "Walk") SetComDir(COMD_Up);
	if (Random(10)) SetComDir(COMD_Right);
	if (Random(10)) SetComDir(COMD_Left);
}

protected func Death()
{
	ChangeDef(DeadFish);
	_inherited();
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
// Behaviour

private func AnimalReproductionRate(){	return 2000;}

private func AnimalReproductionCondition()
{
	var effect = AnimalGetActivityEffect();
	if (Contained()) return false;
	if (GetAction() != "Swim") return false;
	return !Random(AnimalReproductionRate());
}

private func FxIntAnimalActivityStatus( object target, proplist effect)
{
	if (target != this) return;

	effect.ignoreCalls = false;

	// Dead fish don't do much...
	if(!GetAlive())
	{
		effect.ignoreCalls = true;
		return;
	}
}

private func FxIntAnimalActivityMovement( object target, proplist effect)
{
	if (target != this) return;

	if (GetAction() == "Walk")
	{
		if (Random(2))
			SetComDir(COMD_Right);
		else
			SetComDir(COMD_Left);

		return;
	}

	// Swim!
	if (!GBackLiquid(0, -4) && GetAction() != "Walk") return SetComDir(COMD_Down);
	if (Random(2)) return;
	if (GetAction() != "Swim") return;
	if (!Random(10)) return SetComDir(COMD_Up);
	if (!Random(10)) return SetComDir(COMD_Down);

	if (Random(2))
		AnimalTurnRight();
	else
		AnimalTurnLeft();
}


private func FxIntAnimalActivityFight( object target, proplist effect)
{
	if (target != this) return;

	// Escape threats
	var found_threat;
	if (!Contained() && InLiquid())
	{
		for (var threat in FindObjects(Find_Distance(100),
		  Find_Category(C4D_Living),
		  Find_NoContainer(),
		  Find_OCF(OCF_InLiquid),
		  Find_Not(Find_Func("IsClonk")),
		  Find_Not(Find_ID(GetID())),
		  Find_OCF(OCF_Alive),
		  Sort_Distance()))
		{
			  // Threat is not moving
			  if (Inside(threat->GetXDir(), -2, +2) && Inside(threat->GetYDir(), -3, +3)) continue;
			  // No contact?
			  if (threat->GetContact(-1, 8)) continue;

				found_threat = true;
				var xdist = threat->GetX() - GetX();
				var ydist = threat->GetY() - GetY();
				var axdist = Max(1, Abs(xdist));
				var aydist = Max(1, Abs(ydist));
				var xsign = xdist / axdist;
				var ysign = ydist / aydist;
				var fleex = GetX() - xsign * (1500 / BoundBy(axdist, 20, 80)); // 20..80 -> 70..15
				var fleey = GetY() - ysign * (1000 / BoundBy(aydist, 20, 80)); // 20..80 -> 50..10
				SetCommand("MoveTo", 0, fleex, fleey, 0, true);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
// Animation

public func AnimalInitialAction(){	return "Swim";}

protected func AnimalInit()
{
	// Random size
	var scale = RandomX(100, 150) * 10;
	SetObjDrawTransform(scale, 0, 0, 0, scale);

	// Color
	var r1 = 255, g1 = 255, b1 = 255;
	var r2 =  75, g2 =  85, b2 = 108;
	var r3 = 139, g3 = 142, b3 = 149;

	//var col = Random(2);
	var scale2 = Random(100);
	var r, g, b;

	if (!Random(2))
	{
		r = (r1 * (100-scale2) + r2 * scale2)/100;
		g = (g1 * (100-scale2) + g2 * scale2)/100;
		b = (b1 * (100-scale2) + b2 * scale2)/100;
	}
	else
	{
		r = (r1 * (100-scale2) + r3 * scale2)/100;
		g = (g1 * (100-scale2) + g3 * scale2)/100;
		b = (b1 * (100-scale2) + b3 * scale2)/100;
	}

	var color = RGB( r, g, b);

	SetColor(color);

	_inherited();
}


local ActMap = {
Walk={
		Prototype = Action,
		Name = "Walk",
		Procedure = DFA_WALK,
		Directions=2,
		FlipDir=1,
		Speed=30,
		Accel = 16,
		Decel = 16,
		Length=10,
		Delay=1,
		X=0,Y=0,Wdt=8,Hgt=6,
		NextAction="Walk",
		InLiquidAction="Swim",
},

Swim={
		Prototype = Action,
		Name="Swim",
		Procedure = DFA_SWIM,
		Directions=2,
		FlipDir=1,
		Speed=100,
		Accel = 16,
		Decel = 16,
		Length=20,
		Delay=1,
		X=0,Y=6,Wdt=8,Hgt=6,
		NextAction="Swim",
},

Turn={
		Prototype = Action,
		Name="Turn",
		Procedure = DFA_SWIM,
		Directions=2,
		FlipDir=1,
		Speed=100,
		Accel = 16,
		Decel = 16,
		Length=15,
		Delay=3,
		X=0,Y=18,Wdt=8,Hgt=6,
		NextAction="Swim",
},

Jump={
		Prototype = Action,
		Name="Jump",
		Procedure = DFA_FLIGHT,
		Directions=2,
		FlipDir=1,
		Length=15,
		Delay=1,
		X=0,Y=12,Wdt=8,Hgt=6,
		NextAction="Hold",
		InLiquidAction="Swim",
},
};

local Name="$Name$";
local MaxEnergy=30000;
local MaxBreath = 1440; // Bird can breathe for 40 seconds on land.
local Description="$Description$";
local Collectible=1;
local NoBurnDecay=1;
local BreatheWater=1;
local BorderBound=5;

