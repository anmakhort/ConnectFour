#include "../include/connectfour.h"

GC *get_GC(object_t *sender, GC *out) {
	if (!sender || !out) return NULL;
	if (!sender->disp || !sender->wnd) return NULL;

	XGCValues values;
	values.cap_style = CapButt;
	values.join_style = JoinBevel;
	unsigned long valuemask = GCCapStyle | GCJoinStyle;
	*out = XCreateGC(sender->disp, *sender->wnd, valuemask, &values);

	XSetForeground(sender->disp, *out, WhitePixel(sender->disp, sender->screen));
	XSetFillStyle(sender->disp, *out, FillSolid);

	return out;
}