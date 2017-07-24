#include "../include/connectfour.h"

void clean_up_exit(object_t *sender) {
	if (!sender) return;
	if (sender->game_bg) {
		XFreePixmap(sender->disp, *sender->game_bg);
		free(sender->game_bg);
	}
	if (sender->frame_img)
		XDestroyImage(sender->frame_img);
	else if (sender->img_ptr)
		free(sender->img_ptr);
	XDestroyWindow(sender->disp, *sender->wnd);
	XCloseDisplay(sender->disp);
	exit(0);
}