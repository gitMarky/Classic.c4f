/*
 * Attached tools need some hacks, because they are at a very different position than the actual user.
 * 
 * Author: Marky
 */

#appendto Shovel
#appendto Axe

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