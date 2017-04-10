/*--- The Log ---*/

protected func Hit()
{
	Sound("Hits::Materials::Wood::WoodHit?");
}

func Incineration()
{
	SetClrModulation (RGB(48, 32, 32));
}

public func IsFuel() { return true; }
public func GetFuelAmount(bool get_partial) 
{ 
	if (get_partial)
		return GetCon() / 2;
	return 50;
}
public func IsSawmillProduct() { return true; }

local Collectible = true;
local Name = "$Name$";
local Description = "$Description$";
local Rebuy = true;
local BlastIncinerate = 5;
local ContactIncinerate = 1;
local Plane = 470;