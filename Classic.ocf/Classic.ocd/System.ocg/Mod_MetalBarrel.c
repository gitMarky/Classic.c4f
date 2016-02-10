#appendto MetalBarrel

func IsFuel()
{
	return WildcardMatch("Lava", GetLiquidType())
	    || WildcardMatch("Oil", GetLiquidType());
}
