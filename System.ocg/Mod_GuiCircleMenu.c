/*
 * I want back the part where the controller tells the item what to do :'(
 * 
 * Author: Marky
 */

#appendto GUI_CircleMenu

public func OnMouseOverItem(object item, object dragged)
{
	if (menu_commander && menu_commander->~IsContentMenu())
	{
		menu_commander->~OnMouseOverItem(this, item, dragged);
	}
	else
	{
		// make it appear bigger
		item->SetObjDrawTransform(1100, 0, 0, 0, 1100, 0, 1);
	}
}

public func OnMouseOutItem(object item, object dragged)
{
	if (menu_commander && menu_commander->~IsContentMenu())
	{
		menu_commander->~OnMouseOutItem(this, item, dragged);
	}
	else
	{
		// return to normal size
		item->SetObjDrawTransform(1000, 0, 0, 0, 1000, 0, 1);
	}
}

public func OnMenuSelect()
{
	SetClrModulation(RGB(255,255,255),2);
}

public func OnMenuDeselect()
{
	SetClrModulation(RGB(100,100,100),2);
}
