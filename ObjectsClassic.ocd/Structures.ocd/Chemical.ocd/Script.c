/*
 *	Chemical factory
 *
 *	Author: Marky, Mesh: constantin
 */

#include Library_Structure
#include Library_Ownable
#include Basement60
#include Library_DoorControl


func Definition(def)
{
	//SetProperty("MeshTransformation", Trans_Rotate(5,0,1,0));
	SetProperty("PictureTransformation", Trans_Mul(Trans_Translate(0,0,-1000),Trans_Rotate(-25,1,0,0),Trans_Rotate(-20,0,1,0)), def);
}



local BlastIncinerate = 100;
local HitPoints = 70;


local ActMap = {
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
	Animation = "OpenDoor",
},
DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Procedure = DFA_NONE,
	Length = 20,
	Delay = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
	Animation = "DoorOpen",
},
CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
	Animation = "CloseDoor",
},
};

local Name = "$Name$";
local Description = "$Description$";
