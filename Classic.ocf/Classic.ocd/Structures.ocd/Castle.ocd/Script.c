/*-- Castle --*/


#include Library_ClassicStructure
#include Library_Ownable
#include Library_HomeBase
#include Library_DoorControl

#include Basement80

local topface;

protected func Construction()
{
	_inherited(...);
    this.PictureTransformation = Trans_Mul(Trans_Rotate(-20, 0, 1, 0), Trans_Rotate(-15, 1, 0, 0), Trans_Rotate(7, 0, 0, 1), Trans_Translate(10000, -5000, 30000), Trans_Scale(900, 900, 450));
}

protected func Initialize()
{
	topface = CreateObject(Dummy, 0, 0, NO_OWNER);
	topface->SetPosition(GetX(), GetY());
	topface->SetGraphics("TopFace", GetID());
	topface.Visibility = VIS_All;
	topface.Plane = 500;
}

func Destruction()
{
	if (topface) topface->RemoveObject();
	_inherited(...);
}

  
/* Türsteuerung */

private func SoundOpenDoor()
{
	Sound("DoorOpen");
}
  
private func SoundCloseDoor()
{
	Sound("DoorClose");
}

private func SoundOpenGate()
{
	Sound("GateOpen");
}
  
private func SoundCloseGate()
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
	NextAction = "DoorOpen",
	StartCall = "SoundOpenGate",
	Animation = "MainOpenDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 40,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
	Animation = "MainDoorOpen",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseGate",
	Animation = "MainCloseDoor",
},

TowerOpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	NextAction = "TowerDoorOpen",
	StartCall = "SoundOpenDoor",
	Animation = "TowerOpenDoor",
},

TowerDoorOpen = {
	Prototype = Action,
	Name = "Door",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 40,
	NextAction = "TowerCloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
	Animation = "TowerDoorOpen",
},

TowerCloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
	Animation = "TowerCloseDoor",
},

};
