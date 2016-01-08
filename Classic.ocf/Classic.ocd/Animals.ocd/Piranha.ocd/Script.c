/*
 * Piranha
 *
 * Author: Marky, original from Clonk Rage
 */

#include Fish


protected func Death()
{
	_inherited();
	ChangeDef(DeadPiranha);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
// Properties

local Name="$Name$";
local MaxEnergy=40000;
local MaxBreath = 1440; // Piranha can breathe for 40 seconds on land.
local Description="$Description$";
local Collectible=1;
local NoBurnDecay=1;
local BreatheWater=1;
local BorderBound=5;

