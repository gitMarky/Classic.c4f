/*-- Castle --*/


#include Library_ClassicStructure
#include Library_Ownable
#include Library_HomeBase
#include Library_DoorControl

#include Basement80

local tower;

protected func Initialize()
{
	tower = CreateObjectAbove(ClassicCastleTower, -23, +44, GetOwner());
	tower.Plane = this.Plane + 1;
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 160;
local ContainBlast = 1;
local BurnTo = ClassicCastleBurned;
local PictureTransformation = Trans_Mul(Trans_Rotate(-20, 0, 1, 0), Trans_Rotate(-15, 1, 0, 0), Trans_Rotate(7, 0, 0, 1), Trans_Translate(10000, -5000, 30000), Trans_Scale(900, 900, 450));

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
