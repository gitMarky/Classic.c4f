#appendto Barrel

private func GetValueOf(string szMaterial) // 300 px of...
{
	// default value for the metal barrel is 16
	// default value of CR metal barrel is 8
	// just some provisional values, feel free to change them
	// for gameplay reasons
	if (szMaterial == "Water") return -8;     // total: 8
	if (szMaterial == "Lava") return -6;      // total: 10
	if (szMaterial == "DuroLava") return -6;  // total: 10
	if (szMaterial == "Acid") return -6;      // total: 10
	if (szMaterial == "Firefluid") return 10; // total: 26
	if (szMaterial == "Oil") return 9;        // total: 25
	return 0;
}
