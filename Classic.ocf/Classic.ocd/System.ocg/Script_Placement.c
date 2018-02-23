

/**
 Places an object on surfaces.
 
 @par settings the possible settings:
               - no_stuck => true does place objects if they are stuck
               - liquid => true finds in liquid, false finds everything but liquid
               - location => set to additional Loc_*() functions if desired.
 */
global func PlaceOnSurface(int amount, proplist rectangle, proplist settings)
{
	AssertDefinitionContext();

	var max_tries = 4 * amount;

	if (!settings) settings = {};
	settings.no_stuck = settings.no_stuck ?? false;
	settings.liquid = settings.liquid ?? false;
	
	
	var loc_area = nil;
	if (rectangle) 
		loc_area = Loc_InArea(rectangle);

	var objects = [];
	var loc_bkg;
	if (settings.liquid)
	{
		loc_bkg = Loc_Liquid();
	}
	else
	{
		loc_bkg = Loc_And(Loc_Or(Loc_Tunnel(), Loc_Sky()), Loc_Not(Loc_Liquid()));
	}

	while ((amount > 0) && (--max_tries > 0))
	{
		var spot = FindLocation(loc_bkg, loc_area, Loc_Wall(CNAT_Bottom), settings.location);
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





global func PlaceInEarthExact(int amount)
{
	AssertDefinitionContext();
	PlaceObjects(this, ConvertInEarthAmount(amount), "Earth");
}


global func PlaceByCriteria(int amount)
{
	AssertDefinitionContext();
	var max_tries = 4 * amount;
	var placed = [];
	while ((amount > 0) && (--max_tries > 0))
	{
		var spot = FindLocation(...);
		if (!spot) continue;

		var obj = CreateObject(this, spot.x, spot.y, NO_OWNER);
		PushBack(placed, obj);
		--amount;
	}
	return placed;
}

/* -- Special placement -- */


global func PlaceInEarth(int relative_amount)
{
	AssertDefinitionContext();
	PlaceControl()->AddType(this, relative_amount);
}


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


global func PlaceControl()
{
	var fx = GetEffect("FxPlaceControl", Scenario);
	if (!fx)
	{
		fx = Scenario->CreateEffect(FxPlaceControl, 1, 1);
	}
	ScheduleCall();
	return fx;
}


static const FxPlaceControl = new Effect
{
	SetLevel = func(int level)
	{
		this.Level = BoundBy(level, 1, 1000);
	},
	
	AddType = func (id type, int relative_amount)
	{
		this.Objects = this.Objects ?? {};
		var data = this.Objects[Format("%i", type)];
		if (data)
		{
			data.numerator += relative_amount;
		}
		else
		{
			this.Objects[Format("%i", type)] = {type = type, numerator = relative_amount};
		}
	},
	
	Timer = func()
	{
		var material = "Earth";
		this.Objects = this.Objects ?? {};
		// Determine total amount
		var denominator = 0;
		for (var key in GetProperties(this.Objects))
		{
			denominator += Max(0, this.Objects[key].numerator);
		}
		// Place everything
		var total = ConvertInMatAmount(material, this.Level);
		for (var key in GetProperties(this.Objects))
		{
			var data = this.Objects[key];
			var amount = total * data.numerator / Max(1, denominator);
			// Insert
			PlaceObjects(data.type, amount, material);
		}
	
		return FX_Execute_Kill;
	},
};

/* -- Location conditions -- */

 // The original is broken, because liquid can count as sky...
global func Loc_Sky() {	return Loc_Material("Sky"); }


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

