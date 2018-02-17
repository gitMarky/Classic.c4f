/**
	Ambience sounds
	
	Use this object to play various ambience sounds.
	
	@author Marky
*/

local Name = "$Name$";
local Description = "$Description$";
local Visibility = VIS_Editor;

private func Construction()
{
	CreateEffect(FxAmbience, 1, 30);
}

local FxAmbience = new Effect
{
	Construction = func()
	{
		this.Chance = 13;
		this.Condition = nil;
		this.SoundName = nil;
		this.SoundOpts = nil;
		this.Wait = 0;
	},

	Timer = func(int time)
	{
		if (time < this.Wait || !this.SoundName)
			return FX_OK;
	
		// Condition for making the sound must be fulfilled
		if (!this.Condition || this.Target->Call(this.Condition, this))
		{
			if (Random(100) < this.Chance)
			{
				this.Target->Sound(this.SoundName, this.SoundOpts);
			}
		}
		return FX_OK;
	},
};


public func SetChance(int chance)
{
	var fx = GetEffect("FxAmbience", this);
	if (fx)
	{
		fx.Chance = chance;
	}
	return this;
}


public func SetSound(string name)
{
	var fx = GetEffect("FxAmbience", this);
	if (fx)
	{
		fx.SoundName = name;
	}
	return this;
}


public func SetOptions(proplist opts)
{
	var fx = GetEffect("FxAmbience", this);
	if (fx)
	{
		fx.SoundOptions = opts;
	}
	return this;
}


public func SetIcon(id icon)
{
	SetGraphics(nil, icon, 1, GFXOV_MODE_IngamePicture);
	SetObjDrawTransform(1000, 0, GetDefWidth() * 300, 0, 1000, GetDefHeight() * 200, 1);
	return this;
}


public func SetInterval(int interval)
{
	var fx = GetEffect("FxAmbience", this);
	if (fx)
	{
		fx.Interval = interval;
	}
	return this;
}


public func SetCondition(condition)
{
	var fx = GetEffect("FxAmbience", this);
	if (fx)
	{
		fx.Condition = condition;
	}
	return this;
}


public func Wait(int frames)
{
	var fx = GetEffect("FxAmbience", this);
	if (fx)
	{
		fx.Time = 0;
		fx.Wait = frames;
	}
	return this;
}
