/*
 * Pump
 *
 * Author: Marky
 */

#include Pump
#include Basement26

protected func Definition(def) 
{
	if (def == ClassicPump)
	{
		def.PictureTransformation = Trans_Rotate(50, 0, 1, 0);
		def.MeshTransformation = Trans_Translate(1000, 4000, 0);
	}
}

func Initialize()
{
	this.MeshTransformation = ClassicPump.MeshTransformation; // somehow it always took that of the pump
	_inherited(...);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 50;
local LineAttach = [-10, 10];
