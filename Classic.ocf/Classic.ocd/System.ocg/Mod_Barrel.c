#appendto Barrel


public func CalcValue(object in_base, int for_player)
{
	if (LiquidContainerIsEmpty())
	{
		return GetDefValue();
	}
	else
	{
		var value = 0;
		var liquid = GetLiquidType();
		
		if (liquid == "Lava"
		 || liquid == "DuroLava"
		 || liquid == "Acid") value = 4;
		if (liquid == "Oil"
		 || liquid == "FireFluid") value = 16;
		
		return GetLiquidFillLevel() * value / GetLiquidContainerMaxFillLevel();
	}
}

public func OnSale(int for_player, object in_base)
{
	CreateContents(this->GetID()); // create an empty barrel of the same kind
}