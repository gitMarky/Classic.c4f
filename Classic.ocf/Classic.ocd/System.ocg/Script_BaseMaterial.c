/**
 	Better base material

	Creating custom setups for base material is tedious, so here are some functions that should help speed up the process.

	@author Marky
 */

/* -- Additional functions -- */

/**
 Sets the minimum amount of base material that a player has.
 Does nothing if the player already has more than this amount.
 */
global func SetBaseMaterialAtLeast(int player, id material, int amount)
{
	return SetBaseMaterial(player, material, Max(amount, GetBaseMaterial(player, material)));
}


/**
 Sets the minimum amount of base production that a player has.
 Does nothing if the player already has more than this amount.
 */
global func SetBaseProductionAtLeast(int player, id material, int amount)
{
	return SetBaseProduction(player, material, Max(amount, GetBaseMaterial(player, material)));
}

/* -- Best effort default homebase -- */

/**
 Best effort function for giving players their homebase material.
 Should be called after scenario initialization (because it relies
 on objects having been placed), and after
 the players were given knowledge (because it relies on the knowledge).
 */
global func GivePlayerHomebaseMaterial(int player)
{
	// Get at least the material to create these
	var essential_knowledge = [Sawmill, ClassicFoundry, ClassicWindmill];
	var material_list = {};
	for (var knowledge in essential_knowledge)
	{
		var index = 0;
		for (var component = knowledge->GetComponent(nil, index); !!component; component = knowledge->GetComponent(nil, ++index))
		{
			material_list[Format("%i", component)] += knowledge->GetComponent(component);
		}
	}
	
	// Update the home base material
	var index = 0;
	for (var material_name in GetProperties(material_list))
	{
		var material = GetDefinition(material_name);
		if (material)
		{
			// Set home base material: At least the minimum required amount,
			// but deduct the materials that the player already has
			var amount = Max(0, material_list[material_name] - ObjectCount(Find_ID(material), Find_Owner(player)));
			SetBaseMaterialAtLeast(player, material, amount);
			SetBaseProductionAtLeast(player, material, 1);
		}
	}
}
