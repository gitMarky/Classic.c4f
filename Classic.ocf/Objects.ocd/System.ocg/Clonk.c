#appendto Clonk

public func GetDiggingAnimation()
{
	var dig_effect = GetEffect("IntDig", this);
	if (dig_effect)
		return dig_effect.animation;
	return;
}