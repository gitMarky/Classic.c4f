/**
	Knowdlege
	Provides global functions to give players knowledge for scenarios.
	
	@author Maikel
*/

 
// Gives the player specific knowledge as given in the knowledge array.
global func GivePlayerSpecificKnowledge(int plr, array knowledge)
{
	for (var plan in knowledge)
		SetPlrKnowledge(plr, plan);
}

// Removes the player specific knowledge as given in the knowledge array.
global func RemovePlayerSpecificKnowledge(int plr, array knowledge)
{
	for (var plan in knowledge)
		SetPlrKnowledge(plr, plan, true);
}

// Gives the player plans according to basic knowledge.
global func GivePlayerBasicKnowledge(int plr)
{
	var knowledge = [
		// Basic structures for a settlement and production of tools and explosives.
		Flagpole, Basement, WindGenerator, SteamEngine, Compensator, Sawmill, Foundry, Elevator, ToolsWorkshop, ChemicalLab, Chest,
		// Basic tools for mining and tree chopping and loam production.
		Shovel, Hammer, Axe, Pickaxe, Barrel, Bucket, Torch,
		// The basic resources.
		Metal, Loam, GoldBar,
		// Some of the basic explosives.
		Dynamite, DynamiteBox,
		// Some basic vehicles which aid in the settlement construction.
		Lorry
	];
	for (var plan in knowledge)
		SetPlrKnowledge(plr, plan);
	return;
}

global func GivePlayerPowerKnowledge(int plr)
{
	GivePlayerSpecificKnowledge(plr, [ClassicWindmill, ClassicPowerPlant]);
}

global func GivePlayerChemicalKnowledge(int plr)
{
	GivePlayerSpecificKnowledge(plr, [ClassicChemicalFactory, Flint, TFlint, ClassicDynamiteBox]);
}

global func GivePlayerPumpingKnowledge(int plr)
{
	GivePlayerSpecificKnowledge(plr, [ClassicPump, MetalBarrel, Pipe]);
}

global func GivePlayerMiningKnowledge(int plr)
{
	GivePlayerSpecificKnowledge(plr, [ClassicElevator, ClassicLorry]);
}
