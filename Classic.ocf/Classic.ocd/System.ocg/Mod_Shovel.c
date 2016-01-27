#appendto Shovel


func GetModifiedDigSpeed(object clonk, int speed)
{
//	var iAnimation = GetEffect("IntDig", clonk).var1;
//	var iPosition = clonk->GetAnimationPosition(iAnimation)*180/clonk->GetAnimationLength("Dig");
//	speed = speed*(Cos(iPosition-45, 50)**2)/2500;

	return 3 * speed / 4;
}
