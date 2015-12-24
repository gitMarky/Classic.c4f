/*
 * Additions to the array scripts
 *
 * Author: Marky
 */

#appendto ConstructionSite

local existing_site;

public func Set(id def, int dir, object stick, object existing_object)
{
	_inherited(def, dir, stick);

	existing_site = existing_object;
	
	if (existing_object != nil)
	{
		// create existing contents
		var i, cid, num;
		while (cid = existing_object->GetComponent(nil, i++))
		if ((num = existing_object->GetComponent(cid)) > 0)
			while (num--) CreateContents(cid);
			
		var dummy = CreateObject(Dummy, 0, 0, NO_OWNER);
		existing_object->Enter(dummy);
		//existing_site->SetGraphics();
		
		SetGraphics(nil, nil, 3, GFXOV_MODE_Object, nil, nil, existing_object);
		
		var y_offset = existing_object->GetDefBottom() - existing_object->GetY();
		
		SetObjDrawTransform(1000, 0, 0, 0, 1000, -1000 * y_offset, 3);
	}
	
	SetClrModulation(RGBa(255, 255, 255, 10), 2);
	
	ShowMissingComponents();
}

private func StartConstructing()
{
	if(!definition)
		return;
	if(!full_material)
		return;
	
	is_constructing = true;
	
	// find all objects on the bottom of the area that are not stuck
	var wdt = GetObjWidth();
	var hgt = GetObjHeight();
	var lying_around = FindObjects(Find_Or(Find_Category(C4D_Vehicle), Find_Category(C4D_Object), Find_Category(C4D_Living)),Find_InRect(-wdt/2 - 2, -hgt, wdt + 2, hgt + 12), Find_Not(Find_OCF(OCF_InFree)),Find_NoContainer());
	
	// create the construction, below surface constructions don't perform any checks.
	// uncancellable sites (for special game goals) are forced and don't do checks either
	var site;
	var checks = !definition->~IsBelowSurfaceConstruction() && !no_cancel;
/*	
	if (existing_site != nil)
	{
		var dummy = existing_site->Contained();
		if (dummy != nil)
		{
			existing_site->Exit();
			dummy->RemoveObject();
		}
		
		existing_site->SetGraphics();
		existing_site->SetCon(1);
		existing_site->SetPosition(GetX(), GetY());
		site = existing_site;
	}
*/	
	if(site == nil && !(site = CreateConstruction(definition, 0, 0, GetOwner(), 1, checks, checks)))
	{
		// spit out error message. This could happen if the landscape changed in the meantime
		// a little hack: the message would immediately vanish because this object is deleted. So, instead display the
		// message on one of the contents.
		if(Contents(0))
			CustomMessage("$TxtNoConstructionHere$", Contents(0), GetOwner(), nil,nil, RGB(255,0,0));
		Interact(nil, 1);
		return;
	}
	
	if (existing_site != nil)
	{
		var dummy = existing_site->Contained();
		if (dummy != nil)
		{
			existing_site->Exit();
			dummy->RemoveObject();
		}
		
		site->SetCon(Max(site->GetCon(), existing_site->GetCon()));
		existing_site->RemoveObject();
	}
	
	if(direction)
		site->SetDir(direction);
	// Inform about sticky building
	if (stick_to)
		site->CombineWith(stick_to);
	
	// Object provides custom construction effects?
	if (!site->~DoConstructionEffects(this))
	{
		// If not: Autoconstruct 2.0!
		Schedule(site, "DoCon(2)",1,50);
		Schedule(this,"RemoveObject()",1);
	}
	
	// clean up stuck objects
	for(var o in lying_around)
	{
		if (!o) continue;
		
		var x, y;
		var dif = 0;
		
		x = o->GetX();
		y = o->GetY();
		
		// move living creatures upwards till they stand on top.
		if(o->GetOCF() & OCF_Alive)
		{
			while(o->GetContact(-1, CNAT_Bottom))
			{
				// only up to 20 pixel
				if(dif > 20)
				{
					o->SetPosition(x,y);
					break;
				}
				
				dif++;
				o->SetPosition(x, y-dif);
			}
		}
		else {
			while(o->Stuck())
			{
				// only up to 20 pixel
				if(dif > 20)
				{
					o->SetPosition(x,y);
					break;
				}
				
				dif++;
				o->SetPosition(x, y-dif);
			}
		}
	}
}