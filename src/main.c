#include "../include/connectfour.h"

uint8_t endian;

int main() {
	endian = _isBigEndian();

	Display	*display = XOpenDisplay(NULL);
	if (!display) {
		perror("Can't open display!");
		exit(1);
	}
	
	int screen = DefaultScreen(display);
	int depth = DefaultDepth(display, screen);
	Visual *visual = DefaultVisual(display, screen);

	XSetWindowAttributes xswa;
	xswa.border_pixel = BlackPixel(display, screen);

	Window win = XCreateWindow(display, DefaultRootWindow(display), \
		WND_X, WND_Y, WND_WIDTH, WND_HEIGHT, WND_BRD_W, \
		depth, InputOutput, visual, CWBorderPixel, &xswa);
	
	XStoreName(display, win, WND_TITLE);
	XSelectInput(display, win, ExposureMask | KeyReleaseMask);

	XSizeHints hints;
	XGetWMNormalHints(display, win, &hints, NULL);
	hints.width = hints.min_width = hints.max_width = WND_WIDTH;
	hints.height = hints.min_height = hints.max_height = WND_HEIGHT;
	hints.flags = PPosition | PSize | PMinSize | PMaxSize;
	XSetWMNormalHints(display, win, &hints);

	XSetWindowBackground(display, win, WND_BG_C);
	XMapWindow(display, win);

	Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, win, &WM_DELETE_WINDOW, 1);
    XSync(display, 0);

	char *img_buff = NULL;
	XImage *img = create_frame_image(display, visual, depth, &img_buff);
	
	// allocate struct on STACK, because 37 bytes (40 bytes without packing)
	// is not so critical compared to the default stack size & don't need to
	// care about manually deallocating its memory:
	object_t sender = {display, &win, img, img_buff, screen, -1};

	// no need to pass object_t* struct as argument,
	// because update(...) will be called from
	// the exposed_handler(...) at the beginning
	// of the GUI initialisation, so we use NULL:
	new_game(NULL);

	while (1) {
		XEvent event;
		XNextEvent(display, &event);

		switch (event.type) {
			case Expose:
				if (0 == event.xexpose.count)
					exposed_handler(&event.xexpose, &sender);
				break;

			case KeyRelease:
				key_released_handler(&event.xkey, &sender);
				break;

			case ClientMessage:
				// it is OK, because we subscribed only to the
				// "pressed 'X' window's button" event -
				// so, do clean-up, disconnect from the server
				// and exit:
				clean_up_exit(&sender);
				break;

			default:
				break;
		}
	}

	return 0;
}