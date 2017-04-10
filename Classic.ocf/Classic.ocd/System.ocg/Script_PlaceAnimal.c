
static const PLACEMENT_Surface = 0;
static const PLACEMENT_Liquid = 1;
static const PLACEMENT_Air = 2;
static const PLACEMENT_Tunnel = 3;
static const PLACEMENT_Burrow = 4;
static const PLACEMENT_Material_Any = -1;

/**
 Better Animal Placement. 
 
 @par definition Object to be placed.
 @par amount Quantity to be planted.
 @par rectangle [optional] Target rectangle as array [x, y, width, height]. Always in absolute coordinates.
 @par placement [optional]
 {@table
  {@tr {@th Constant} {@th Value} {@th Description}}
  {@tr {@td PLACEMENT_Surface} {@td 0} {@td Placement on solid material.}}
  {@tr {@td PLACEMENT_Liquid} {@td 1} {@td Placement in liquids.}}
  {@tr {@td PLACEMENT_Air} {@td 2} {@td Placement in air.}}
  {@tr {@td PLACEMENT_Tunnel} {@td 3} {@td Placement with tunnel background.}}
  {@tr {@td PLACEMENT_Burrow} {@td 4} {@td Not functional yet.}}
 }
 @par material [optional]
 - For placement = 0 or 3: the Material it should be place on top of; For placement=1: the liquid it should be placed in (use -1 for any solid or liquid respectively)   
 - Can be single material or array] TODO
 @par con_range Array with [minimal, maximal] growth rates of the animal. If {@c nil} is passed the growth rate will be always 100%.
 @return array An array with the placed animals.
 @author Tyron, GZE Project
 @version 0.3
 */
global func PlaceAnimals(id definition, int amount, int placement, int material, proplist rectangle, array con_range)
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

	var x, y, width, height;
	
	if (rectangle == nil)
	{
		x = 0;
		y = 0;
		width = LandscapeWidth();
		height = LandscapeHeight();
	}
	else
	{
	 	x = rectangle.x;
	 	y = rectangle.y;
	 	width = rectangle.w;
	 	height = rectangle.h;
	}
	
	if (this) // make coordinates local in object context
	{
		x -= GetX();
		y -= GetY();
	}

	if (con_range == nil)
	{
		con_range = [100, 100];
	}
	
	
	// At least 120% of the objects height must be free vertically
	var minverticalspace = (definition->GetDefHeight() * 5) / 4;
	// Minimum distance between other animals
	var mindistance = Max(10, definition->GetDefWidth());
	
	// The Material the object will be placed in
	var freemat = -1; // in air for placement == PLACEMENT_Surface  and placement == PLACEMENT_Air
	if (placement == PLACEMENT_Tunnel)
		freemat = Material("Tunnel");
	if (placement == PLACEMENT_Liquid)
		freemat = material;
	
	// Create a dozen random places and try there
	var random_x, random_y, is_valid, mat_at_pos;
	
	var any_material = (material == PLACEMENT_Material_Any);
	
	// to make the loop a bit more efficient we do this calculation outside the loop - these are adjustments for root depth etc.
	var realy_diff;
	
	realy_diff = definition->GetDefHeight() / 2;
	
	var animals = [];

		for (var i = 0, attempts = 0; i < amount && attempts < 40000; attempts++)
		{
			random_x = x + Random(width);
			random_y = y + Random(height);
			mat_at_pos = GetMaterial(random_x, random_y);
			
			is_valid = (placement == PLACEMENT_Surface || placement == PLACEMENT_Tunnel)
			    && ((!any_material && mat_at_pos == material) || (any_material && GBackSolid(random_x, random_y)));
			
			// On surface or in caves => search upwards vertically
			while (is_valid && GetMaterial(random_x, random_y) != freemat)
			{
				is_valid = (!any_material && GetMaterial(random_x, random_y) == material) || (any_material && GBackSolid(random_x, random_y));
				random_y--;
			}
			
			// We got air for air placement
			is_valid = is_valid || placement == PLACEMENT_Air && mat_at_pos == -1;
			
			// We got the right liquid for liquid placement
			is_valid = is_valid || (placement == PLACEMENT_Liquid && ((!any_material && mat_at_pos == material) || (any_material && GBackLiquid(random_x, random_y))));
			
			if (is_valid)
			{
				// Search upwards/downwards again to see how much free vertical space we have
				var rndy_spacecheck = random_y, testverticalspace = minverticalspace;
				
				while (is_valid && testverticalspace > 0)
				{
					is_valid = ((placement != PLACEMENT_Liquid || !any_material)
					          && GetMaterial(random_x, rndy_spacecheck) == freemat)
					          || (placement == PLACEMENT_Liquid && any_material && GBackLiquid(random_x, rndy_spacecheck));
					rndy_spacecheck--;
					testverticalspace--;
				}
			}
			
			// Ok, enough vertical space
			if (is_valid)
			{
				if (!FindObject(Find_ID(definition), Find_Distance(mindistance, random_x, random_y)))
				{
					var animal = CreateObjectAbove(definition, random_x, random_y);

					animal->SetCon(BoundBy(RandomX(con_range[0], con_range[1]), 1, 100));
					animals[i] = animal;
					i++;
				}
			}
		}
	
	return animals;
}
