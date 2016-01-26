#appendto Bird

func Construction()
{
	_inherited(...);
	
	var dark = RandomX(100, 200);
	SetClrModulation(RGB(dark / 2, dark, dark));
}
