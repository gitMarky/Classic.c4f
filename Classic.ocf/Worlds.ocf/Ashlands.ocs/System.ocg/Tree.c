#appendto Library_ChoppableTree

local dead = false;

func StartAnimation()
{
	if (GetAction() == "Chopped") return;
	_inherited();
}

// Prevent tree movement
func SetBurned()
{
	dead = true;
	SetGraphics("Burned");
	SetAction("Chopped");
}

func IsDeadTree(){ return dead; }