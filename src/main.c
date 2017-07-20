#include "../include/connectfour.h"

int main() {
	Display	*display = XOpenDisplay(NULL);
	if (!display) {
		perror("Can't open display!");
		exit(1);
	}
	
	int screen = DefaultScreen(display);
	
	Window win = XCreateSimpleWindow(display, \
		RootWindow(display, screen), \
		WND_X, WND_Y, \
		WND_WIDTH, WND_HEIGHT, \
		WND_BRD_W, WND_BRD_C, \
		WND_BG_C);
	
	XSelectInput(display, win, ExposureMask | KeyReleaseMask);

	XStoreName (display, win, WND_TITLE);
	XMapWindow(display, win);

	while (1) {
		XEvent event;
		XNextEvent(display, &event);
		object_t sender = {display, win};

		switch (event.type) {
			case Expose:
				exposed_handler(&sender);
				break;
			case KeyRelease:
				key_released_handler(event.xkey.keycode, &sender);
				break;
			default:
				break;
		}
	}

	return 0;
}