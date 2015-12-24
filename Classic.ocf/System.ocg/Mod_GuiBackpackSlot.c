/*
 * Changed GUI backpack slot:
 * 
 * Displays the function on pressing [Throw] if the object is useable.
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
	
	if (obj != nil && GetType(obj) != C4V_C4Object && GetType(obj) != C4V_Def)
	{
			FatalError(Format("Function needs an id or object, got %v", GetType(obj)));
	}
		
	if(!obj)
	{
		SetGraphics(nil, nil, GUI_BPS_UseIcon_Bg, GFXOV_MODE_None);
		SetGraphics(nil, nil, GUI_BPS_UseIcon_Fg, GFXOV_MODE_None);
	}
	else
	{
		var definition = nil;
		
		if (GetType(obj) == C4V_C4Object && obj->~IsUseable())
		{
			definition = obj->GetID();
			
			//if (!obj->GetUseReady()) definition = nil;
		}
		else if (GetType(obj) == C4V_Def && obj->~IsUseable())
		{
			definition = obj;
		}
		
		if (definition != nil)
		{
			var icon = definition->~GetUseIcon();
			
			if (icon == nil)
			{
				icon = definition;
			}
		
			var index = 0;
			var scale = 600;
			
			var x = 1000 * GetDefWidth()/2 - 500;
			var y = 20000 + index * GetDefHeight() * scale;
			
			SetGraphics(nil, GUI_Marker, GUI_BPS_UseIcon_Bg, GFXOV_MODE_IngamePicture);
			SetObjDrawTransform( scale, 0, x, 0, scale, y, GUI_BPS_UseIcon_Bg);	
	
			SetGraphics(nil, icon, GUI_BPS_UseIcon_Fg, GFXOV_MODE_IngamePicture);
			SetObjDrawTransform( scale, 0, x, 0, scale, y, GUI_BPS_UseIcon_Fg);	
		}
		else
		{
			SetGraphics(nil, nil, GUI_BPS_UseIcon_Bg, GFXOV_MODE_None);
			SetGraphics(nil, nil, GUI_BPS_UseIcon_Fg, GFXOV_MODE_None);
		}
		
		// if object has extra slot, show it
		if(obj->~HasExtraSlot() && obj->Contents())
		{
		}
		// or otherwise, remove it
		else
		{
		}
		
	}
}
