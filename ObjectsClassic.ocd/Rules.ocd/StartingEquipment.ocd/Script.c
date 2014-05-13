/*
 * Clonks start with starting equipment.
 *
 * Author: Marky
 */


protected func InitializePlayer(int player)
{
	SetPlayerZoomByZoomFactor(player, GetScenarioZoomMax(), PLRZOOM_LimitMax, GetScnearioZoomPrecision());
	SetPlayerZoomByZoomFactor(player, GetScenarioZoomMin(), PLRZOOM_LimitMin, GetScnearioZoomPrecision());
	SetPlayerZoomByZoomFactor(player, GetScenarioZoomMin(), PLRZOOM_Direct, GetScnearioZoomPrecision());
}

protected func OnClonkRecruitment(object crew, int plr)
{
	crew->InventoryAttachTool(0, CreateObject(Shovel, 0, 0, NO_OWNER));
	crew->InventoryAttachTool(1, CreateObject(Axe, 0, 0, NO_OWNER));
}


local Name = "$Name$";
local Description = "$Description$";
