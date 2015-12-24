/*
 *	The Home Base
 *
 *	Author: Marky
 */

#include Library_Base
#include Library_GoldSeller

static const g_Homebase_Interact_Buy = 0;
static const g_Homebase_Interact_Sell = 1;
static const g_Homebase_Interact_RemoveFlag = 2;

private func Collection2( object pObj, bool fPut )
{
	if(!IsBase() && pObj->~IsBaseFlag() && pObj->GetOwner() != NO_OWNER)
	{
		pObj->~SetBase(this);
		MakeBase(false); // this actually makes it a base...
	}

	_inherited(...);
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

public func GetInteractionCount() { return 3; }
public func GetInteractionMetaInfo(object clonk, int num)
{
	if (num == g_Homebase_Interact_Buy)
		return {IconName=nil, IconID=Library_Base, Description="$MsgBuy$"};
	if (num == g_Homebase_Interact_Sell)
		return {IconName=nil, IconID=BaseMaterial, Description="$MsgSell$"};
	if (num == g_Homebase_Interact_RemoveFlag && IsBase())
		return {IconName=nil, IconID=ClassicFlag, Description="$MsgRemoveFlag$"};
}

public func Interact(object clonk, int num)
{
	if (num == g_Homebase_Interact_Buy)
		OpenBuyMenu(clonk);
	if (num == g_Homebase_Interact_Sell)
		OpenSellMenu(clonk);
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
