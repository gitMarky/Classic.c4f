#appendto Clonk

private func Recruitment(int player)
{
	// For better ambience
	SetLightColor(RGB(180, 180, 150));
	
	// Starting equipment
	EnsureHasContents(Shovel);
	EnsureHasContents(Axe);

	return _inherited(player, ...);
}
