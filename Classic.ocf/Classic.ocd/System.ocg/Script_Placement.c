/**
 Places objects on the map, relative to the map size
 */
global func PlaceByMapSize(int amount, proplist rectangle, proplist settings)
{
	AssertObjectContext();
	return this->Place(ConvertInEarthAmount(amount, 9), rectangle, settings, ...);
}
