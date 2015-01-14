/*
 *	The Home Base
 *
 *	Author: Marky
 */

#include Library_Base
#include Library_GoldSeller

static const g_Homebase_Interact_Buy = 0;
static const g_Homebase_Interact_Sell = 1;

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

public func GetInteractionCount() { return 2; }
public func GetInteractionMetaInfo(object clonk, int num)
{
	if(num == g_Homebase_Interact_Buy)
		return {IconName=nil, IconID=Library_Base, Description="$MsgBuy$"};
	if(num == g_Homebase_Interact_Sell)
		return {IconName=nil, IconID=BaseMaterial, Description="$MsgSell$"};
}

public func Interact(object clonk, int num)
{
//	var menu;
//	var i = 0, item, amount;
//	while (item = GetHomebaseMaterial(GetOwner(), nil, i++))
//	{
//		amount = GetHomebaseMaterial(GetOwner(), item);
//		// Add even if amount==0
//		if (!menu) menu = clonk->CreateRingMenu(Flagpole, this);
//		if (!menu) return false;
//		menu->AddItem(item, amount, nil);
//	}
//	if (!menu) return false;
//	menu->Show();
	if (num == g_Homebase_Interact_Buy)
		OpenBuyMenu(clonk);
	if (num == g_Homebase_Interact_Sell)
		OpenSellMenu(clonk);

	return true;
}
//
//public func Selected(object menu, proplist menu_item, bool alt)
//{
//	// Safety
//	var clonk = menu->GetMenuObject();
//	if (!clonk || !IsInteractable(clonk)) return;
//	var def = menu_item->GetSymbol();
//	if (!def) return;
//	// Buy
//	DoBuy(def, clonk->GetController(), GetOwner(), clonk, alt);
//	// Excess objects exit flag (can't get them out...)
//	var i = ContentsCount();
//	var obj;
//	while (i--)
//		if (obj = Contents(i))
//			Contents(i)->Exit(0, GetDefHeight() / 2);
//	// Update available count
//	menu_item->SetAmount(GetHomebaseMaterial(GetOwner(), def));
//	menu->Show();
//	return true;
//}
