/*
 * Limit zoom to given factors.
 *
 * Author: Marky
 */

global func GetScenarioZoomMin(){ return 2;}
global func GetScenarioZoomMax(){ return 1;}
global func GetScnearioZoomPrecision(){ return 1;}


protected func InitializePlayer(int player)
{
	SetPlayerZoomByZoomFactor(player, GetScenarioZoomMax(), PLRZOOM_LimitMax, GetScnearioZoomPrecision());
	SetPlayerZoomByZoomFactor(player, GetScenarioZoomMin(), PLRZOOM_LimitMin, GetScnearioZoomPrecision());
	SetPlayerZoomByZoomFactor(player, GetScenarioZoomMin(), PLRZOOM_Direct, GetScnearioZoomPrecision());
}

global func SetPlayerZoomByZoomFactor(int player, int zoom, int flags, int precision)
{
	var prec = 1;

	if (precision > 0) prec = precision;

	var range = 690 * prec / zoom;

	return SetPlayerZoomByViewRange(player, range, range, flags);
}

local Name = "$Name$";
local Description = "$Description$";
