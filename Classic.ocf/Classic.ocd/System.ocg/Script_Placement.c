
/**
 Adjusts an amount to the map size, if 
 the scenario has a function 'AdjustAmountToMapSize'.
 Otherwise leaves the amount as it is.
 */
global func AdjustToMapSize(int amount)
{
	if (Scenario.AdjustAmountToMapSize)
	{
		return Scenario->AdjustAmountToMapSize(amount);
	}
	else
	{
		return amount;
	}
}


/**
 Places an object on surfaces.
 
 @par settings the possible settings:
               - no_stuck => true does place objects if they are stuck
 */
global func PlaceOnSurface(int amount, proplist rectangle, proplist settings)
{
	AssertDefinitionContext();

	var max_tries = 4 * amount;

	if (!settings) settings = {};
	settings.no_stuck = settings.no_stuck ?? false;
	
	var loc_area = nil;
	if (rectangle) 
		loc_area = Loc_InArea(rectangle);

	var objects = [];
	var loc_bkg = Loc_Or(Loc_Tunnel(), Loc_Sky());

	while ((amount > 0) && (--max_tries > 0))
	{
		var spot = FindLocation(loc_bkg, loc_area, Loc_Wall(CNAT_Bottom));
		if (!spot)
			continue;
		
		var thing = CreateObject(this, spot.x, spot.y, NO_OWNER);
		if (!thing) 
			continue;
		
		if (settings.no_stuck && thing->Stuck())
		{
			thing->RemoveObject();
			continue;
		}
		PushBack(objects, thing);
		--amount;
	}
	
	return objects;
}


global func PlaceInEarth(int amount)
{
	AssertDefinitionContext();
	PlaceObjects(this, ConvertInEarthAmount(amount), "Earth");
}


global func LocFunc_HasSunLight(int x, int y)
{
	var limit = y - 250;
	for (var ynew = y; ynew >= limit; ynew -= 5)
	{
		if (GBackSky(x, ynew))
		{
			return true;
		}
	}
	return false;
}

