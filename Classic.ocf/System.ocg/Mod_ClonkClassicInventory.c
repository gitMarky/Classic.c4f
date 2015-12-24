/*
 * Classic styled inventory:
 * 1 hand only, 3 items max.
 * 
 * Author: Marky
 */

#appendto ClassicClonk


private func HandObjects() { return 1; }
public func MaxContentsCount() { return 3; }

public func Collection2()
{
	_inherited(...);

	ObjectControlShiftInventory(nil); // selected old contents again
}

public func Ejection()
{
	_inherited(...);

	ObjectControlShiftInventory(nil); // selected old contents again
}
