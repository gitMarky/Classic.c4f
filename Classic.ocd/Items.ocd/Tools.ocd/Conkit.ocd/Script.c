/*
	Construction kit
	Author: Marky

	Not much to say, it's just the hammer with different graphics.
*/

#include Library_Constructor

private func Hit(x, y)
{
	StonyObjectHit(x, y);
	return true;
}

public func IsTool() { return true;}
public func IsToolProduct() { return true;}


local Collectible = 1;
local Name = "$Name$";
local Description = "$Description$";
local UsageHelp = "$UsageHelp$";
local Rebuy = true;
