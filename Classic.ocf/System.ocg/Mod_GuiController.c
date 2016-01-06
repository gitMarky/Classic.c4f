/*
 * Adjusted interaction queue
 * 
 * Author: Marky
 */

#appendto GUI_Controller

/*
// takes care of displaying the interactions
public func FxIntSearchInteractionObjectsTimer(object target, effect, int time)
{

	// find vehicles & structures & script interactables
	var startAt = effect.startAt;
	var i = startAt;
	
	//var hotkey = i+1-target->HandObjects();
	var hotkey = i+1;
	
	// Get custom interactions from the clonk
	// extra interactions are an array of proplists. proplists have to contain at least a function pointer "f", a description "desc" and an "icon" definition/object. Optional "front"-boolean for sorting in before/after other interactions.
	var extra_interactions = target->~GetExtraInteractions()??[]; // if not present, just use []. Less error prone than having multiple if(!foo).
	// we could sort the interactions, but there usually will only be like 1-3. Not really worth it.
	
	// Add buttons:
	
	// all except structures only if outside
	//if(!target->Contained())
	//{
	var house = target->Contained();
	
		if(!house)
		// add extra-interactions Priority 0
		for(var interaction in extra_interactions)
			if(interaction.Priority == 0)
				ActionButton(target, i++, interaction.Object, ACTIONTYPE_EXTRA, hotkey++, nil, interaction);
	
		// add interactables (script interface)
		var interactables = FindObjects(Find_AtPoint(target->GetX()-GetX(),target->GetY()-GetY()),Find_Func("IsInteractable",target) /*,Find_NoContainer()*//*, Find_Layer(target->GetObjectLayer()));
		var j, icnt;
		for(var interactable in interactables)
		{
			if (house && interactable != house) continue;
			if (!house && interactable->Contained()) continue;
			
			icnt = interactable->~GetInteractionCount();
			if(!icnt)
				icnt = 1;

			for(j=0; j < icnt; j++)
			{
				ActionButton(target,i++,interactable,ACTIONTYPE_SCRIPT,hotkey++, j);
			}
		}
		
		if(!house)
		// add extra-interactions Priority 1
		for(var interaction in extra_interactions)
			if(interaction.Priority == 1)
				ActionButton(target, i++, interaction.Object, ACTIONTYPE_EXTRA, hotkey++, nil, interaction);
		
		// add vehicles
		var vehicles = FindObjects(Find_AtPoint(target->GetX()-GetX(),target->GetY()-GetY()),Find_OCF(OCF_Grab),Find_NoContainer(), Find_Layer(target->GetObjectLayer()));
		if(!house)
		for(var vehicle in vehicles)
		{
			ActionButton(target,i++,vehicle,ACTIONTYPE_VEHICLE,hotkey++);
		}
		
		if(!house)
		// add extra-interactions Priority 2
		for(var interaction in extra_interactions)
			if(interaction.Priority == 2)
				ActionButton(target, i++, interaction.Object, ACTIONTYPE_EXTRA, hotkey++, nil, interaction);
	//}

	// add structures
	var structures = FindObjects(Find_AtPoint(target->GetX()-GetX(),target->GetY()-GetY()),Find_OCF(OCF_Entrance),Find_NoContainer(), Find_Layer(target->GetObjectLayer()));
	for(var structure in structures)
	{
		ActionButton(target,i++,structure,ACTIONTYPE_STRUCTURE,hotkey++);
	}
	
	// add extra-interactions after everything
	for(var interaction in extra_interactions)
		if(interaction.Priority == nil || interaction.Priority > 2)
			ActionButton(target, i++, interaction.Object, ACTIONTYPE_EXTRA, hotkey++, nil, interaction);
	
	ClearActionButtons(i);
	
	return;
}
*/