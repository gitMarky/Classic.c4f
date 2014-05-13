/*
 * Tells the hammer how to get used by the attached tools function.
 * 
 * Author: Marky
 */

#appendto Library_Constructor

public func AttachedToolStartUse(object user)
{
	return ControlUseStart(user, user->GetX() -10 + 20*(user->GetDir()), user->GetY());
}

// Called by Control2Effect
func FxControlConstructionPreviewControl(object clonk, effect, int ctrl, int x, int y, int strength, bool repeat, bool release)
{
	if (ctrl != CON_Aim)
	{
		// CON_Use is accept
		if (ctrl == CON_Use || ctrl == CON_Throw)
			CreateConstructionSite(clonk, effect.structure, AbsX(effect.preview->GetX()), AbsY(effect.preview->GetY() + effect.preview.dimension_y/2), effect.preview.direction, effect.preview.stick_to);
		// movement is allowed
		else if (IsMovementControl(ctrl))
			return false;
		// Flipping
		// this is actually realized twice. Once as an Extra-Interaction in the clonk, and here. We don't want the Clonk to get any non-movement controls though, so we handle it here too.
		// (yes, this means that actionbar-hotkeys wont work for it. However clicking the button will.)
		else if (IsInteractionControl(ctrl))
		{
			if (release)
				effect.preview->Flip();
			return true;
		}

		// everything else declines
		RemoveEffect("ControlConstructionPreview", clonk, effect);
		return true;
	}
		
	effect.preview->Reposition(x, y);
	return true;
}