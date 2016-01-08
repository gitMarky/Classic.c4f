/*
 * Clonks start with starting equipment.
 *
 * Author: Marky
 */


protected func OnClonkRecruitment(object crew, int plr)
{
	crew->CreateContents(Shovel);
	crew->CreateContents(Axe);
	//crew->InventoryAttachTool(0, CreateObject(Shovel, 0, 0, NO_OWNER));
	//crew->InventoryAttachTool(1, CreateObject(Axe, 0, 0, NO_OWNER));
}


local Name = "$Name$";
local Description = "$Description$";
