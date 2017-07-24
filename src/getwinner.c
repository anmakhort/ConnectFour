#include "../include/connectfour.h"

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];

char test_horiz() {
	return -1;
}

char test_verts() {
	return -1;
}

char test_diags() {
	return -1;
}

void draw_greetings(object_t *sender) {
	GC gc;
	if (NULL == get_GC(sender, &gc)) return;

	XSync(sender->disp, sender->screen);

	if (sender->winner >= 0) {
		char buff[64] = {0};
		int n = sprintf(buff, GREETINGS_STRING, (sender->winner+1));
		buff[n] = '\0';

		Font font = XLoadFont(sender->disp, "*x16");
		XSetFont(sender->disp, gc, font);
		XTextItem text = {buff, n, 10, font};

		XSetForeground(sender->disp, gc, player_color[(int)sender->winner]);
		XDrawText(sender->disp, *sender->wnd, gc, GREETINGS_X, GREETINGS_Y, &text, 1);

		if (!XGetSubImage(sender->disp, *sender->wnd, 0, 0, BF_WIDTH, BF_HEIGHT, \
					AllPlanes, ZPixmap, sender->frame_img, 0, 0)) {

			perror("XGetSubImage: ERROR!\n");
		}
	}
}

char get_winner(object_t *sender) {
	if (!sender) return -1;

	test_horiz();
	test_verts();
	test_diags();

	sender->winner = 1;

	draw_greetings(sender);

	XClearWindow(sender->disp, *sender->wnd);
	XPutImage(sender->disp, *sender->wnd, \
			DefaultGC(sender->disp, 0), \
			sender->frame_img, \
			0, 0, 0, 0, \
			BF_WIDTH, BF_HEIGHT);
	
	return sender->winner;
}