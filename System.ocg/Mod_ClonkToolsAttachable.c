/*
 * This part lets clonks items to their inventory.
 * 
 * Two kinds of attachable items exist: tools (shovel, hammer, etc.) and equipment (alchemy bag, armor).
 *
 * Tools are limited to two at a time, one useable with ControlDig and the second useable with ControlDigDouble.
 * 
 * Equipment is not limited (in most cases, except stacking items of the same category) and they need no activation.
 * 
 * Author: Marky
 */

#appendto ClassicClonk

local inventory_saver; // contains the items
local inventory_tools; // array, saves the attached tools
local inventory_equipment; // array, saves the attached equipment

local iToolMesh;

protected func Construction()
{
	inventory_saver = CreateObject(Dummy,0,0,NO_OWNER);
	inventory_saver.clonk = this;
	inventory_tools = CreateArray();
	inventory_equipment = CreateArray();
	iToolMesh = CreateArray();
	
	_inherited(...);
}

protected func Destruction()
{
	// Exit all saved contents as well
	if (inventory_saver)
	{
		inventory_saver->SetPosition(GetX(), GetY());
		inventory_saver->RemoveObject(true);
	}
	
	return _inherited(...);
}

private func InventoryMaxTools(){ return 2;}

private func ContextMenuAddEntriesInventory()
{
	var entries = 0;
	var toolsInInventory = FindObjects(Find_Container(this), Find_Func("IsAttachableTool"));
	
	var attachedToolIDs = CreateArray();
	
	for(var toolIndex = 0; toolIndex < InventoryMaxTools(); toolIndex++)
	{
		if(inventory_tools[toolIndex])
			PushBack(attachedToolIDs, inventory_tools[toolIndex]->GetID());
	}

	for(var toolIndex = 0; toolIndex < InventoryMaxTools(); toolIndex++)
	{
		var interjection = "";

		if(InventoryMaxTools() > 1)
			interjection = Format(" [%d]", toolIndex+1);

		// add attach dialogue for open slots
		if (!inventory_tools[toolIndex] && GetLength(toolsInInventory))
		{
			// one option for every tool
			for(var tool in toolsInInventory)
			{
				// only one tool of each kind
				if(!IsValueInArray(attachedToolIDs, tool->GetID()))
				{
					if (!GetEffect("IntShowToolAttach", tool))
						 AddEffect("IntShowToolAttach", tool, 1, 1, this);

					var effect = GetEffect("IntShowToolAttach", tool);

					AddMenuItem(Format("%s%s: %s", "$TxtAttachTool$", interjection, tool.Name), Format("InventoryAttachTool(%d,Object(%d))", toolIndex, tool->ObjectNumber()), nil, nil, nil, nil, C4MN_ItemExtra_Object, effect.icon);
					entries++;
				}
			}
		}

		if (inventory_tools[toolIndex])
		{
			AddMenuItem(Format("%s%s: %s", "$TxtDetachTool$", interjection, inventory_tools[toolIndex].Name), "InventoryDetachTool", nil, nil, toolIndex, nil, C4MN_ItemExtra_Object, inventory_tools[toolIndex]);
			entries++;
		}
	}
	
	return entries;
}

public func InventoryAttachTool(int index, object tool)
{
	if (!tool) return;
	if (inventory_tools[index]) return;
	
	inventory_tools[index] = tool;
	tool->Enter(inventory_saver);

	if (!GetEffect("IntShowToolDetach", tool))
		 AddEffect("IntShowToolDetach", tool, 1, 0, this);

	UpdateAttach();
}

public func InventoryGetAttachedTool(int index)
{
	return inventory_tools[index];
}

public func InventoryGetAttachedEquipment(int index)
{
	return inventory_equipment[index];
}
public func InventoryDetachTool(id symbol, int index)
{
	if (!inventory_tools[index]) return;
	
	inventory_tools[index]->Exit();
	inventory_tools[index]->SetPosition(this->GetX(),this->GetY());

	if (GetEffect("IntShowToolDetach", inventory_tools[index]))
     RemoveEffect("IntShowToolDetach", inventory_tools[index]);

	inventory_tools[index] = nil;
	UpdateAttach();

	return;
}

protected func FxIntShowToolAttachStart(object tool, proplist effect, int temporary)
{
	if (temporary) return;

	effect.icon = CreateObject(Icon_Dummy, 0, 0, NO_OWNER);
	effect.icon->SetGraphics(nil, tool->GetID(), 0, GFXOV_MODE_Picture);
	effect.icon->SetGraphics(nil, Icon_AttachTool, 1, GFXOV_MODE_Picture);
}

protected func FxIntShowToolAttachTimer(object tool, proplist effect, int timer)
{
	if (!tool) return -1;
	if (!IsMenuOpen()) return -1;
}

protected func FxIntShowToolAttachStop(object tool, proplist effect, int reason, bool temporary)
{
	if (temporary) return;
	if (effect.icon) effect.icon->RemoveObject();
}

protected func FxIntShowToolDetachStart(object tool, proplist effect, int temporary)
{
	if (temporary) return;

	effect.overlay = tool->GetUnusedOverlayID(1);

	tool->SetGraphics("Detach", Icon_AttachTool, effect.overlay, GFXOV_MODE_Picture);
}

protected func FxIntShowToolDetachStop(object tool, proplist effect, int reason, bool temporary)
{
	if (temporary) return;
	if (tool) tool->SetGraphics(nil, nil, effect.overlay, GFXOV_MODE_None);
}



func UpdateAttach()
{
	StopAnimation(GetRootAnimation(6));
	DoUpdateAttach(0);
	DoUpdateAttach(1);
	
	for(var toolIndex = 0; toolIndex < InventoryMaxTools(); toolIndex++)
	{
		DoUpdateAttachTool(toolIndex);
		DoUpdateAttachTool(toolIndex); // maybe this helps??
	}

	if (GetSelector()) GetSelector()->UpdateTitleGraphic();
}

func DoUpdateAttachTool(index)
{
	if(iToolMesh[index])
	{
		DetachMesh(iToolMesh[index]);
		iToolMesh[index] = nil;
	}

	var tool = inventory_tools[index];
	if (!tool) return;
		
	var iAttachMode = tool->~GetCarryMode(this);
	if (iAttachMode == CARRY_None) return;


	var bone = "main";
	var bone2;
	if(tool->~GetCarryBone())  bone  = tool->~GetCarryBone(this);
	if(tool->~GetCarryBone2()) bone2 = tool->~GetCarryBone2(this);
	else bone2 = bone;
	var nohand = 0;
	if(!HasHandAction(index, 1)) nohand = 1;
	var trans = tool->~GetCarryTransform(this, index, nohand);

	var pos_hand = "pos_hand2";
	if(index) pos_hand = "pos_hand1";
	var pos_back = "pos_back1";
	if(index) pos_back = "pos_back2";
	var closehand = "Close2Hand";
	if(index) closehand = "Close1Hand";

	if(!index) fBothHanded = 0;

	var special = tool->~GetCarrySpecial(this);

	if(special)
	{
		iToolMesh[index] = AttachMesh(tool, special, bone, trans);
		iAttachMode = 0;
	}

	if(iAttachMode == CARRY_Hand)
	{
		if(HasHandAction(index, 1))
		{
			iToolMesh[index] = AttachMesh(tool, pos_hand, bone, trans);
			PlayAnimation(closehand, 6, Anim_Const(GetAnimationLength(closehand)), Anim_Const(1000));
		}
		else
			; // Don't display
	}
	else if(iAttachMode == CARRY_HandBack)
	{
		if(HasHandAction(index, 1))
		{
			iToolMesh[index] = AttachMesh(tool, pos_hand, bone, trans);
			PlayAnimation(closehand, 6, Anim_Const(GetAnimationLength(closehand)), Anim_Const(1000));
		}
		else
			iToolMesh[index] = AttachMesh(tool, pos_back, bone2, trans);
	}
	else if(iAttachMode == CARRY_HandAlways)
	{
		iToolMesh[index] = AttachMesh(tool, pos_hand, bone, trans);
		PlayAnimation(closehand, 6, Anim_Const(GetAnimationLength(closehand)), Anim_Const(1000));
	}
	else if(iAttachMode == CARRY_Back)
	{
		iToolMesh[index] = AttachMesh(tool, pos_back, bone2, trans);
	}
	else if(iAttachMode == CARRY_BothHands)
	{
		if(index) return;
		if(HasHandAction(index, 1) && !index)
		{
			iToolMesh[index] = AttachMesh(tool, "pos_tool1", bone, trans);
			PlayAnimation("CarryArms", 6, Anim_Const(tool->~GetCarryPhase(this)), Anim_Const(1000));
			fBothHanded = 1;
		}
		else
			; // Don't display
	}
	else if(iAttachMode == CARRY_Spear)
	{
		if(HasHandAction(index, 1) && !index)
		{
			PlayAnimation("CarrySpear", 6, Anim_Const(0), Anim_Const(1000));
		}
		else
			iToolMesh[index] = AttachMesh(tool, pos_back, bone2, trans);
	}
	else if(iAttachMode == CARRY_Musket)
	{
		if(HasHandAction(index, 1) && !index)
		{
			iToolMesh[index] = AttachMesh(tool, "pos_hand2", bone, trans);
			PlayAnimation("CarryMusket", 6, Anim_Const(0), Anim_Const(1000));
			fBothHanded = 1;
		}
		else
			iToolMesh[index] = AttachMesh(tool, pos_back, bone2, trans);
	}
	else if(iAttachMode == CARRY_Grappler)
	{
		if(HasHandAction(index, 1) && !index)
		{
			iToolMesh[index] = AttachMesh(tool, "pos_hand2", bone, trans);
			PlayAnimation("CarryCrossbow", 6, Anim_Const(0), Anim_Const(1000));
			fBothHanded = 1;
		}
		else
			iToolMesh[index] = AttachMesh(tool, pos_back, bone2, trans);
	}
}

protected func InventoryUseTool(bool secondary, bool attached)
{
	inventory_saver->SetPosition(this->GetX(),this->GetY());

	var tool;

	if (!attached)
	{
		tool = Contents();
	}
	else
	{
		if (!secondary)
			tool = inventory_tools[0];
		else
			tool = inventory_tools[1];
	}
	
	if (!tool) return false;
	
	if (tool->~AttachedToolIsInUse(this))
		return tool->~AttachedToolCancelUse(this);
	else
		return tool->~AttachedToolStartUse(this);
}
