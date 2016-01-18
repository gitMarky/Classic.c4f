#appendto MetalBarrel

func IsFuel()
{
	return WildcardMatch("*Lava*", GetBarrelMaterial())
	    || WildcardMatch("Lava*", GetBarrelMaterial())
	    || WildcardMatch("*Lava", GetBarrelMaterial())
	    || WildcardMatch("Lava", GetBarrelMaterial());
}

func GetFuelAmount(bool partial)
{
	if (partial)
	{
		return GetFillLevel() / 2;
	}

	return BarrelMaxFillLevel() / 2;
}

func OnFuelRemoved(int amount)
{
	iVolume = BoundBy(iVolume - amount * 2, 0, BarrelMaxFillLevel());
	UpdateBarrel();
	return true;
}
