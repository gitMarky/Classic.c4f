/*
 *	The Home Base
 *
 *	Author: Marky
 */

#include Library_Base
#include Library_Vendor

static const g_Homebase_Interact_RemoveFlag = 1;

private func Collection2(object item)
{
	if(!IsBase() && item->~IsBaseFlag() && item->GetOwner() != NO_OWNER)
	{
		item->~SetBase(this);
		MakeBase(false); // this actually makes it a base...
	}

	_inherited(item);
}

private func OnFlagLost()
{
	MakeBase(true);
}

/* --- Buy materials at base --- */


public func IsInteractable(object clonk)
{
	if (GetCon() < 100) return false;
	if (!IsBase()) return false;
	if(Hostile(GetOwner(), clonk->GetOwner())) return false;
	return true;
}

public func GetInteractionCount() { return 1; }
public func GetInteractionMetaInfo(object clonk, int num)
{
	if (num == g_Homebase_Interact_RemoveFlag && IsBase())
		return {IconName=nil, IconID=ClassicFlag, Description="$MsgRemoveFlag$"};
}

public func Interact(object clonk, int num)
{
	if (num == g_Homebase_Interact_RemoveFlag)
		RemoveFlag(clonk);

	return true;
}

public func RemoveFlag(object clonk)
{
	var flag = GetFlag();
	
	if (flag == nil) return false;
	
	flag->LostBase();
	
	var x = flag->GetX();
	var y = flag->GetY();
	
	if (!clonk->Collect(flag))
	{
		flag->SetPosition(x, y);
	}
	
	return true;
}

public func GetFlag()
{
	return FindObject(Find_Func("IsBaseFlag"), Find_Owner(GetOwner()), Find_ActionTarget(this));
}

protected func OnStructureDestroyed()
{
	var flag = GetFlag();
	if (flag != nil)
	{
		flag->~LostBase();
	}
	
	_inherited(...);
}
