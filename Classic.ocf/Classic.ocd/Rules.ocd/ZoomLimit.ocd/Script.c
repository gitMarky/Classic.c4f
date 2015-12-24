/*
 * Limit zoom to given factors.
 *
 * Author: Marky
 */

global func GetScenarioZoomMin(){ return 1;}
global func GetScenarioZoomMax(){ return 2;}
global func GetScnearioZoomPrecision(){ return 1;}


protected func InitializePlayer(int player)
{
	SetPlayerZoom(player, GetScenarioZoomMax(), GetScnearioZoomPrecision(), PLRZOOM_LimitMax);
	SetPlayerZoom(player, GetScenarioZoomMin(), GetScnearioZoomPrecision(), PLRZOOM_LimitMin);
	SetPlayerZoom(player, GetScenarioZoomMin(), GetScnearioZoomPrecision(), PLRZOOM_Direct);
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
