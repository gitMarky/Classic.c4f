/*-- Elevator case --*/

#include ElevatorCase

//static const ElevatorCase_move_speed = 10;

func Initialize()
{
	_inherited(...);

	AddEffect("CheckAutoMoveTo", this, 1, 30, this);
	//AddEffect("ElevatorUpperLimitCheck", this, 1, 1, this);
	//AddEffect("FetchVehicles", this, 1, 1, this);
	
	//case_speed = ElevatorCase_move_speed / 2;
	//case_speed_automatic = ElevatorCase_move_speed;
	
	partner_was_synced = false;

	if (front) front->RemoveObject();
	if (back) back->RemoveObject();
}


public func IsInteractable(object clonk)
{
	if (GetCon() < 100) return false;
	if (!elevator) return false;
	if (Hostile(GetOwner(), clonk->GetOwner())) return false;
	if (clonk->GetProcedure() != DFA_PUSH) return false;
	//if (clonk->GetActionTarget() !) no action target check! interaction from vehicle would be impossible
	return true;
}

public func GetInteractionCount() { return 1; }
public func GetInteractionMetaInfo(object clonk, int num)
{
		return {IconName=nil, IconID=Icon_ElevatorInteractions, Description="$TxtDrillshaft$"};
}


public func Interact(object clonk, int num)
{
	// drill!
	SetMoveDirection(COMD_Down, true, true);
	return true;
}


func Drilling()
{
	var additional_y = 1;

	var bounds_l = GetDefOffset();
	var bounds_u = GetDefOffset(1) - additional_y;
	var bounds_r = GetID()->GetDefWidth() + GetDefOffset();
	var bounds_d = GetID()->GetDefHeight() + GetDefOffset(1) + additional_y;

	var rect = Rectangle(GetX() + bounds_l, GetY() + bounds_u, GetX() + bounds_r, GetY() + bounds_d);
	if(IsMaster())
	{
		rect.x = Min(rect.x, partner->GetX() + bounds_l);
		rect.y = Min(rect.y, partner->GetY() + bounds_u);
		rect.w = Max(rect.w, partner->GetX() + bounds_r);
		rect.h = Max(rect.h, partner->GetY() + bounds_d);
	}
	DigFreeRect(rect.x, rect.y, rect.w - rect.x, rect.h - rect.y);

	// has to remove dug out earth!!!!!
	var chunks = FindObjects(Find_Func("IsRemoveableMaterialChunk"), Find_InRect(bounds_l,bounds_u, bounds_r-bounds_l, bounds_d-bounds_u));
	for(var obj in chunks) obj->RemoveObject();
}

local Plane = 250;

func FxElevatorUpperLimitCheckTimer(target, effect, time)
{
	if(!elevator) return -1;
	if(IsSlave()) return -1;

	var d = GetY() - (elevator->GetY() + 15); // was 20

	// HOW COULD THIS HAPPEN :C
	if(d <= 0)
	{
		if(GetYDir() < 0)
		{
			SetPosition(GetX(), GetY() - d);
			ForceSync();
			ContactTop();
		}
		else
			if(GetYDir() == 0)
				SetPosition(GetX(), GetY() - d);

		effect.Interval = 1;
		return 1;
	}

	// everything okay, adjust timer accordingly
	// check less often if far away from elevator
	// note: d > 0
	var t = BoundBy(d / 3, 1, 20);
	effect.Interval = t;
	return 1;
}


// or else we cannot ungrab :'(
func ControlDown(object clonk)
{
// code below is in comments, because the previous implementation used Control-Down-Double to ungrab
// maybe this will be implemented again, but probably not. Will delete the comment once the decision was made.
//	return false;
//}
//
//
//func ControlDownSingle(object clonk)
//{
//	if (IsSlave()) return Control2Master("ControlDownSingle", clonk);
	if (IsSlave()) return Control2Master("ControlDown", clonk);

	SetMoveDirection(COMD_Down, true, false);
	return true;
}

func ControlLeft(object clonk)
{
	if (IsSlave()) return Control2Master("ControlLeft", clonk);

	Halt(true);
	return true;
}

func ControlRight(object clonk)
{
	if (IsSlave()) return Control2Master("ControlRight", clonk);

	Halt(true);
	return true;
}

func FxFetchVehiclesTimer(target, effect, time)
{
	if(!elevator) return -1;
	if(IsSlave()) return 1;

	// look for vehicles
	var additional = -9;
	var x = - 12 - additional;
	var w = + 12 + additional;
	var y = - 12;
	var h = + 15;

	if(IsMaster())
	{
		x = Min(x, partner->GetX() - GetX() - 12 - additional);
		w = Max(w, partner->GetX() - GetX() + 12 + additional);
	}

	// Fetch vehicles
	for (var vehicle in FindObjects(Find_InRect(x, y, w - x, h - y), Find_Category(C4D_Vehicle), Find_NoContainer(), Find_Func("FitsInElevator")))
	{
		vehicle->SetPosition(vehicle->GetX(), GetY() + 11 - vehicle->GetDefHeight() - vehicle->GetDefOffset(1));
		vehicle->SetYDir();
		vehicle->SetR();
		if (GetEffect("ElevatorControl", vehicle)) continue;
		AddEffect("ElevatorControl", vehicle, 30, 5, vehicle, nil, this);
	}

	return 1;
}

local ActMap = {
Drill = {
	Sound = "Drill",
},
};
