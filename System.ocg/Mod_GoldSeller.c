/*
 * Gold seller sells gold contents too.
 * 
 * Author: Marky
 */

#appendto Library_GoldSeller


func FxAutoSellValuablesTimer(_, effect, time)
{
	var owner = GetOwner();
	
	if(!GetPlayerName(owner))
	{
		effect.Interval = LIBRARY_GOLDSELLER_MaxTimer;
		return 1;
	}
	
	var objs = [];
	
	for(var obj in FindObjects(Find_Distance(AutoSellValuablesRadius()), Find_Or(Find_NoContainer(), Find_Container(this)), Find_Func("IsValuable")))
	{
		if(obj->Stuck()) continue;
		if(!IsAllied(owner, obj->GetController())) continue;
		objs[GetLength(objs)] = obj;
	} 
	
	if(!GetLength(objs))
	{
		effect.Interval = LIBRARY_GOLDSELLER_MaxTimer;
		return 1;
	}
	
	var comp = objs[0];
	var to_remove = [];
	
	for(var obj in objs)
	{
		var d = ObjectDistance(obj, comp);
//		if(d > 50) continue; // this was already checked in the max distance stuff above
		to_remove[GetLength(to_remove)] = obj;
	}
	
	AutoSellObjects(to_remove);
	
	effect.Interval = BoundBy(effect.Interval - Random(LIBRARY_GOLDSELLER_TimerStep), LIBRARY_GOLDSELLER_MinTimer, LIBRARY_GOLDSELLER_MaxTimer);
	return 1;
}

protected func AutoSellObjects(array to_remove)
{
	if (!to_remove || GetLength(to_remove) == 0) return;
	var comp = to_remove[0];
	
	// assert: at least one object in to_remove
	var value = 0;
	var fm = CreateObject(FloatingMessage, comp->GetX() - GetX(), comp->GetY() - GetY(), NO_OWNER);
	fm->SetColor(250, 200, 50);
	fm->FadeOut(2, 10);
	fm->SetSpeed(0, -5);
	
	var dust_particles =
	{
		Prototype = Particles_Dust(),
		Size = PV_KeyFrames(0, 0, 0, 100, 10, 1000, 0),
		Alpha = PV_KeyFrames(0, 0, 255, 750, 255, 1000, 0),
		R = 200,
		G = 125,
		B = 125,
	};
	
	for(var valuable in to_remove)
	{
		if(valuable->~QueryOnSell(valuable->GetController())) continue;
		
		DoWealth(valuable->GetController(), valuable->GetValue());
		
		value += valuable->GetValue();
		
		CreateParticle("Flash", valuable->GetX() - GetX(), valuable->GetY() - GetY(), 0, 0, 8, { Prototype = Particles_Flash(), Size = 2 * Max(5, Max(valuable->GetDefWidth(), valuable->GetDefHeight())) });
		CreateParticle("Dust", valuable->GetX() - GetX(), valuable->GetY() - GetY(), PV_Random(-10, 10), PV_Random(-10, 10), PV_Random(18, 36), dust_particles, 10);
		valuable->RemoveObject();
	}
	
	fm->SetMessage(Format("%d</c>{{Icon_Coins}}", value));
	Sound("Cash");
}
