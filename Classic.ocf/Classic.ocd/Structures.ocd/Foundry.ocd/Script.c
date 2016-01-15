/*--
	Foundry
	Authors: Makry (mesh, texture), Open Clonk Team (script, probably by Maikel)

	Melts iron ore to metal, using some sort of fuel.
--*/


#include Library_ClassicStructure
#include Library_Ownable
#include Library_DoorControl
#include Library_Producer

#include Basement72


func Definition(id def)
{
	def.MeshTransformation = Trans_Mul(Trans_Rotate(40, 0, 1, 0),
	                                   Trans_Translate(-16500));
	def.PictureTransformation = Trans_Mul(Trans_Rotate( 40, 0, 1, 0), 
	                                      Trans_Rotate( -5, 0, 0, 1),
	                                      Trans_Rotate(-10, 1, 0, 0),
	                                      Trans_Translate(1000, -5000, -2000));
}


/*-- Production --*/

private func IgnoreKnowledge() { return true; }

private func IsProduct(id product_id)
{
	return product_id->~IsFoundryProduct();
}

public func PowerNeed() { return 0; }
private func ProductionTime(id toProduce) { return 290; }

public func OnProductionStart(id product)
{
	AddEffect("Smelting", this, 100, 1, this);
	Sound("Structures::Furnace::Start");
	return;
}

public func OnProductionHold(id product)
{
	return;
}

public func OnProductionFinish(id product)
{
	RemoveEffect("Smelting", this);
	return;
}

/*-- Door Control --*/

private func SoundOpenDoor()
{
	Sound("GateOpen");
}

private func SoundCloseDoor()
{
	Sound("GateClose");
}

protected func Collection()
{
	Sound("Clonk");
}

public func FxSmeltingTimer(object target, proplist effect, int time)
{
	// Fire in the furnace.
	CreateParticle("Fire", -17 * GetCalcDir() + RandomX(-2, 2), 14 + RandomX(-2, 2), PV_Random(-1, 1), PV_Random(-1, 1), PV_Random(10, 18), Particles_Fire(), 2);

	// Smoke from the pipes.
	Smoke(-23 * GetCalcDir(), -26, RandomX(10, 16));

	// Furnace sound after some time.
	if (time == 30)
		Sound("Fire::Fire", false, 100, nil, +1);

	//Molten metal hits cast... Sizzling sound
	if (time == 256)
		Sound("Liquids::Sizzle");

	// Fire from the pouring exit.
	if (Inside(time, 244, 290))
		CreateParticle("SphereSpark", +23 * GetCalcDir(), +13 + RandomX(-1, 1), PV_Random(5 * GetCalcDir(), 10 * GetCalcDir()), PV_Random(-2, 3), PV_Random(18, 36), Particles_Glimmer(), 2);

	if (time == 290)
	{
		Sound("Fire::Fire", false ,100, nil, -1);
		Sound("Structures::Furnace::Stop");
		return FX_Execute_Kill;
	}

	return FX_OK;
}

public func OnProductEjection(object product)
{
	product->SetPosition(GetX() + 27 * GetCalcDir(), GetY() + 13);
	product->SetSpeed(-10, 0);
	product->SetR(30 - Random(59));
	return;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 100;
local ContainBlast = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Length = 10,
	Delay = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
	Animation = "OpenDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Delay = 20,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
	Animation = "DoorOpen",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Length = 10,
	Delay = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
	EndCall = "DoorClosed",
	Animation = "CloseDoor"
},

};
