#include "../include/connectfour.h"

void exposed_handler(XExposeEvent *ev, object_t *sender) {
	if (!sender || !ev) return;

	if (sender->game_bg) {
		XClearWindow(sender->disp, *sender->wnd);
		XPutImage(sender->disp, *sender->wnd, \
					DefaultGC(sender->disp, 0), \
					sender->frame_img, \
					0, 0, 0, 0, \
					BF_WIDTH, BF_HEIGHT);
	} else {
		draw_game_field(sender);
		update(sender);
	}

	XFlush(sender->disp);
}