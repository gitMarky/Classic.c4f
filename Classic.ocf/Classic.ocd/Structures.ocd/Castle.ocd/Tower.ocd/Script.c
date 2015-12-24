/*-- Small tower --*/


#include Library_DoorControl

private func SoundDoorOpen()
{
	Sound("DoorOpen");
}

private func SoundDoorClose()
{
	Sound("DoorClose");
}

/* Ascending */

protected func CheckContents()
{
	while (Contents()) Contents()->Exit(0, -10, 0, 0);  
}

protected func Initialize()
{
  UpdateTransferZone();
}

protected func UpdateTransferZone()
{
	SetTransferZone(-19,-28,38,48);
}

protected func ControlTransfer(object pObj, int tx, int ty)
{
	if (Inside(tx - GetX(), -20, 20))
	{
		// Aufstieg zur Plattform
		if (Inside(ty - GetY(), -38, -12)
	    && (GetY(pObj) > GetY() - 12))
			return HandleTransferAscend(pObj, tx, ty);
			
		// Abstieg von der Plattform
		if (Inside(GetX(pObj) - GetX(), -20, 20)
		 && Inside(GetY(pObj) - GetY(), -38, -12)
	     && Inside(ty - GetY(), -12, 20))
			return HandleTransferDescend(pObj, tx, ty);
	}

	// Transfer nicht möglich
	return false;
}

private func HandleTransferAscend(object pObj, int tx, int ty)
{
	if (Inside(GetX(pObj) - GetX(), -20, 20) && Inside(GetY(pObj) - GetY(), -38, -12))
    	return false;
    
	if (pObj->Contained() == this) return true;

	// Clonk soll den Turm betreten
	return pObj->AddCommand("Enter", this);
}
  
private func HandleTransferDescend(object pObj, int tx, int ty)
{
	if(pObj->Contained() == this)
		return true;
	pObj->Enter(this);

	return pObj->AddCommand("Exit");
}

// Loren nicht im Turm ausleeren
public func NoLorryEjection(object lorry) { return true;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 150;
local ContainBlast = 1;
local BurnTo = ClassicCastleTowerBurned;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	X = 0,
	Y = 42,
	Wdt = 14,
	Hgt = 19,
	OffX = 8,
	OffY = 23,
	FacetBase = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundDoorOpen",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Procedure = DFA_NONE,
	Delay = 15,
	X = 126,
	Y = 42,
	Wdt = 14,
	Hgt = 19,
	OffX = 8,
	OffY = 23,
	FacetBase = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Procedure = DFA_NONE,
	Length = 4,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 42,
	Wdt = 14,
	Hgt = 19,
	OffX = 8,
	OffY = 23,
	FacetBase = 1,
	NextAction = "Idle",
	StartCall = "SoundDoorClose",
	EndCall = "CheckContents",
},

};
