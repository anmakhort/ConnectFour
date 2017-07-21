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
	XClearWindow(display, win);

	XFlush(display);
	XSync(display, 0);

	XMapWindow(display, win);
	XSync(display, 0);

	char *img_buff = NULL;
	XImage *img = create_frame_image(display, visual, depth, &img_buff);
	
	object_t sender = {display, &win, img, img_buff};

	while (1) {
		XEvent event;
		XNextEvent(display, &event);

		switch (event.type) {
			case Expose:
				exposed_handler(&event.xexpose, &sender);
				break;
			case KeyRelease:
				key_released_handler(&event.xkey, &sender);
				break;
			default:
				break;
		}
	}

	return 0;
}

XImage *create_frame_image(Display *disp, Visual *vis, int depth, char **buff) {
	if (!disp || !vis || depth < 24 || !buff) return NULL;
	if (*buff) free(*buff);
	*buff = malloc(4 * sizeof(char) * BF_WIDTH * BF_HEIGHT);
	return XCreateImage(disp, vis, depth, ZPixmap, 0, *buff, \
		BF_WIDTH, BF_HEIGHT, 32, 0);
}