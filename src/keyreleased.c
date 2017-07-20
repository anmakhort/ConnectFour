#include "../include/connectfour.h"

void key_released_handler(int key, object_t *sender) {
	if (!sender) return;
	if (key == KEYBOARD_ESC_KEY) {
		XDestroyWindow(sender->disp, sender->wnd);
		XCloseDisplay(sender->disp);
		exit(0);
	}
}