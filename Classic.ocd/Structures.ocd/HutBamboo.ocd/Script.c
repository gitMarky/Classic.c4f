/*-- Bamboo hut --*/

#include Library_ClassicStructure
#include Library_Ownable
#include Library_HomeBase
#include Library_DoorControl

protected func SoundOpenDoor() { return nil;}
protected func SoundCloseDoor() { return nil;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 10;
//local BurnTo = ClassicHutBambooBurned;
local ContactIncinerate = 3;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Length = 10,
	Delay = 1,
	X = 0,
	Y = 43,
	Wdt = 11,
	Hgt = 17,
	OffX = 20,
	OffY = 26,
	FacetBase = 1,
	NextAction = "DoorOpen",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Delay = 20,
	X = 99,
	Y = 43,
	Wdt = 11,
	Hgt = 17,
	OffX = 20,
	OffY = 26,
	FacetBase = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Length = 10,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 43,
	Wdt = 11,
	Hgt = 17,
	OffX = 20,
	OffY = 26,
	FacetBase = 1,
	NextAction = "Idle",
},

};
