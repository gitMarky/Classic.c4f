/*
	Construction kit
	Author: Marky

	Not much to say, it's just the hammer with different graphics.
*/

#include Library_Useable
#include Library_Constructor

private func Hit(x, y)
{
	StonyObjectHit(x, y);
	return true;
}

public func IsTool() { return true;}
public func IsToolProduct() { return true;}

public func GetUseIcon()
{
	return Icon_Construction;
}


local Collectible = 1;
local Name = "$Name$";
local Description = "$Description$";
local UsageHelp = "$UsageHelp$";
local Rebuy = true;
local Components = {Wood = 2, Metal = 1};
