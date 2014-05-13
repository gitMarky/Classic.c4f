/*
 * Structures are always containers if the caller is inside of them!
 * 
 * Author: Marky
 */

#appendto Library_Structure

public func IsContainer(object caller)
{
	if (caller == nil) return false;
	return caller->Contained() == this;
}
