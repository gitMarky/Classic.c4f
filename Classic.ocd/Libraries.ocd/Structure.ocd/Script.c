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

protected func Incineration(int by_player)
{
	SetGraphics("Destroyed");
	
	if (!GetEffect("IntStopBurnDecay", this))
	{
		AddEffect("IntStopBurnDecay", this, 1, 1, this);
	}
	
	return _inherited(...);
}

protected func FxIntStopBurnDecayTimer(object target, proplist effect, int timer)
{
	if (target->GetCon() <= 30)
	{
		target->Extinguish();
		target->StructureReconstruct();
		return FX_Execute_Kill;
	}
	
	return FX_OK;
}

protected func StructureReconstruct()
{
	var site;
	site = CreateObjectAbove(ConstructionSite, 0, GetDefBottom()-GetY(), GetOwner());
	
	// Randomize sign rotation
	site->SetProperty("MeshTransformation", Trans_Mul(Trans_Rotate(RandomX(-30, 30), 0, 1, 0), Trans_Rotate(RandomX(-10, 10), 1, 0, 0)));
	site->PlayAnimation("LeftToRight", 1, Anim_Const(RandomX(0, GetAnimationLength("LeftToRight"))), Anim_Const(500));
	
	site->Set(GetID(), 0, nil, this);
	site->SetPosition(GetX(), GetDefBottom() - (site->GetDefBottom() - site->GetY()) - 2);
}