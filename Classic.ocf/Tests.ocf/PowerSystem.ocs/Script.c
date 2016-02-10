/**
	Power System
	Unit tests for the power system. 
*/


static script_plr;

protected func Initialize()
{
	// Create a script player for some tests.
	script_plr = nil;
	CreateScriptPlayer("PowerBuddy", RGB(0, 0, 255), nil, CSPF_NoEliminationCheck);
	return;
}

protected func InitializePlayer(int plr)
{
	// Set zoom to full map size.
	SetPlayerZoomByViewRange(plr, LandscapeWidth(), nil, PLRZOOM_Direct);
	
	// No FoW to see everything happening.
	SetFoW(false, plr);
	
	// All players belong to the first team.
	// The second team only exists for testing.
	SetPlayerTeam(plr, 1);
		
	// Initialize script player.
	if (GetPlayerType(plr) == C4PT_Script)
	{
		// Store the player number.
		if (script_plr == nil)
			script_plr = plr;
		// No crew needed.
		GetCrew(plr)->RemoveObject();
		return;
	}	
	
	// Move player to the start of the scenario.
	GetCrew(plr)->SetPosition(120, 150);
	
	// Some knowledge to construct a flagpole.
	GetCrew(plr)->CreateContents(Hammer);
	SetPlrKnowledge(plr, Flagpole);
	
	// Add test control effect.
	StartTests(plr);
	return;
}

protected func RemovePlayer(int plr)
{
	// Remove script player.
	if (GetPlayerType(plr) == C4PT_Script)
	{
		if (plr == script_plr)
			script_plr = nil;
		return;	
	}
	return;
}

/*-- Power Tests --*/

// Test for power plant fueled by oil barrels.
global func Test1_OnStart(int plr)
{
	// Power source: one power plant.
	var engine = CreateObjectAbove(ClassicPowerPlant, 100, 160, plr);

	for (var i = 0; i < 3; ++i)
	{
		var barrel = engine->CreateContents(Barrel, 1);
		barrel->SetLiquidContainer("Oil", 10);
	}
	
	// Power consumer: chemical plant.
	var chemical = CreateObjectAbove(ClassicChemicalFactory, 280, 160, plr);
	chemical->CreateContents(Coal, 5);
	chemical->AddToQueue(GunPowder, 5);

	// Log what the test is about.
	Log("A power plant fueled by oil barrels.");
	return true;
}

global func Test1_Completed()
{
	return (ObjectCount(Find_ID(GunPowder)) >= 5);
}

global func Test1_OnFinished()
{
	RemoveAll(Find_Or(Find_ID(ClassicPowerPlant), Find_ID(ClassicChemicalFactory)));
	return;
}

// Test for power plant fueled by oil field and pump.
global func Test2_OnStart(int plr)
{
	// Oil field
	DrawMaterialQuad("Oil", 144, 168, 208 + 1, 168, 208 + 1, 304, 144, 304, true);

	// Power source: one power plant.
	var engine = CreateObjectAbove(ClassicPowerPlant, 70, 160, plr);
	engine.fuel_amount = 100;
	
	// Power consumer: one pump.
	var pump = CreateObjectAbove(ClassicPump, 124, 160, plr);
	var source = CreateObjectAbove(Pipe, 176, 292, plr);
	source->ConnectPipeTo(pump, PIPE_STATE_Source);
	var drain = CreateObjectAbove(Pipe, 100, 160, plr);
	drain->ConnectPipeTo(pump, PIPE_STATE_Drain);
	drain->ConnectPipeTo(engine);
	
	
	// Power consumer: chemical plant.
	var chemical = CreateObjectAbove(ClassicChemicalFactory, 280, 160, plr);
	chemical->CreateContents(Coal, 10);
	chemical->AddToQueue(GunPowder, 10);

	// Log what the test is about.
	Log("A power plant fueled by an oil field via pump.");
	return true;
}

global func Test2_Completed()
{
	return (ObjectCount(Find_ID(IronBomb)) >= 10);
}

global func Test2_OnFinished()
{
	RestoreWaterLevels();
	RemoveAll(Find_Or(Find_ID(ClassicPowerPlant), Find_ID(ClassicChemicalFactory), Find_ID(Pipe), Find_ID(ClassicPump)));
	return;
}


/*-- Helper Functions --*/

global func RestoreWaterLevels()
{
	// Restore water levels.
	DrawMaterialQuad("Water", 144, 168, 208 + 1, 168, 208 + 1, 304, 144, 304, true);
	for (var x = 216; x <= 280; x++)
		for (var y = 24; y <= 120; y++)
			if (GetMaterial(x, y) == Material("Water"))
				ClearFreeRect(x, y, 1, 1);
	return;
}

global func RemoveWater()
{
	for (var x = 144; x <= 208 + 1; x++)
		for (var y = 168; y <= 304; y++)
			if (GetMaterial(x, y) == Material("Water"))
				ClearFreeRect(x, y, 1, 1);
	return;
}
