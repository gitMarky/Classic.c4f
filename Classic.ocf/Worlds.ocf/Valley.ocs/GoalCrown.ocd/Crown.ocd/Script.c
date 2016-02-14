
protected func Hit()
{
	Sound("Hits::Materials::Metal::LightMetalHit?");
}

func OnSale(int by_player, object base)
{
	var goal = FindObject(Find_ID(Goal_GetCrown));
	
	if (goal)
	{
		goal->PlayerSoldCrown(by_player);
	}
}

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;
