/**
 Tree control
 
 @author Redwolf Design, Clonk Rage
 @version 0.2
 */

#include Library_Plant
#include Library_Tree

local MotionThreshold;
local MotionOffset;

private func ForegroundFrequency() { return 10;}
private func RootDepth(){ return 3; }
private func SeedArea() { return 400; }
private func TreeStrength() { return 150; }
private func MaxDamage()
{
	if (!this)
		return TreeStrength();
	else
		return TreeStrength() * Max(GetCon(), 30)/100;
}

// Placement information

/**
 Trees are placed in earth.
 @version 0.3
 */
public func GetVegetationSoil(){ 	return Material("Earth");}
/**
 Trees are placed 5 pixels deep in the ground.
 @version 0.3
 */
public func GetVegetationRootDepth() { return 5;}
/**
 Trees adjust to the landscape with rotation between -30 and +30.
 @version 0.3
 */
public func GetVegetationRotation() { return [-30, 30]; }
/**
 Trees grow from 25% to 100% with a bias towards 100%.
 @version 0.3
 */
public func GetVegetationConRange() { return [25, 150]; }

/* Initialisierung */

protected func Construction()
{
	MotionThreshold = Random(10);

	SetAction("Initialize");
	
	SetObjDrawTransform( (-1 + 2 * Random(2)) * 1000, 0, 0, 0, 1000);

	ScheduleCall(this, "StartAnimation", Random(50));

	if (!Random(ForegroundFrequency()))
		ScheduleCall(this, "PlaceVegetationForeground", 5, 0, this);


	_inherited(...);
}

protected func RootSurface()
{
	_inherited(...);

	if (HasCNAT(CNAT_Bottom))
	{
		var limit_up = 20;
		while ((GetContact(-1) & CNAT_Bottom) && limit_up-- > 0)
				SetPosition(GetX(), GetY()-1);

		if (!(GetContact(-1) & CNAT_Bottom)) SetPosition(GetX(),GetY()+RootDepth()); // try make the plant stuck
	}
}
  
protected func StartAnimation()
{
	SetAction("Still");
}

/* Movement from wind (Wind) */
  
private func Still()
{
  if (Abs(GetWind()) > 49 + MotionThreshold) SetAction("Breeze");
}

private func Breeze()
{
  if (Abs(GetWind()) < 50 + MotionThreshold) SetAction("Still");
}

   
/* Kontext */

public func ContextChop(pClonk)
{
  //[$TxtChop$|Image=CXCP|Condition=IsStanding]
  pClonk -> AddCommand("Chop", this);
  return true;
}

protected func Damage()
{
    // Damaged dead trees should rot...
    if (this->IsDeadTree()
    && !GetEffect("IntTreeDecay", this)
    && GetCon() < 90
    && this.Touchable != 0)
        AddEffect("IntTreeDecay", this, 1, 51, this);

    if (!Random(3)) CastLeafParticles();

  	_inherited(...);
}

protected func Hit3(int x, int y)
{
	CastLeafParticles();

	_inherited(x, y,...);
}


public func CastLeafParticles()
{
	if (OnFire()) return;

	var particles = this->GetLeafParticles();
	if (!this->IsDeadTree() && particles != nil)
	{
		var amount = Random(GetCon()/20) + 1;

		for (var i=0; i<amount; i++)
		{
			var x = GetDefOffset(0) + Random(GetID()->GetDefWidth()-20) +10;
			var y = GetDefOffset(1) + Random(GetID()->GetDefHeight()-GetDefFireTop()-20) +10;

			CreateParticle("Leaves", x, y, 0, 1, RandomX(150, 200), particles, 1);
		}
	}
}

protected func ChopDown()
{
	SetAction("Chopped");
	ScheduleCall(this, this.CastLeafParticles, 5, 2);

	_inherited(...);
}

protected func Incineration()
{
	SetGraphics("Burned");
	SetAction("Chopped");
	_inherited(...);
}

func FxTreeFallTimer(object target, proplist fx, int time)
{
	// this makes sure that the tree falls properly,
	// does not get stuck in an upright position
	if (!fx.stopForcedFall)
	{
		var contact = GetContact(-1);

		// if you hit the landscape somewhere else, then stop forced falling
		// or if you have a 'believable' rotation already, or if it just took to long
		 if ((contact & CNAT_Top || contact & CNAT_Center) || !Inside(GetR(), -70, 70) || time > 50)
			 fx.stopForcedFall = true;

		if ((contact & CNAT_Bottom))
		{
			if (!Random(10))
				SetPosition(GetX(),GetY()-2);
			else
				SetPosition(GetX(),GetY()-1);

			SetXDir(RandomX(-3,3));
		}
	}

	return _inherited(target, fx);
}

private func GetLeafParticles()
{
	return Particles_Colored(Particles_Leaves(), RGB(64,150,64), RGB(0,110,0) );
}


protected func FxIntTreeDecayTimer(object target, proplist fx, int time)
{
	if (!target->~IsDeadTree() || target->GetCon() >= 90)
		return FX_Execute_Kill;

	target->DoCon(-1);
	return FX_OK;
}

public func IsDeadTree() { return false; } // overload dead trees



local ActMap = {
Initialize = {
		Prototype = Action,
		Name = "Initialize",
		Length = 1,
		Delay = 60,
		FacetBase = 1,
		NextAction = "Still",
},

Still = {
		Prototype = Action,
		Name = "Still",
		FacetBase=0,
		NextAction="Still",
		StartCall="Still",
},

Breeze = {
		Prototype = Action,
		Name="Breeze",
		FacetBase=0,
		NextAction="Breeze",
		StartCall="Breeze",
},

Chopped = {
		Prototype = Action,
		Name = "Chopped",
		Length = 1,
		Delay = 0,
		FacetBase = 1,
		NextAction = "Hold",
},
};

local Name = "$Name$";
local Description = "$Description";
local ContactIncinerate=2;
local BlastIncinerate=10;
