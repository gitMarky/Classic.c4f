/*
 * Limit zoom to given factors.
 *
 * Author: Marky
 */

global func GetScenarioZoomMin(){ return 1;}
global func GetScenarioZoomMax(){ return 3;}
global func GetScnearioZoomPrecision(){ return 1;}


protected func InitializePlayer(int player)
{
	SetPlayerZoom(player, GetScenarioZoomMax(), GetScnearioZoomPrecision(), PLRZOOM_LimitMax);
	SetPlayerZoom(player, GetScenarioZoomMin(), GetScnearioZoomPrecision(), PLRZOOM_LimitMin);
	SetPlayerZoom(player, (GetScenarioZoomMin() + GetScenarioZoomMax()) / 2, GetScnearioZoomPrecision(), PLRZOOM_Direct);
}

local Name = "$Name$";
local Description = "$Description$";
