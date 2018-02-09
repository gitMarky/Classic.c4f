#appendto Rule_StartingEquipment


private func OnClonkRecruitment(object crew, int player)
{
	if (GetCrew(player, 0) == crew)
	{
		crew->CreateContents(ClassicFlag);
		crew->CreateContents(Conkit);
	}

	_inherited(crew, player, ...);
}