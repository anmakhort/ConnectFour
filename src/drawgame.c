#include "../include/connectfour.h"

void draw_game_field(object_t *sender) {
	if (!sender) return;
	XClearWindow(sender->disp, *sender->wnd);
	XPutImage(sender->disp, *sender->wnd, \
		DefaultGC(sender->disp, 0), \
		sender->frame_img, \
		0, 0, 0, 0, \
		BF_WIDTH, BF_HEIGHT);
	XFlush(sender->disp);
}