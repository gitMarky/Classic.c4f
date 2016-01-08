/*-- Lorry --*/

#include Library_ElevatorControl

local content_menu;

public func IsLorry() { return true;}
public func IsVehicle() { return true;}
public func IsContainer() { return true;}
public func IsToolProduct() { return true;}


/*-- Movement --*/

protected func ContactLeft()
{
	if (Stuck() && !Random(5))
		SetRDir(RandomX(-7, +7));
}

protected func ContactRight()
{
	if (Stuck() && !Random(5))
		SetRDir(RandomX(-7, +7));
}

func Hit3()
{
	Sound("DullMetalHit?");
}

/*-- Contents --*/

private func MaxContentsCount()
{
	return 50;
}

protected func RejectCollect(id object_id, object obj)
{
	// objects can still be collected
	if (ContentsCount() < this->MaxContentsCount())
	{
		Sound("Clonk");
		return false;
	}
	
	// the object cannot be collected, notify carrier?
	if (obj->Contained())
		Message("$TxtLorryisfull$");
	else
	{
		// if not carried, objects slide over the lorry
		if(Abs(obj->GetXDir()) > 5)
		{
			obj->SetYDir(-2);
			obj->SetRDir(0);
			Sound("SoftHit*");
		}
	}
	// reject collection
	return true;
}

// Automatic unloading in buildings.
protected func Entrance(object container)
{
	// Only in buildings
	if (container->GetCategory() & (C4D_StaticBack | C4D_Structure))
		// Not if the building prohibits this action.
		if (!container->~NoLorryEjection(this))
			// Empty lorry.
			container->GrabContents(this);
}

local ActMap = {
		Drive = {
			Prototype = Action,
			Name = "Drive",
			Procedure = DFA_NONE,
			Directions = 2,
			FlipDir = 1,
			Length = 20,
			Delay = 2,
			X = 0,
			Y = 0,
			Wdt = 22,
			Hgt = 16,
			NextAction = "Drive",
			//Animation = "Drive",
		},
};

func Definition(def)
{
	SetProperty("PictureTransformation",Trans_Mul(Trans_Rotate(-25,1,0,0),Trans_Rotate(40,0,1,0)),def);
}

local Name = "$Name$";
local Description = "$Description$";
local Touchable = 1;
local Rebuy = true;
local BorderBound = 1;
