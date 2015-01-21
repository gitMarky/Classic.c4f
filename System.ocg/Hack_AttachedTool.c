/*
 * Appending in definitions is not possible anymore, so I hope that this hack will work...
 *
 * Author: Marky
 */
 
#appendto Library_AttachedTool
#appendto Axe
#appendto Shovel

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