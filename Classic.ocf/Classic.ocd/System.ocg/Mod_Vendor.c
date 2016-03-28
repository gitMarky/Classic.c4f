#appendto Library_Vendor

private func EjectAllContents()
{
	// Called when buying stuff, should do nothing, so that contents stay in the vendor
}

// ----- Selling

public func AllowSellMenuEntries(){ return true;}

func GetSellableContents(int wealth_player)
{
	var inventory = [];
	var obj, i = 0;
	while (obj = Contents(i++))
	{
		if (obj->~QueryOnSell(wealth_player)) continue;
		
		var sellable = obj->~GetCategory() & C4D_Object
		            || obj->~GetCategory() & C4D_Vehicle
		            || obj->~GetCategory() & 65536/*C4D_TradeLiving*/;

		if (!sellable) continue;

		// check if already exists (and then stack!)
		var found = false;

		// How many objects are this object?!
		var object_amount = obj->~GetStackCount() ?? 1;

		// Infinite stacks work differently - showing an arbitrary amount would not make sense.
		if (object_amount > 1 && obj->~IsInfiniteStackCount())
			object_amount = 1;

		// Empty containers can be stacked.
		for (var inv in inventory)
		{
			if (!inv.objects[0]->CanBeStackedWith(obj)) continue;
			if (!obj->CanBeStackedWith(inv.objects[0])) continue;
			if (!CanStackSellableContents(inv.objects[0], obj)) continue;
			inv.count += object_amount;
			PushBack(inv.objects, obj);
			
			// This object has a custom symbol (because it's a container)? Then the normal text would not be displayed.
			if (inv.custom != nil)
			{
				inv.custom.top.Text = inv.text;
				inv.custom.top.Style = inv.custom.top.Style | GUI_TextRight | GUI_TextBottom;
			}
			
			found = true;
			break;
		}

		// Add new!
		if (!found)
		{
			PushBack(inventory,
			{
					objects = [obj],
					count = object_amount,
			});
		}
	}

	return inventory;
}

func CanStackSellableContents(object first, object second)
{
	return first->CanConcatPictureWith(second) // need the same picture
	   && (this->GetSellValue(first) == this->GetSellValue(second)); // and the same value
}


public func GetInteractionMenus(object clonk)
{
	var menus = _inherited() ?? [];

	if (this->AllowSellMenuEntries())
	{
		var sell_menu =
		{
			title = "$MsgSell$",
			entries_callback = this.GetSellMenuEntries,
			callback = "OnSellMenuSelection",
			callback_target = this,
			BackgroundColor = RGB(50, 50, 0),
			Priority = 21
		};
		
		var has_sell_menu = false;
		for (var menu in menus)
		{
			if (menu.title == "$MsgSell$")
			{
				has_sell_menu = true;
				break;
			}
		}
		
		if (!has_sell_menu)
		{
			PushBack(menus, sell_menu);
		}
	}
	
	return menus;
}


// ----- Selling

public func GetSellMenuEntries(object clonk)
{	
	// distinguish owners here
	var wealth_player = clonk->GetController();

	var menu_entries = [];
	var i = 0, item, amount;
	
	for (item in this->GetSellableContents(wealth_player))
	{
		var instance = item.objects[0];
		amount = GetLength(item.objects);
		var value = this->GetSellValue(instance);
		var entry = GetBuyMenuEntry(i, instance, amount, value);
		PushBack(menu_entries, {symbol = instance, extra_data = nil, custom = entry});
	}

	return menu_entries;
}

public func OnSellMenuSelection(object item, extra_data, object clonk)
{
	// distinguish owners here
	var wealth_player = clonk->GetController();
	// Buy
	DoSell(item, wealth_player);
	UpdateInteractionMenus(this.GetSellMenuEntries);
}

public func Collection2(object item)
{
	UpdateInteractionMenus(this.GetSellMenuEntries);
	_inherited(item);
}


public func Ejection(object item)
{
	UpdateInteractionMenus(this.GetSellMenuEntries);
	_inherited(item);
}
