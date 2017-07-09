/*
 * Bird
 *
 * With improved behavior.
 *
 * Author: Marky, original found in Clonk Rage
 */

#include Library_AnimalControl
#include Library_AnimalFighting
#include Library_AnimalShelter
#include Library_AnimalReproduction

private func AnimalReproductionRate(){    return 2000;}
public func AnimalInitialAction(){    return "Fly";}


/* Initialisierung */

private func FxIntAnimalTurnTimer(object target, proplist effect)
{
    if (target != this) return;

    AvoidHittingLandscape();

    // Flying backwards? Turn around!
    if (GetXDir()>0 && GetDir() == DIR_Left)  return AnimalTurnRight();
    if (GetXDir()<0 && GetDir() == DIR_Right) return AnimalTurnLeft();

}

private func FxIntAnimalActivityStatus( object target, proplist effect)
{
    if (target != this) return;

    effect.ignoreCalls = false;

    // Dead birds don't do much...
    if (!GetAlive())
    {
        effect.ignoreCalls = true;
        return;
    }

    // Make a sound :)
    if (!Random(25)) DoTwitter();

}

private func FxIntAnimalActivityMovement( object target, proplist effect)
{
    if (target != this) return;

    // let bird take further movement commands if he is close to his actual target,
    // but only if he has no second command (such as call to nest, or second move target)
    // this ensures smooth movement :)
    if (GetCommand() != "Wait" && GetCommand() != nil)
    {
        if (GetCommand() == "MoveTo" && GetCommand(0, 1) == nil)
        {
            if (Distance(GetX(), GetY(), GetCommand(2), GetCommand(3)) > 200)
                return;
        }
        else
        {
            return;
        }
    }

    if (GetAction() == "Sit")
    {
        if (Random(2))
            SetDir(DIR_Left);
        else
            SetDir(DIR_Right);

        return;
    }

    // Do nothing
    //if (Random(2) || GetAction() != "Fly") return;
    if (GetAction() != "Fly") return;

    var x = RandomX(20, LandscapeWidth()-20);
    var ref_y = GetFeasableHeight(x);

    if (ref_y == nil)
    {
            // Fly down or up
            if (Random(2))
                SetComDir(GetComDir()|COMD_Down);
            else
                SetComDir(GetComDir()|COMD_Up);

            return;
    }

    var y = RandomX(ref_y[0], ref_y[1]);
    AppendCommand("MoveTo", nil, x, y);

//
//    // Fly down or up
//    if (Random(2))
//        SetComDir(GetComDir()|COMD_Down);
//    else
//        SetComDir(GetComDir()|COMD_Up);
//
//    // Do nothing again
//    if (!Random(4)) return;
//
//    // Turn around
//    if (Random(2))
//        AnimalTurnRight();
//    else
//        AnimalTurnLeft();
}

private func FxIntAnimalActivityFight( object target, proplist effect)
{
    if (target != this) return;

}
private func FxIntAnimalActivityShelter( object target, proplist effect)
{
    if (target != this) return;

    // remove current shelter
    if (effect.shelter)
    {
          // if the nest is not hanging on a tree anymore
          // if the nest is flooded
          // if the nest is burning
          if (effect.shelter->GetAction() == "Decay"
           || GBackSemiSolid(effect.shelter->GetX()-GetX(), effect.shelter->GetY()-GetY())
           || effect.shelter->OnFire())
          {
                  effect.shelter = nil;
          }
    }

    // No nest? Build one!
    if (!effect.shelter)
    {
        var pTree = BirdFindTree(effect);

         if (pTree)
         {
             if (!GetEffect("IntBirdNestMarker", pTree))
                   AddEffect("IntBirdNestMarker", pTree, 1, 0, this);

            var id = pTree->GetID();

            var nest_x = pTree->GetX()+id->GetDefOffset()+Random(id->GetDefWidth()-20)+10;
             var nest_y = pTree->GetY()+id->GetDefOffset(1)+Random(id->GetDefHeight()-id->GetDefFireTop()-20)+10;

             nest_x = BoundBy( nest_x, Abs(BirdNest->GetDefOffset()) + 5, LandscapeWidth() - BirdNest->GetDefWidth() - BirdNest->GetDefOffset());

            SetCommand( "Call", this, pTree, 0, nil, "BirdStartBuildNest");
            AddCommand( "MoveTo", nil, nest_x, nest_y);
         }

        return;
    }
    else
    {
        if (effect.shelter->GetCon() < 100) BirdFlyToNest(effect); // builds the rest
    }

    if (IsNight()) // go to sleep
    {
        BirdFlyToNest(effect);

        if (Contained() && effect.shelter == Contained() && GetActTime() > 100 && GetAction() != "Sleep")
        {
            SetAction("Sleep");
        }
    }
    else // leave the nest!
    {
        if (Contained() && effect.shelter && Contained() == effect.shelter)
        {
            Exit();
        }
    }
}

private func AnimalCanTurn(){ return !Stuck() && GetAction() == "Fly"; }
private func AnimalOnTurnLeft()
{
    SetAction("Turn");
}
private func AnimalOnTurnRight()
{
    SetAction("Turn");
}

private func AnimalReproductionCondition()
{
    var effect = AnimalGetActivityEffect();
    if (!effect) return false;
    if (!effect.shelter) return false;
    if (Contained() != effect.shelter) return false;
    return true;
}

private func AnimalReproductionCustom()
{
    if (Random(AnimalReproductionRate())) return true;
    var effect = AnimalGetActivityEffect();
    if (!effect) return true;

    var egg = effect.shelter->CreateContents(BirdEgg);
    egg->Fertilize(GetID(), 2000);

    return true;
}

private func FlyTryAttack()
{
      // Only while flying
      if (GetAction() != "Fly") return;

      // Find a blimp or balloon
      if (!this.pokeTarget)
      {
          this.pokeTarget = FindObject(Find_Func("IsPokeableByBird", this));
      }
      if (!this.pokeTarget) return;

      // Poke it!
      this.pokeTarget->~GetPoked(this);
      SetAction("Attack");
      DoTwitter();
}

private func FlyAvoidDanger()
{
    // Avoid liquids and burning objects
    if (InLiquid() || GBackLiquid(GetXDir()*2, GetYDir()*2) || GBackLiquid(GetXDir()*3, GetYDir()*3) || FindObject(Find_InRect(-20 + GetXDir() * 2, -20 + GetYDir() * 2, 40, 40), Find_OCF(OCF_OnFire)))
        SetComDir(COMD_Up);
}


/* Hitting the landscape... */

protected func ContactLeft()
{
    return AnimalTurnRight();
}

protected func ContactRight()
{
    return AnimalTurnLeft();
}

protected func ContactTop()
{
    return SetComDir(COMD_Down);
}

protected func ContactBottom()
{
    return SetComDir(COMD_Up);
}

protected func Entrance()
{
    if (GetAlive()) SetAction("Sit");
}

protected func Departure()
{
    if (GetAlive()) SetAction("Fly");
}

protected func Death()
{
    ChangeDef(DeadBird);
    _inherited(...);
}

func DoTwitter()
{
    Sound("Animals::Bird::Raven?");
}

/* Animations */

local ActMap = {
Fly = {
    Prototype = Action,
    Name = "Fly",
    Procedure = DFA_FLOAT,
    Speed = 200,
    Accel = 16,
    Decel = 16,
    Directions = 2,
    FlipDir = 1,
    Length = 20,
    Delay = 1,
    X = 0,
    Y = 0,
    Wdt = 14,
    Hgt = 12,
    NextAction = "Fly",
    TurnAction = "Turn",
    StartCall = "FlyTryAttack",
    PhaseCall = "FlyAvoidDanger",
},

Turn = {
    Prototype = Action,
    Name = "Turn",
    Procedure = DFA_FLOAT,
    Speed = 100,
    Accel = 16,
    Decel = 32,
    Directions = 2,
    FlipDir = 1,
    Length = 20,
    Delay = 1,
    X = 0,
    Y = 12,
    Wdt = 14,
    Hgt = 12,
    NextAction = "Fly",
},

Attack = {
    Prototype = Action,
    Name = "Attack",
    Procedure = DFA_FLOAT,
    Directions = 2,
    FlipDir = 1,
    Length = 20,
    Delay = 1,
    X = 0,
    Y = 24,
    Wdt = 14,
    Hgt = 12,
    NextAction = "Fly",
},

Tumble = {
    Prototype = Action,
    Name = "Tumble",
    Procedure = DFA_NONE,
    Directions = 2,
    FlipDir = 1,
    Length = 20,
    Delay = 1,
    X = 0,
    Y = 36,
    Wdt = 14,
    Hgt = 12,
    NextAction = "Fly",
    ObjectDisabled = 1,
    InLiquidAction = "Fly",
},

Eat = {
    Prototype = Action,
    Name = "Eat",
    Procedure = DFA_FLOAT,
    Directions = 2,
    FlipDir = 1,
    Length = 20,
    Delay = 2,
    X = 0,
    Y = 24,
    Wdt = 14,
    Hgt = 12,
    NextAction = "Fly",
    //EndCall = "Eating",
},

BuildNest = {
    Prototype = Action,
    Name = "BuildNest",
    Procedure = DFA_FLOAT,
    Directions = 2,
    FlipDir = 1,
    Length = 20,
    Delay = 2,
    X = 0,
    Y = 24,
    Wdt = 14,
    Hgt = 12,
    NextAction = "BuildNest",
    PhaseCall = "BirdDoBuildNest",
},

Sit = {
    Prototype = Action,
    Name = "Sit",
    Procedure = DFA_FLOAT,
    Directions = 2,
    FlipDir = 1,
    Length = 1,
    Delay = 40,
    X = 96,
    Y = 48,
    Wdt = 14,
    Hgt = 12,
    OffY = 2,
    NextAction = "Sit",
},

Sleep = {
    Prototype = Action,
    Name = "Sleep",
    Procedure = DFA_FLOAT,
    Directions = 2,
    FlipDir = 1,
    Length = 1,
    Delay = 40,
    X = 96,
    Y = 48,
    Wdt = 14,
    Hgt = 12,
    OffY = 3,
    NextAction = "Sleep",
},
};

local Name = "$Name$";
local Description = "$Description$";
local MaxEnergy = 40000;
local MaxBreath = 720; // Bird can breathe for 20 seconds under water.
local NoBurnDecay = 1;
local ContactIncinerate = 1;
local ContactCalls = true;
local Collectible = true;
local BorderBound = 7;



private func BirdFindTree(proplist effect)
{
    if (effect.tree)
    {
        if (!(effect.tree->IsStanding()))
            effect.tree = nil;
        else
            return effect.tree;
    }

    var goodTrees = CreateArray();
    var distance = 500;

    var obj, pTree;
    // Find a suitable tree
    for (obj in FindObjects(Find_Func("IsTree"), Find_Distance(distance),
               Find_Not(Find_OCF(OCF_OnFire)), Find_Func("IsStanding")))
    {
        if (obj->GetCon() < 100) continue;
        // not flooded
        if (GBackSemiSolid(obj->GetX()-GetX(), obj->GetY()-GetY())) continue;
        if (FindObject(Find_ID(BirdNest), Find_ActionTarget(obj))) continue;
        if (GetEffect("IntBirdNestMarker", obj)) continue;

        PushBack(goodTrees, obj);
    }

    var target;
    for (target in goodTrees)
    {
        var dist = ObjectDistance(target);
        if (dist < distance)
        {
            pTree = target;
            distance = dist;
        }
    }
    // save for future use
    effect.tree = target;
    return target;
}


public func BirdStartBuildNest(pThis, pTree)
{
      var effect = AnimalGetActivityEffect();
      if (!pTree || effect == nil) return;
      if (pTree->GetX()<GetX())
          SetDir(DIR_Left);
      else
          SetDir(DIR_Right);

      effect.shelter = CreateConstruction(BirdNest, (-GetID()->GetDefWidth()+2*GetID()->GetDefWidth()*GetDir())/2, +5, -1, 30);

      effect.shelter.pTree = pTree;
      effect.shelter->SetAction("Be", pTree);

      if (GetEffect("IntBirdNestMarker", pTree))
          RemoveEffect("IntBirdNestMarker", pTree);
}

protected func BirdPrepareBuildNest()
{
      SetAction("BuildNest");
      SetComDir(COMD_Stop);
      SetXDir(0);
      SetYDir(0);
}

protected func BirdDoBuildNest()
{
      var effect = AnimalGetActivityEffect();
      if (!effect || !effect.shelter || effect.shelter->OnFire() || ObjectDistance(effect.shelter) > GetID()->GetDefWidth())
      { SetAction("Fly");  return; }

      if (GetPhase()%2) return;

      effect.shelter->DoCon(1);
      if (effect.shelter->GetCon()>=100)
      {
               SetAction("Fly");
               BirdFlyToNest(effect);
      }
}



private func BirdFlyToNest(proplist effect)
{
    if (!effect.shelter) return;

    if (effect.shelter->GetCon() < 100)
    {
        // continue building the nest
        SetCommand("Call", this, 0, 0, nil, "BirdPrepareBuildNest");
        AddCommand("MoveTo", effect.shelter);
    }
    else
    {
        // Fly to the nest and enter it
        SetCommand("Call", this, 0, 0, nil, "BirdEnterNest");
        AddCommand("MoveTo", effect.shelter);
    }
}


protected func BirdEnterNest()
{
      var effect = AnimalGetActivityEffect();
      if (!effect || !effect.shelter) return;

      ForceEnter(effect.shelter);
}


public func AvoidHittingLandscape()
{
    if (Contained()) return;

    var dist = GetID()->GetDefHeight()*2;

    var d_top = 0;
    var d_down = 0;
    var d_top_dir = 0;
    var d_down_dir = 0;

    var tolerance_y = 20;
    //var ydir_max = 10;
    var ydir_change = 1;

    var dx = GetXDir()*15;
    var dist2 = dist + 10*BoundBy(Abs(GetXDir())-3, 0, 10);
    var d_min = 40;

    // calculate distance to landscape right below the bird
    for (d_top = Abs(GetDefOffset(1)); d_top < dist; d_top++)
    {
        if (GBackSemiSolid(0,-d_top)) break;
    }

    for (d_down = GetDefOffset(1) + GetID()->GetDefHeight(); d_down < dist; d_down++)
    {
        if (GBackSemiSolid(0, d_down)) break;
    }

    // calculate distance to landscape in movement direction
    for (d_top_dir = Abs(GetDefOffset(1)); d_top_dir < dist2; d_top_dir++)
    {
        if (GBackSemiSolid(dx,-d_top_dir)) break;
    }

    for (d_down_dir = GetDefOffset(1) + GetID()->GetDefHeight(); d_down_dir < dist2; d_down_dir++)
    {
        if (GBackSemiSolid(dx, d_down_dir)) break;
    }

    // adjust height

    var target_y = GetY()+(d_down-d_top)/2 +BoundBy(+d_min-d_top, 0, d_min)-BoundBy(+d_min-d_down, 0, d_min);
    var target_y_dir = GetY()+(d_down_dir-d_top_dir)/2 +BoundBy(+d_min-d_top_dir, 0, d_min)-BoundBy(+d_min-d_down_dir, 0, d_min);

    var w1, w2;

    if (GetYDir() <= 3)
    {
        w1 = 2;
        w2 = 1;
    }
    else
    {
        w1 = 1;
        w2 = 2;
    }
    target_y = (w1*target_y + w2*target_y_dir)/(w1+w2);

    if (GetY() < target_y - tolerance_y)
    {
        SetYDir(BoundBy(GetYDir()+ydir_change, -7, 7));
    }

    if (GetY() > target_y + tolerance_y)
    {
        SetYDir(BoundBy(GetYDir()-ydir_change, -7, 7));
    }
}

private func GetFeasableHeight(int x)
{
    var height = GetY();

    var safe_distance = GetID()->GetDefHeight() * 2;

    var found_starting_point = false;

    var top_range, bottom_range;

    // first look for a good point upwards!
    while ( height > safe_distance && !found_starting_point)
    {
        height -= 10;

        if (GBackSemiSolid(x-GetX(), height-GetY())) continue; // actually free where we move
        if (GBackSemiSolid(x-GetX(), height-GetY()+safe_distance)) continue; // keep safe distance to bottom

        if (GetPathLength(GetX(), GetY(), x, height) != nil) // and we can plan to this point!!
            found_starting_point = true;
    }

    if (found_starting_point)
    {
        bottom_range = height;

        while ( height > 0 && !GBackSemiSolid(x-GetX(), height-GetY()))
        {
            height -= 10;
        }

        top_range = height + safe_distance;

        return [top_range, bottom_range];
    }


    // now look for a good point downwards!
    height = GetY();
    while ( height < LandscapeHeight()-safe_distance && !found_starting_point)
    {
        height += 10;

        if (GBackSemiSolid(x-GetX(), height-GetY())) continue; // actually free where we move
        if (GBackSemiSolid(x-GetX(), height-GetY()-safe_distance)) continue; // keep safe distance to top

        if (GetPathLength(GetX(), GetY(), x, height) != nil) // and we can plan to this point!!
            found_starting_point = true;
    }

    if (found_starting_point)
    {
        top_range = height;

        while ( height < LandscapeHeight() && !GBackSemiSolid(x-GetX(), height-GetY()))
        {
            height += 10;
        }

        bottom_range = height - safe_distance;

        return [top_range, bottom_range];
    }

    return nil;
}
