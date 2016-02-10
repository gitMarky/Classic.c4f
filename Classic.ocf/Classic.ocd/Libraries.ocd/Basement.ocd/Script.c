/**
	Basement Library
	Basic library for basements, handles:
	* Damage
	* Creation
	
	Author: Marky, original found in Clonk Rage
*/

/* Engine Overrides */

protected func Construction()
{
	_inherited(...);
	CreateBasement();
}
  
protected func Destruction()
{
	RemoveBasement();
	_inherited(...);
}

/* Fundament */

local basement;
static const FX_BasementHandler = "IntBasementHandler";

private func BasementID(){ return nil; }
private func BasementWidth(){ return 0; }


private func CreateBasement()
{
	if(!GetEffect(FX_BasementHandler,this)) AddEffect(FX_BasementHandler,this,1,0,this,0,BasementID());
}

private func RemoveBasement()
{
	RemoveEffect(nil, this, GetEffect(FX_BasementHandler, this));
}


/* Effekte */

public func FxIntBasementHandlerStart(object target, proplist effect, int temporary, id basementID)
{
	if(temporary) return;

	if(target->GetID() == basementID) return;

	if(!effect.basement)
	{
		effect.basement = target->CreateObjectAbove(basementID, 0, -1, target->GetOwner());
		effect.basement -> SetPosition(effect.basement->GetX(), target->GetDefBottom()-effect.basement->GetDefOffset(1));
		effect.basement -> MoveOutClonks();
		effect.basement -> SetCategory(C4D_StaticBack);
		target->~SetBasement(effect.basement);
	}
}

public func FxIntBasementHandlerStop(object target, proplist effect, int reason, bool temporary)
{
	if(temporary) return;

	if(effect.basement)
	{
		effect.basement->RemoveBasement();
	}
}


/* Just copied, needs better code! */

private func MoveOutClonks()
{
	var pObj;
	if(GetID()!=BasementID()) return;

	var tol = 10;

	for(pObj in FindObjects(Find_InRect(-tol-BasementWidth()/2,-15, +2*tol + BasementWidth(), +25),
                                Find_OCF(OCF_Collectible | OCF_Grab | OCF_Alive),
                                Find_NoContainer(),
                                Find_Not(Find_Func("IsBridge")),
                                Find_Not(Find_Category(C4D_Structure))))
		MoveOutClonk(pObj);
}
  
private func MoveOutClonk(object pObj)
{
	if(GetID()!=BasementID()) return;

	while(pObj->Stuck() && Inside(pObj->GetY()-this->GetY(),-15,+5))
		pObj->SetPosition(pObj->GetX(),pObj->GetY()-1);  
}

local Name="$Name$";
local Description="$Description$";

