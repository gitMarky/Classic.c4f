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


/* -- Engine Callbacks -- */

private func Hit(int x, int y)
{
	StonyObjectHit(x,y);
	if (!Random(2))
	{
		Hatch();
	}
}

private func Damage()
{
	Hatch();
}


private func Hatch()
{
	if (GBackSolid(0, -1) || !this.Collectible)
		return;

	Exit();
	this.Collectible = false;
	Sound("Animals::EggBreak");
	// TODO: create monster, and so on
	FadeOut(200, true);
	SetGraphics("Broken");
	
	var particles = 
	{
		Size = PV_KeyFrames(0, 0, 0, 100, PV_Random(3, 5), 1000, 3),
		R = 243,
		G = 244,
		B = 242,
		Alpha = PV_Linear(255, 0),
		ForceY = PV_Gravity(100),
		CollisionVertex = 0
	};
	
	CreateParticle("Hail", 0, 0, PV_Random(-5, 5), PV_Random(-5, 0), PV_Random(10, 60), particles, 20);
	
}


private func Initialize()
{
	AddTimer(this.Breed, 350);
}


private func Breed()
{
	if (!Random(200))
	{
		Hatch();
	}
}


/* -- Properties -- */

local Collectible = true;
local Name = "$Name$";
local Description = "$Description$";
