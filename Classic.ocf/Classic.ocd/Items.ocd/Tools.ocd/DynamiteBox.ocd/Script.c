/**
	Dynamite box
	Contains five dynamite sticks which can be placed and detonated from a distance. 
*/

#include DynamiteBox

func Construction()
{
	_inherited(...);
	SetGraphics(nil, DynamiteBox);
}

local Collectible = 1;
local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 1;
local ContactIncinerate = 2;
