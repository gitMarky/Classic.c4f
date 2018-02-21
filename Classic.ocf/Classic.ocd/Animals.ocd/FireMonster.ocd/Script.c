/* -- Fire monster -- */

#include Monster

private func Construction()
{
	_inherited(...);
	MakeNonFlammable();
}

/* -- Fire attack -- */

private func SpecialActivity()
{
	if (Random(8))
		return false;
	
	return StartFlame();
}

public func StartFlame()
{
	if (GetAction() != "Walk" || GetEffect("FxFireAttack", this) || GetCon() < 50)
		return false;
		
	CreateEffect(FxFireAttack, 1, 1);
	Sound("Fire::Inflame");
	Sound("Animals::Monster::MonsterGrowl?");
	PlayAnimation("Breath", ANIM_SLOT_Monster_Attack, Anim_Linear(0, 0, GetAnimationLength("Breath"), 40, ANIM_Remove));
}


private func Flaming()
{
	var x = 22 * GetCalcDir();
	var y = -2;
	
	var angle = 90 * GetCalcDir() + RandomX(-7, 7);
	var range = RandomX(30, 40);

	var flame = CreateObject(Flame, x, y, GetOwner());
	flame->SetController(GetController());
	flame->SetXDir(+Sin(angle, range));
	flame->SetYDir(-Cos(angle, range));
}


local FxFireAttack = new Effect
{

	Timer = func(int time)
	{
		// Timeout - should exist long after the attack, for cooldown
		if (time >= 140)
		{
			return FX_Execute_Kill;
		}
		// Actual flame attack every 2 frames
		if (Inside(time, 15, 35) && time%2)
		{
			this.Target->Flaming();
		}
		return FX_OK;
	},	
};


/* -- Properties -- */

local Name = "$Name$";
local Description = "$Description$";

local MaxEnergy = 250000;
local MaxBreath = 720; // Monster can breathe for 20 seconds under water.
local NoBurnDecay = 1;
local ContactCalls = true;
local Collectible = true;
local BorderBound = C4D_Border_Sides;

