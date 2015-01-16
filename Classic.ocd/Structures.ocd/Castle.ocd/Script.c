/*-- Burg --*/


#include Library_Structure
#include Library_Ownable
#include Library_HomeBase
#include Library_DoorControl


//#include BAS8

/* Initialisierung */

protected func Initialize()
{
	//SetObjectOrder(this(), CreateObject(TWR1,-23,+44,GetOwner()));
}
  
/* Türsteuerung */

private func SoundOpenDoor()
{
	Sound("GateOpen");
}
  
private func SoundCloseDoor()
{
	Sound("GateClose");
}
  
/* Forschung */

public func GetResearchBase() { return(CST1); }


/* Status */

public func IsCastle() { return true; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 160;
local ContainBlast = 1;
local BurnTo = ClassicCastleBurned;

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
	Y = 87,
	Wdt = 20,
	Hgt = 22,
	OffX = 40,
	OffY = 65,
	FacetBase = 1,
	NextAction = "Door",
	StartCall = "SoundOpenDoor",
},

Door = {
	Prototype = Action,
	Name = "Door",
	Procedure = DFA_NONE,
	Delay = 40,
	X = 180,
	Y = 87,
	Wdt = 20,
	Hgt = 22,
	OffX = 40,
	OffY = 65,
	FacetBase = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 87,
	Wdt = 20,
	Hgt = 22,
	OffX = 40,
	OffY = 65,
	FacetBase = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
},

};
