global func ConvertInEarthAmount(int amount)
{
	var materialAmount = GetMaterialCount(Material("Earth"));
	var factor = materialAmount / 40000; // creates a factor of 10 most of the time
	return amount * factor;
}