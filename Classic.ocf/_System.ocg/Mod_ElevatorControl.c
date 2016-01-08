/*
 * Modified elevator control library
 * 
 * Author: Marky
 */

#appendto Library_ElevatorControl


func ControlLeft(object clonk)
{
	if (GetEffect("ElevatorControl", this)) return Control2Elevator(CON_Left, clonk);
	return _inherited(clonk);
}
func ControlRight(object clonk)
{
	if (GetEffect("ElevatorControl", this)) return Control2Elevator(CON_Right, clonk);
	return _inherited(clonk);
}
func ControlDownSingle(object clonk)
{
	if (GetEffect("ElevatorControl", this)) return Control2Elevator(CON_DownSingle, clonk);
	return _inherited(clonk);
}


func Control2Elevator(int control, object clonk)
{
	var effect = GetEffect("ElevatorControl", this);
	
	// vehicles have to get out again...
	if ((control == CON_Left || control == CON_Right) && effect.case->GetYDir() == 0) return false;
	if (control == CON_DownSingle && GetXDir() != 0 && GetYDir() != 0) return false;
	
	if (control == CON_Up) effect.case->ControlUp(clonk);
	if (control == CON_Down) effect.case->ControlDown(clonk);
	if (control == CON_DownSingle) effect.case->ControlDownSingle(clonk);
	if (control == CON_Left) effect.case->ControlLeft(clonk);
	if (control == CON_Right) effect.case->ControlRight(clonk);

	effect.controlled = control;
}