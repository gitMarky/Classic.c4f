/*
 * Tells the shovel how to get used by the attached tools function.
 * 
 * Author: Marky
 */

#appendto Shovel

public func AttachedToolStartUse(object user, bool release)
{
	if (!AttachedToolReady(user) || release) return;

	return user->ObjectControlDig(); //SetAction("Dig");
}

private func AttachedToolReady(object user)
{
	if (!user) return;
	if (user->Contained()) return;
	
	var proc = user->GetProcedure();
	
	return proc == DFA_WALK;
}
public func AttachedToolIsInUse(object user)
{
	if (!user) return false;
	return user->GetProcedure() == "DIG";
}

public func AttachedToolCancelUse(object user, bool release)
{
	if (!user || release) return false;
	
	var effect = GetEffect("IntDig", user);
	
	if (!effect || effect.digMaterialRequest)
	{
		user->SetAction("Walk");
		user->SetComDir(COMD_Stop);
	}
	else
		user->ObjectControlDig();

	return true;
}

public func GetUseIcon()
{
	return Icon_Dig;
}
