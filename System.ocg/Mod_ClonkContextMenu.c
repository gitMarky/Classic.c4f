/*
 * A context menu for the clonk. Contains mainly the options that the interaction queue from OC has.
 * 
 * Author: Marky
 */

#appendto ClassicClonk


public func ContextMenuAddEntries()
{
	var entries = 0;
	
	entries += ContextMenuAddEntriesInteraction();
	entries += ContextMenuAddEntriesInventory();

	return entries > 0;
}

private func ContextMenuAddEntriesInteraction()
{
	var entries = 0;
	// Add all interaction buttons
	var hotkeys = FindObjects(Find_ID(GUI_ObjectSelector), Find_Owner(GetOwner()), Find_Func("ShowsItem"));
	//for (var icon in hotkeys)
	for (var i = GetLength(hotkeys)-1; i >= 0; i--) // Sort_Reverse() made no difference
	{
		var icon = hotkeys[i];
		if (icon.crew != this) continue;
		
		//AddMenuItem(Format("{{%i}} %s", icon.myobject->GetID(), icon.Tooltip), "DoNothing", nil, nil, icon, nil, C4MN_ItemExtra_Object, icon);
		AddMenuItem(icon.Tooltip, "SelectActionButtonViaContext", nil, nil, icon, nil, C4MN_ItemExtra_Object, icon);
		
		entries++;
	}

	return entries;
}

protected func SelectActionButtonViaContext(id icon, object actionButton)
{
	if (!actionButton) return;
	
	actionButton->~MouseSelection(GetOwner());
}
