/*
 * Changed GUI backpack slot:
 * 
 * Displays only one hand, hand marks the currently selected item.
 * 
 * Author: Marky
 */

#appendto GUI_Backpack_Slot_Icon


local GUI_BPS_ExtraSlot = 1;
local GUI_BPS_Object = 2;
local GUI_BPS_Hand1 = 4;
local GUI_BPS_Hand2 = 5;
local GUI_BPS_UseIcon_Bg = 11;
local GUI_BPS_UseIcon_Fg = 12;

// SetSymbol from GUI_RingMenu_Icon
public func SetSymbol(obj)
{
	_inherited(obj);
		
	if(!obj)
	{
		SetGraphics(nil, nil, GUI_BPS_UseIcon_Bg, GFXOV_MODE_None);
		SetGraphics(nil, nil, GUI_BPS_UseIcon_Fg, GFXOV_MODE_None);
	}
	else
	{
		if (GetType(obj) == C4V_C4Object && obj->~IsUseable())
		{
			var index = 0;
			var scale = 600;
			
			var x = 1000 * GetDefWidth()/2 - 500;
			var y = 18000 + index * GetDefHeight() * scale;
			
			SetGraphics(nil, GUI_Marker, GUI_BPS_UseIcon_Bg, GFXOV_MODE_IngamePicture);
			SetObjDrawTransform( scale, 0, x, 0, scale, y, GUI_BPS_UseIcon_Bg);	
	
			SetGraphics(nil, obj->GetID(), GUI_BPS_UseIcon_Fg, GFXOV_MODE_IngamePicture);
			SetObjDrawTransform( scale, 0, x, 0, scale, y, GUI_BPS_UseIcon_Fg);	
		}
		
//			SetGraphics(nil, nil, 2, GFXOV_MODE_ObjectPicture, nil, 0, obj);
//		else
//			SetGraphics(nil,obj, 2, GFXOV_MODE_IngamePicture);
		
		// if object has extra slot, show it
		if(obj->~HasExtraSlot() && obj->Contents())
		{
//			SetGraphics(nil, nil, 1, GFXOV_MODE_ObjectPicture, nil, nil, obj->Contents());
//			SetClrModulation(RGBa(255,255,255,200),1);
//			SetObjDrawTransform(900,0,0,0,900,0,1);
		}
		// or otherwise, remove it
		else
		{
//			SetGraphics(nil,nil, 1);
		}
		
	}
}
