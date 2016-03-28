#appendto Barrel


public func CalcValue(object in_base, int for_player)
{
	if (GetLiquidAmount() == 0)
	{
		return GetDefValue();
	}
	else
	{
		var value = 0;
		for (var liquid in Contents())
		{
			if (liquid->~GetLiquidType())
			{
				value += liquid->GetValue();
			}
		}
		
		return value;
	}
}

public func OnSale(int for_player, object in_base)
{
	CreateContents(this->GetID()); // create an empty barrel of the same kind
}