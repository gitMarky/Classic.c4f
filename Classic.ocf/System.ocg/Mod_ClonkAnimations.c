/*
 * Minor changes in the clonk animations:
 * - smoother hangling
 * - can dig material chunks on request
 *
 * Author: Marky
 */


#appendto Clonk_Animations


func FxIntHangleTimer(pTarget, effect, iTime)
{
	// (TODO: Instead of effect.is_moving we should be able
	// to query the current animation... maybe via a to-be-implemented
	// GetAnimationName() engine function.

	// If we are currently moving
	if(effect.is_moving)
	{
		var phase = 20;

		var var_speed = 30;
		var bas_speed = 50;

		var max_speed = 100;

		var inc_speed = 3;
		var dec_speed = 7;

		if(pTarget->GetComDir() == COMD_Stop || effect.request_stop == 1)
			effect.current_speed = BoundBy(effect.current_speed - dec_speed, 0, max_speed);
		else
			effect.current_speed = BoundBy(effect.current_speed + inc_speed, 0, max_speed);

		var iSpeed = effect.current_speed * (bas_speed + var_speed -Cos((iTime%(2*phase))*180/phase, var_speed))/max_speed;

		ActMap.Hangle.Speed = effect.hangle_speed*iSpeed/50;

		// Exec movement animation (TODO: Use Anim_Linear?)
		var position = GetAnimationPosition(effect.animation_id);
		position += (effect.hangle_speed*5/48*1000/phase);

		SetAnimationPosition(effect.animation_id, Anim_Const(position % GetAnimationLength("Hangle")));

		// Continue movement, if the clonk still has momentum
		if(GetComDir() == COMD_Stop && iSpeed>10)
		{
			// Make it stop after the current movement
			effect.request_stop = 1;

			if(GetDir())
				SetComDir(COMD_Right);
			else
				SetComDir(COMD_Left);
		}
		// Stop movement if the clonk has lost his momentum
		else if(iSpeed <= 10 && (GetComDir() == COMD_Stop || effect.request_stop))
		{
			effect.request_stop = 0;
			SetComDir(COMD_Stop);

			// and remeber the pose (front or back)
			if(GetAnimationPosition(effect.animation_id) > 2500 && GetAnimationPosition(effect.animation_id) < 7500)
				effect.facing_front = 1;
			else
				effect.facing_front = 0;

			// Change to HangleStand animation
			var begin = 4000*effect.facing_front;
			var end = 2000+begin;
			effect.animation_id = PlayAnimation("HangleStand", 5, Anim_Linear(begin, begin, end, 100, ANIM_Loop), Anim_Linear(0, 0, 1000, 5, ANIM_Remove));
			effect.is_moving = 0;
		}
	}
	else
	{
		// We are currently not moving
		if(GetComDir() != COMD_Stop)
		{
			// Switch to move
			effect.is_moving = 1;
			// start with frame 100 or from the back hanging pose frame 600
			var begin = 10*(100 + 500*effect.facing_front);
			effect.animation_id = PlayAnimation("Hangle", 5, Anim_Const(begin), Anim_Linear(0, 0, 1000, 5, ANIM_Remove));
		}
	}
}


// Removes diggable materials
func FxIntDigTimer(pTarget, effect, iTime)
{
	if (iTime % 36 == 0)
	{
		Sound("Dig?");
	}
	if ((iTime-18) % 36 == 0 ||  iTime > 35)
	{
//		var noDig = 1;
//		for (var pShovel in FindObjects(Find_ID(Shovel), Find_Container(this)))
//			if(pShovel->IsDigging()) noDig = 0;
//
//		if (noDig)
//		if (!FindObject(Find_ID(Shovel), Find_Container(this)))
//		{
//			SetAction("Walk");
//			SetComDir(COMD_Stop);
//			return -1;
//		}
	}
	if (!effect.digMaterialRequest)
	{
		var chunks = FindObjects(Find_Func("IsRemoveableMaterialChunk"), Find_Distance(12));

		for(var obj in chunks) obj->RemoveObject();
	}
}

