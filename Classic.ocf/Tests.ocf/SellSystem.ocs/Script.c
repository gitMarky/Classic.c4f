/**
	Power System
	Unit tests for the power system. 
*/


static script_plr;

protected func Initialize()
{
}

protected func InitializePlayer(int player)
{
	StartTest(player);
	return;
}

global func StartTest(int player)
{
	var passed = true;
	
	var seller = CreateObjectAbove(ClassicHutWooden, GetCrew(player)->GetX(), GetCrew(player)->GetY() + 10, player);
	
	Log("---------------------");
	Log("Testing Sell System:");

	var test_data = [
		["Oil", 16],
		["Lava", 4],
		["Acid", 4],
		["Water", 0]];
		
	var barrels = [Barrel, MetalBarrel];
	
	for (var barrel_type in barrels)
	{
		for (var data in test_data)
		{
			var liquid = data[0];
			var profit = data[1];
			passed &= TestSellBarrel(player, seller, barrel_type, liquid, barrel_type->GetLiquidContainerMaxFillLevel(), profit);
			passed &= TestSellBarrel(player, seller, barrel_type, liquid, barrel_type->GetLiquidContainerMaxFillLevel() / 2, profit / 2);
			passed &= TestSellBarrel(player, seller, barrel_type, liquid, barrel_type->GetLiquidContainerMaxFillLevel() / 4, profit / 4);
		}
	}

	Log("---------------------");
	Log("Done!");
	if (passed)
	{
		Log("All tests passed!");
	}
	else
	{
		Log("Test failed");
	}
}


global func TestSellBarrel(int player, object seller, id def, string liquid, int fill_level, int expected_profit)
{
	var passed = true;
	SetWealth(player, 0);

	var barrel = seller->CreateContents(def);
	barrel->SetLiquidContainer(liquid, fill_level);

	seller->DoSell(barrel, player);
	
	var profit = GetWealth(player);
	var test = profit == expected_profit; passed &= test;
	Log(" - Selling %s barrel, filled 100%: profit = %d, expected %d; passed: %v", liquid, profit, expected_profit, test);	

	SetWealth(player, 0);
	
	test = (barrel == nil); passed &= test;
	Log("  * Barrel got removed: %v", test);
	var remaining_barrel = FindObject(Find_ID(def));
	test = (remaining_barrel != nil); passed &= test;
	Log("  * New barrel spawned: %v", test);

	if (remaining_barrel)
	{
		test = remaining_barrel->LiquidContainerIsEmpty(); passed &= test;
		Log("  * New barrel is empty: %v", test);
		
		remaining_barrel->RemoveObject();
	}
	
	if (barrel) barrel->RemoveObject();

	return test;
}