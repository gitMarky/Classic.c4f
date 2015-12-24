/*
 * The classic AddMenuItem cannot render icons for 3d graphics.
 * 
 * This script uses a workaround to enable that - it renders an object instead!
 * 
 * The interesting thing is: Objects with mesh graphics, that are not listed in HasMeshGraphics()
 * Get rendered if one object is rendered with extra = 4 and XPar1... this seems to be an engine bug
 *
 * Author: Marky
 */

static proplist_addmenuitem;

global func AddMenuItem(string caption, string command, id symbol, int count, parameter, string info_caption, int extra, XPar1, XPar2)
{
	
	//Log(Format("AddMenuItem %s %s", Format("caption: %v, command: %v, symbol: %v, count: %v, parameter: %v", caption, command, symbol, count, parameter), Format(", caption: %v, extra: %v, xpar1: %v, xpar2: %v", info_caption, extra, XPar1, XPar2)));
	var extraX = extra;
	var XPar1X = XPar1;
	
	if (HasMeshGraphics(symbol) && extra == C4MN_ItemExtra_None || extra == C4MN_ItemExtra_BitOverrideValue)
	{
		extraX = extra | C4MN_ItemExtra_Object;
		XPar1X = GetMeshDummy(symbol);
		//Log("Need new gfx for %v", symbol);
	}
	
	return _inherited(caption, command, symbol, count, parameter, info_caption, extraX, XPar1X, XPar2);
}

// does not work, because the engine needs object context... although the docu says otherwise
//global func HasMeshGraphics()
//{
//	if(!this) return false;
//	return this->GetMeshMaterial() != nil;
//}


global func HasMeshGraphics(id type)
{
	return type == ClassicClonk
	    || type == ClassicLorry
	    || type == Shovel
	    || type == ClassicHutWooden;
}

global func GetMeshDummy(id type)
{
	var name = Format("%v", type);

	var dummy = GetProperty(name, proplist_addmenuitem);
	if (!dummy)
	{
		dummy = CreateObject(Dummy, 0, 0, NO_OWNER);
		dummy->SetGraphics(nil, Library_Structure, 0, GFXOV_MODE_None);
		dummy->SetGraphics(nil, type, 1, GFXOV_MODE_Picture);
		
		if (!SetProperty(name, dummy, proplist_addmenuitem))
		{
			proplist_addmenuitem = {"Dummy" = nil};
			SetProperty(name, dummy, proplist_addmenuitem);
		}
	}
	
	return dummy;
}
