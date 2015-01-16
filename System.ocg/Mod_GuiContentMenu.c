#appendto GUI_Contents_Controller

local selected_menu;
local selected_item;


// Called if the mouse cursor enters hovering over an item.
public func OnMouseOverItem(object menu, object item, object dragged)
{
	// deselect the keyboard controlled item;
	if (selected_menu && selected_item)
		OnMouseOutItem(selected_menu, selected_item, nil, true);

	if (!item) return;

	var layer_selection = 4;
	//var layer_redraw = 5;

	// red tint for the selected object
	//item->SetGraphics(nil,item->GetSymbol()->GetID(),layer_selection,GFXOV_MODE_IngamePicture,nil,GFX_BLIT_Mod2);
	//item->SetClrModulation(RGBa(255,0,0,200),layer_selection);
	//item->SetObjDrawTransform(1020,0,0,0,1020,0,layer_selection);

	item->SetGraphics(nil,nil,layer_selection,GFXOV_MODE_ObjectPicture,nil,GFX_BLIT_Mod2, item->GetSymbol());
	item->SetClrModulation(RGBa(240,0,0,100),layer_selection);
	item->SetObjDrawTransform(1100,0,0,0,1100,0,layer_selection);


	selected_menu = menu;
	selected_item = item;
}

public func OnMouseOutItem(object menu, object item, object dragged, bool byMouseOver)
{
	if (item == selected_item && menu == selected_menu && !byMouseOver) return;

	var layer_selection = 4;
	var layer_redraw = 5;

	item->SetGraphics(nil,nil,layer_selection,GFXOV_MODE_None);
	item->SetGraphics(nil,nil,layer_redraw,GFXOV_MODE_None);
}

public func GetMenuObject(int index)
{
	return circ_menus[index].Menu;
}

public func GetMenuObjects()
{
	var list = CreateArray();

	for(var gui in circ_menus)
	{
		if (gui == nil) continue;

		PushBack(list, gui.Menu);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
//
// Keyboard navigation stuff

func Show(bool no_update)
{
	_inherited(no_update);
	OnMenuSelect(GetMenuObject(0));
	KeyboardSelectMenuItem(GetMenuObject(0), GetMenuObject(0)->GetItem(0));
}

func Hide()
{
	selected_menu = nil;
	selected_item = nil;

	_inherited();
}

func KeyboardSelectMenuItem(object menu, object item)
{
	OnMouseOverItem(menu, item, nil);
	//menu->OnMenuSelect();
}

func KeyboardSelectNextItem(bool previous)
{
	if (!selected_menu || !selected_item) return;

	KeyboardSelectMenuItem(selected_menu, GetNextItem( selected_menu, selected_item, previous));
}

func GetNextItem(object menu, object item, bool next)
{
	if (!menu) return nil;
	var items= menu->GetItems();

	var index = GetIndexOf(items, item);
	if (index < 0) return nil;

	var item_count = GetLength(menu->GetItems());

	var new_index = index;

	// looks illogical, but that's how it is :)
	if (next)
		new_index--;
	else
		new_index++;

	if (new_index < 0)
		new_index += item_count;

	new_index = new_index % item_count;

	return menu->GetItem(new_index);
}

// these get caught by the player control already...

func ControlLeft(bool release)
{
	if (release) return true;

	return KeyboardSelectNextItem(false);
}

func ControlRight(bool release)
{
	if (release) return true;

	return KeyboardSelectNextItem(true);
}

func ControlUp(bool release)
{
	if (release) return true;

	return KeyboardPressItem(false);
}

func ControlDown(bool release)
{
	if (release) return true;

	return KeyboardPressItem(true);
}

func KeyboardPressItem(bool alt)
{
	if (!selected_item) return false;

	if (alt)
		selected_item->MouseSelectionAlt(GetMenuObject()->GetOwner());
	else
		selected_item->MouseSelection(GetMenuObject()->GetOwner());

	return true;
}

func KeyboardSelectNextMenu(bool previous)
{
	if (!selected_menu) return;

	var index = FindMenuPos(selected_menu);
	if (index < 0) return; // I don't know how this should be possible, but I'll just leave it :)

	var next = GetNextMenu2(index, previous);

	if (!next) return;

	OnMenuDeselect(selected_menu);

	selected_item = nil;

	OnMenuSelect(next.Menu);
}

private func GetNextMenu2(int index, bool next)
{
	if (index < 0) return nil;

	var item_count = GetLength(circ_menus);

	var new_index = index;

	// looks illogical, but that's how it is :)
	if (next)
		new_index--;
	else
		new_index++;

	if (new_index < 0)
		new_index += item_count;

	new_index = new_index % item_count;

	return circ_menus[new_index];

}

private func PutContentsIntoMenu(object menu, object container)
{
	_inherited(menu, container);

	menu->OnMenuDeselect();

	SelectFirstMenuEntry();
}

func SelectFirstMenuEntry()
{
	if (selected_menu != nil && selected_item == nil)
	{
		KeyboardSelectMenuItem(selected_menu, selected_menu->GetItem(0));
	}
}

func OnMenuDeselect(object menu)
{
	if (!menu) return;

	// remove highlights from old menu
	for(var item in menu->GetItems())
	{
		if (item)
			OnMouseOutItem(menu, item, nil, true);
	}

	menu->OnMenuDeselect();

}

func OnMenuSelect(object menu)
{
	if (!menu) return;
	selected_menu = menu;

	SelectFirstMenuEntry();

	menu->OnMenuSelect();
}


// Adjusted, such that vehicles exit buildings instead of getting transferred into the clonk inventory

/** Transfers the objects contained in menu_item from the source to the target container.
	@param p_source proplist containing the source menu.
	@param p_target proplist containing the target menu.
	@param menu_item the menu item selected by the player.
	@param amount the amount of objects to be transfered.
	@return the actual count of objects that have successfully been transfered.
*/
private func TransferObjects(proplist p_source, proplist p_target, object menu_item, int amount)
{
	// Safety: target and source must be available.
	if (!p_source || !p_target)
		return 0;

	// Determine actual amount that may be transfered.
	var objects = menu_item->GetExtraData(); // will always be at least [object]
	amount = BoundBy(amount, 0, GetLength(objects));

	// Move to object from source container to target container.
	// Memorize which objects have been put where in order to know which menu items to update
	// how (Because the collection can be rejected by RejectCollect/AllowTransfer).
	var moved_to_target = [];
	var moved_length = 0;
	for (var i = 0; i < amount; i++)
	{
		var obj = objects[i];
		// Try to enter the object, but check for some collect callbacks.
		if (p_target.Object->~RejectCollect(obj->GetID(), obj) && !p_target.Object->~AllowTransfer(obj))
			continue;
		// see if the container actually allows taking it out
		if(p_source.Object->~RefuseTransfer(obj))
			continue;
		/*
		 *
		 */
		if (!obj.Collectible)
		{
			obj->AddCommand("Exit");
		} else
		/*
		 *
		 */
		if (obj->Enter(p_target.Object))
		{
			moved_to_target[GetLength(moved_to_target)] = obj;
			moved_length++;
		}
	}

	// Update target menu, source menu is updated elsewhere.
	if (moved_length > 0)
	{
		// in case objects may not be stacked in the contents menu of the target object, add
		// each object as a new menu item
		if (p_target.Object->~NoStackedContentMenu())
		{
			for (var mov_obj in moved_to_target)
				AddContentsMenuItem(mov_obj, p_target.Menu);
		}
		// otherwise, add stacked
		else
		{
			// If menu item with same objects already exists: update menu item.
			var target_item = CanStackObjIntoMenuItem(p_target.Menu, moved_to_target[0]);
			if (target_item)
			{
				var new_extra_data = Concatenate(target_item->GetExtraData(), moved_to_target);
				target_item->SetData(new_extra_data);
				target_item->SetCount(GetLength(new_extra_data));
			}
			// Otherwise add a new menu item to containing menu.
			else
			{
				AddContentsMenuItem(moved_to_target[0], p_target.Menu, moved_to_target);
			}
		}
	}
	// Return the number of items that have been transfered.
	return moved_length;
}
