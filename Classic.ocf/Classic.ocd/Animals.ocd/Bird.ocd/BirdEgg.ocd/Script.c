/*
 * Bird egg
 *
 * Author: Marky, original found in Clonk Rage
 */

private func Destruction()
{
	ClearScheduleCall(this, "FinishBreeding");
	_inherited(...);
}

public func Fertilize(id type, int breedTime)
{
	//Log("Fertilize %v %d", type, breedTime);
	var child = CreateConstruction(type, 0, 0, -1, Max(10, type->~AnimalReproductionBirthSize()));
	if (child)
	{
		child->ForceEnter(this);
		ScheduleCall(this, "FinishBreeding", breedTime);
	}

	return child;
}

public func FinishBreeding()
{
	var child = Contents();

	if (child)
	{
		child->Exit();
		child->~AnimalBirth();
	}

	DoBreak();
}

protected func Hit()
{
	if (Random(2)) DoBreak();
}

protected func Damage()
{
	return DoBreak();
}

protected func Entrance(object container)
{
	if (!(container->~IsNest()))
	{
		ClearScheduleCall(this, "FinishBreeding");
		for(var obj in FindObjects(Find_Container(this)))
		{
			if (obj) obj->RemoveObject();
		}
	}
}

private func DoBreak()
{
	if (GetAction() == "Break") return;
	if (Contained()) Contained()->Ejection(this);

	Sound("Animals::EggBreak");
	SetAction("Break");
}

protected func Destroy()
{
	RemoveObject();
}

local ActMap = {
Break = {
		Prototype = Action,
		Name = "Break",
		Length = 7,
		Delay = 2,
		X = 5, Y = 0, Wdt = 5, Hgt = 6,
		NextAction = "Break",
		EndCall = "Destroy",
},
};

local Name = "$Name$";
local Description = "$Description";
local Collectible=1;
