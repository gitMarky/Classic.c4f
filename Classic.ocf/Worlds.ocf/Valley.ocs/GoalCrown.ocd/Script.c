/*--
		Get crown
--*/


#include Library_Goal

local crown_sold_player = -1;

protected func Initialize()
{
	return inherited(...);
}

public func IsFulfilled()
{
	return crown_sold_player >= 0;
}

func GetDescription(int player)
{
	var message;
	if (IsFulfilled())
		message = Format("$MsgGoalFulfilled$", GetPlayerName(crown_sold_player));		
	else
		message = "$MsgGoalUnFulfilled$";
	return message;
}

func Activate(int player)
{
	MessageWindow(GetDescription(player), player);
	return;
}

func PlayerSoldCrown(int player)
{
	crown_sold_player = player;
}

public func GetShortDescription(int player)
{
	return "{{Crown}}";
}

/*-- Proplist --*/
local Name = "$Name$";
