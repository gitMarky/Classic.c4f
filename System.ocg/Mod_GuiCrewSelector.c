/*
 * Crew selector shows attached tools and equipment.
 * 
 * Author: Marky 
 */

#appendto GUI_CrewSelector

//static const GUI_CS_Base			= 0;
//static const GUI_CS_Title			= 2;
//static const GUI_CS_BreathBG		= 1;
//static const GUI_CS_HealthBG		= 3;
//static const GUI_CS_HealthBar		= 4;
//static const GUI_CS_HealthText	= 5;
//static const GUI_CS_BreathBar		= 6;
//static const GUI_CS_BreathText	= 7;
//static const GUI_CS_SpecialBar	= 8;
//static const GUI_CS_SpecialText	= 9;
//static const GUI_CS_Rank			= 10;
//static const GUI_CS_Hotkey		= 12;

static const GUI_CS_Tool_Bg			= 13; // and onwards, but we do not expect more than two tools
static const GUI_CS_Tool_Fg			= 15;
static const GUI_CS_Equipment 		= 17; // and onwards


// I just hijack this one for calling the other methods
public func UpdateTitleGraphic()
{
	UpdateAttachedTools();
	UpdateAttachedEquipment();
	_inherited();
}

public func UpdateAttachedTools()
{
	// display the tools that are attached to the clonks inventory
	var max = crew->~InventoryMaxTools();
	
	if (!max) return;
	
	var scale = 250;
	
	for (var index = 0; index < max; index++)
	{
		var tool = crew->InventoryGetAttachedTool(index);

		if (!tool)
		{
			SetGraphics(nil, nil, GUI_CS_Tool_Bg + index, GFXOV_MODE_None);
			SetGraphics(nil, nil, GUI_CS_Tool_Fg + index, GFXOV_MODE_None);
			continue;
		}
		
		var x = -1000 * GetDefWidth()/2 + 14500;
		var y = -18000 + index * GetDefHeight() * scale;
		
		SetGraphics(nil, GUI_Marker, GUI_CS_Tool_Bg + index, GFXOV_MODE_IngamePicture);
		SetObjDrawTransform( scale, 0, x, 0, scale, y, GUI_CS_Tool_Bg + index);	

		SetGraphics(nil, tool->GetID(), GUI_CS_Tool_Fg + index, GFXOV_MODE_IngamePicture);
		SetObjDrawTransform( scale, 0, x, 0, scale, y, GUI_CS_Tool_Fg + index);	
	}
}

public func UpdateAttachedEquipment()
{
	// display all of the attached equipment
}
