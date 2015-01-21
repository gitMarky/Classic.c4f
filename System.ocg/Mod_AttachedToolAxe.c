/*
 * Tells the axe how to get used by the attached tools function.
 * 
 * Author: Marky
 */

#appendto Axe

public func AttachedToolStartUse(object user)
{
	if (!AttachedToolReady(user)) return;

	return ControlUseStart(user, user->GetX() -10 + 20*(user->GetDir()), user->GetY());
}

private func AttachedToolReady(object user)
{
	if (!user) return;
	var proc = user->GetProcedure();
	
	return proc == DFA_WALK || user->GetAction() == "Jump";
}

public func AttachedToolIsInUse(object user)
{
	if (!user) return false;
	return GetEffect("IntAxe", this)
	    || GetEffect("IntAxe", user)
		|| GetEffect("IntSplit", user)
		|| GetEffect("AxeStrikeStop", user);
}

public func AttachedToolCancelUse(object user)
{
	if (!user) return false;
	Reset(user);
	return true;
}

// somehow I managed to get a call where Contained() == nil
public func GetCarryTransform()
{
	var act = nil;
	
	if (Contained()) act = Contained()->GetAction();
	if(act != "Walk" && act != "Jump")
		return Trans_Mul(Trans_Translate(0,4500,0), Trans_Rotate(-90,0,1,0), Trans_Rotate(180,0,0,1) );

	return Trans_Rotate(90, 0, 1, 0);
}

public func GetUseIcon()
{
	return Icon_Chop;
}

