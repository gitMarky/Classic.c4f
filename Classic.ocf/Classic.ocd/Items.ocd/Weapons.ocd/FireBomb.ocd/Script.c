/*-- Fire bomb --*/

protected func Hit()
{
	// Cast flames on impact.
	for (var i = 0; i < 20; i++)
		CastObjects(Flame, 1, 20, RandomX(-3, 3), RandomX(-4, 0));

	// Sound effects.
	Sound("Fire::Inflame");
 	RemoveObject();
}


public func IsChemicalProduct() { return true;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
