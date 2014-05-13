/*
 * Object selector draws the picture only on the hotkey object, but not on the c4menu icon.
 * 
 * Here is a workaround!
 * 
 * Author: Marky
 */

#appendto GUI_ObjectSelector

static const g_GUI_ObjectSelector_OverlayOffset = 16;

public func SetGraphics(string gfx_name, id source_definition, int overlay, int overlay_mode, string action, int dwBlitMode, object overlay_object)
{
	var retval = _inherited( gfx_name, source_definition, overlay, overlay_mode, action, dwBlitMode, overlay_object);

		if (overlay_mode == GFXOV_MODE_ObjectPicture && overlay_object)
		{
			_inherited( gfx_name, overlay_object->GetID(), overlay+g_GUI_ObjectSelector_OverlayOffset, GFXOV_MODE_Picture, action, dwBlitMode, nil);
		}
		else if (source_definition != Icon_Number)
		{
			_inherited( gfx_name, source_definition, overlay+g_GUI_ObjectSelector_OverlayOffset, GFXOV_MODE_Picture, action, dwBlitMode, overlay_object);
		}

	return retval;
}

public func SetObjDrawTransform(int width, int xskew, int xadjust, int yskew, int height, int yadjust, int overlay_id)
{
		   _inherited(width, xskew, xadjust/4, yskew, height, yadjust/4, overlay_id+g_GUI_ObjectSelector_OverlayOffset);
	return _inherited(width, xskew, xadjust, yskew, height, yadjust, overlay_id);
}

