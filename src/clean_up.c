#include "../include/connectfour.h"

void clean_up(object_t *sender) {
	if (!sender) return;
	if (sender->frame_img)
		XDestroyImage(sender->frame_img);
	else if (sender->img_ptr)
		free(sender->img_ptr);
	XDestroyWindow(sender->disp, *sender->wnd);
	XCloseDisplay(sender->disp);
	exit(0);
}