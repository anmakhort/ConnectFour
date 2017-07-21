#include "../include/connectfour.h"

char bfield[BF_SIZE_Y][BF_SIZE_X];

void update(object_t *sender) {
	if (!sender) return;
	XClearWindow(sender->disp, *sender->wnd);
	for (unsigned char i = 0; i < BF_SIZE_Y; i++) {
		for (unsigned char j = 0; j < BF_SIZE_X; j++) {
			printf("%d  ", bfield[i][j]);
		}
		printf("\n");
	}
	if (sender->frame_img) {
		XPutImage(sender->disp, *sender->wnd, \
			DefaultGC(sender->disp, 0), \
			sender->frame_img, \
			0, 0, BF_OFFSET_X, BF_OFFSET_Y, \
			BF_WIDTH, BF_HEIGHT);
	}
	XFlush(sender->disp);
}