/**
 @author Marky
 @credits Tyron, GZE Project
 @version 0.3
 */


/**
 Places objects on the map, relative to the map size
 */
global func PlaceByMapSize(int amount, proplist rectangle, proplist settings)
{
	AssertObjectContext();
	return this->Place(ConvertInEarthAmount(amount, 9), rectangle, settings, ...);
}


static const PLACEMENT_Type_Object = 1;
static const PLACEMENT_Type_Animal = 2;
static const PLACEMENT_Type_Vegetation = 4;

static const PLACEMENT_Amount_Relative = true;
static const PLACEMENT_Amount_Absolute = false;
 
global func AutoPlaceObject(id definition, int amount, bool amount_relative, array rectangle)
{
	if (definition == nil)
	{
		FatalError("This function needs a definition");
	}
	
	if (amount == nil)
	{
		amount = 1;
	}
	else if (amount < 0)
	{
		FatalError("Cannot place a negative amount!");
	}
	
	// default: absolute amount
	if (amount_relative == nil)
	{
		amount_relative = PLACEMENT_Amount_Absolute;
	}
	
	// default: whole landscape
	if (rectangle == nil)
	{
		rectangle = [];
		rectangle[0] = 0;
		rectangle[1] = 0;
		rectangle[2] = LandscapeWidth();
		rectangle[3] = LandscapeHeight();
	}
	
	var placement = definition.PlacementType; // new property!!
	
	// default
	if (placement == nil)
	{
		placement = PLACEMENT_Type_Object;
	}
	
	if (placement & PLACEMENT_Type_Vegetation)
	{
		AutoPlaceVegetation(definition, amount, rectangle);
	}
}
