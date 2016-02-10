#appendto Barrel

private func GetValueOf(string liquid) // 300 px of...
{
	// default value for the metal barrel is 16
	// default value of CR metal barrel is 8
	// just some provisional values, feel free to change them
	// for gameplay reasons
	if (liquid == "Water") return -8;     // total: 8
	if (liquid == "Lava") return -6;      // total: 10
	if (liquid == "DuroLava") return -6;  // total: 10
	if (liquid == "Acid") return -6;      // total: 10
	if (liquid == "Firefluid") return 10; // total: 26
	if (liquid == "Oil") return 9;        // total: 25
	return 0;
}
