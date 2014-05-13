/*
 * Extension of the base: can sell objects that are not only in the base,
 * but also in the guy who calls the menu and in the vehicle that he grabs.
 * 
 * Author: Marky, original by Randrian
 */

#appendto Library_Base

// Sell Object
func OpenSellMenu(object pClonk, int iSelection, bool fNoListUpdate)
{
	// Filled with [idDef, iCount, pObj] arrays
	var aArray;
	var iIndex;
	if(!fNoListUpdate)
		UpdateSellList(pClonk); // this is the only change here...
	AddClonkSellList(pClonk);
	pClonk->CreateMenu (BaseMaterial, this, C4MN_Extra_Value, "$TxtNothingToSell$", 0, C4MN_Style_Normal, 1);
	var iIndex;
	for(aArray in aSellList) // aArray contains [idDef, iCount, pObj]
	{
		pClonk->AddMenuItem(Format("$TxtSell$", aArray[2]->GetName()), "SellDummy", aArray[0], aArray[1], pClonk, nil, 128+4, aArray[2], GetSellValue(aArray[2]));
		iIndex++;
	}
	if(iSelection == iIndex) iSelection--;
	pClonk->SelectMenuItem(iSelection);
}

func UpdateSellList(object pClonk)
{
	aSellList = [];
	var iIndex;
	// Create a list of the sellable objects
	for(pObj in GetSellableContents(pClonk)) // again, I added only the parameter...
	{
		// Are we allowed to sell the object?
		if (pObj.NoSell) continue;
		// Only check the last item to stack, the engine normally sorts the objects so this should be enought to check
		if(iIndex && CanStack(aSellList[iIndex-1][2], pObj))
			aSellList[iIndex-1][1]++;
		else
			aSellList[iIndex++] = [pObj->GetID(), 1, pObj];
	}
	UpdateClonkSellMenus();
}

func GetSellableContents(object clonk)
{
	var criteria = Find_Or(Find_Category(C4D_Object), Find_Category(C4D_Vehicle), Find_Category(65536/*C4D_TradeLiving*/));
	
	var container;
	if (clonk != nil) if (clonk->GetProcedure() == "PUSH") container = clonk->GetActionTarget();
	
	var searchObjects;
			
	if (container)
		searchObjects = Find_Or(Find_Container(this), Find_Container(clonk), Find_Container(container));
	else
		searchObjects = Find_Or(Find_Container(this), Find_Container(clonk));
	
	return FindObjects( searchObjects, criteria);
}

// just passing parameters in this function and fixed a warning
func SellDummy(id idDef, object pClonk, bool bRight, dummyDummy)
{
	var iIndex = pClonk->GetMenuSelection();
	var aArray = aSellList[iIndex];
	//DoSell(aArray[2], GetOwner(), bRight, pClonk);
	DoSell(aArray[2], GetOwner(), false, pClonk);
	OpenSellMenu(pClonk, iIndex);
}


func DoSell(object pObj, int iPlr, bool bRight, object pClonk, bool stopAfterCash)
{
	//Log("Sell object %v %v", pObj, stopAfterCash);
	// Test the object
	if(pObj.NoSell || pObj->GetOCF() & OCF_CrewMember)
	{
		// Enter base (needed for NoSell objects in other objects which are sold)
		// commented out for test!!
		//if(pObj->Contained() != this)
		//	pObj->Enter(this);
		return 0;
	}
	// Sell contents first
	var pContents;
	for(pContents in FindObjects(Find_Container(pObj)))
		DoSell(pContents, iPlr, false, pClonk, true);
	// Give the player the cash
	DoWealth(iPlr, GetSellValue(pObj));
	Sound("Cash"); //, 0, 100, iPlr+1); // TODO: get sound
	if(pObj.Rebuy)
		DoBaseMaterial(pObj->GetID(), 1);
	// And remove the object
	pObj->RemoveObject();
	if (stopAfterCash) return; // no infinite loops with contents in contents and so on
	// right clicked? then sell other objects too
	var pNewObj;
	var bFound;
	if(bRight)
	{
		for(var pNewObj in GetSellableContents(pClonk)) // here, I made a change :D
			if(CanStack(pObj, pNewObj) && pObj != pNewObj)
			{
				bFound = 1;
				break;
			}
	}
//	// And remove the object
//	pObj->RemoveObject();
	if(bFound) return DoSell(pNewObj, iPlr, bRight);
	return true;
}

func FxIntBaseTimer(pThis, effect, iTime)
{
	var pObj;
	// Can this base heal? Then look for clonks that need some
	if(CanHeal() && GetHeal())
		for(pObj in FindObjects(Find_Container(this), Find_OCF(OCF_CrewMember), Find_Allied(GetOwner())))
		{
			if(pObj->GetEnergy() < pObj->GetMaxEnergy() && !GetEffect("IntBaseHeal", pObj))
				AddEffect("IntBaseHeal", pObj, 1, 1, this);
		}
	// Can this base extinguish? Then look for something on fire
	if(CanExtinguish())
		for(pObj in FindObjects(Find_Container(this), Find_OCF(OCF_OnFire), Find_Allied(GetOwner())))
			pObj->Extinguish();
	// Sell objects
	ExecAutoSell();
	// Update the sell menu of clonks (if someone knows a way to directly get info if the contents of the base change this coult be imporved)
	if(aClonkSellList)
	{
		// Only if there are clonks with menus
		var fFound;
		var pClonk;
		for(pClonk in aClonkSellList)
			if(pClonk)
			{
				fFound = 1;
				break;
			}
		if(fFound)
			UpdateSellList(pClonk);
	}
}
