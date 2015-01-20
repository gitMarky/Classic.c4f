/*
 * Attached tools need some hacks, because they are at a very different position than the actual user.
 * 
 * Author: Marky
 */

#appendto Shovel
#appendto Axe

/**
 Marks the object as an attachable tool that can be used by the clonk.
 */
public func IsAttachableTool()
{
	return true;
}

public func Contained()
{
	var container = _inherited(...);
	if (container && container->GetID() == Dummy) return container.clonk;
	return container;
}

//public func GetX()
//{
//	var container = Contained();
//	if (container) return container->GetX();
//	return _inherited(...);
//}
//
//public func GetY()
//{
//	var container = Contained();
//	if (container) return container->GetY();
//	return _inherited(...);
//}

local Name="$Name$";
local Description="$Description$";

