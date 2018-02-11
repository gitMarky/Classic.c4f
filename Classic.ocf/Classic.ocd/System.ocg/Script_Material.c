
/**
 Conversion method for placing objects in earth, as in old Clonk Rage
 scenarios. This can work as a general indicator for the size of the map,
 though, and can be used for animals, vegetation, etc., too.
 */
global func ConvertInEarthAmount(int amount, int divisor)
{
	var materialAmount = GetMaterialCount(Material("Earth"));
	var factor = Max(1, materialAmount / 40000); // creates a factor of 10 most of the time
	return amount * factor / Max(divisor, 1);
}
