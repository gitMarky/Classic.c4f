/**
	Structure Library
	Basic library for structures, handles:
	* Damage
	* Energy bar if rule active
	
	@author Marky
*/

local IsDeytroyed = false;
local IsDisabled = false;

func Initialize()
{
	if (FindObject(Find_ID(Rule_StructureHPBars)))
	{
		if (this.HitPoints != nil)
			AddEnergyBar();
	}
	return _inherited(...);
}

public func Damage(int change, int cause, int cause_plr)
{
	// Only do stuff if the object has the HitPoints property.
	if (this)
	{
		if (this.HitPoints != nil && GetDamage() >= this.HitPoints)
		{		
			StructureDestroyed();
		}
		
		if (this.BlastIncinerate != nil && GetDamage() >= this.BlastIncinerate
		&& (cause & FX_Call_DmgBlast || cause & FX_Call_EngBlast))
		{
			StructureIncinerate();
		}
	}
	return _inherited(change, cause, cause_plr);
}

// This object is a structure.
public func IsStructure() { return true; }

protected func StructureIncinerate()
{
	if (!OnFire()) Incinerate();
}

protected func StructureDestroyed()
{
	if (!this.IsDestroyed)
	{
		this.IsDestroyed = true;
		this->~OnStructureDestroyed();
	}
}

protected func StructureDisable()
{
	this.IsDisabled = true;
	SetObjectLayer(this);
}

protected func StructureEnable()
{
	this.IsDisabled = false;
	SetObjectLayer(nil);
}