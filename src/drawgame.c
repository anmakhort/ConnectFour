#include "../include/connectfour.h"

void draw_tile_grid(object_t *sender) {
	if (!sender) return;

	GC gc;
	if (NULL == get_GC(sender, &gc)) return;

	XClearWindow(sender->disp, *sender->wnd);
	XSetForeground(sender->disp, gc, 0xffffff);

	XFillRectangle(sender->disp, *sender->wnd, gc, TILE_X_SPACE, TILE_Y_SPACE, TILE_WIDTH, TILE_HEIGHT);

	short x = TILE_X_SPACE;
	for (short i = 1; i < BF_SIZE_X; i++) {
		x += (TILE_WIDTH + TILE_X_SPACE);
		XCopyArea(sender->disp, *sender->wnd, *sender->wnd, gc, TILE_X_SPACE, TILE_Y_SPACE, TILE_WIDTH, TILE_HEIGHT, x, TILE_Y_SPACE);
	}

	short y = TILE_Y_SPACE;
	for (short j = 1; j < BF_SIZE_Y; j++) {
		y += (TILE_HEIGHT + TILE_Y_SPACE);
		XCopyArea(sender->disp, *sender->wnd, *sender->wnd, gc, 0, 0, BF_WIDTH, BF_HEIGHT, 0, TILE_Y_SPACE+TILE_WIDTH);
	}

	XSync(sender->disp, sender->screen);
}

void draw_game_field(object_t *sender) {
	if (!sender) return;
	if (sender->game_bg) return;

	sender->game_bg = (Pixmap*)malloc(sizeof(Pixmap));

	*sender->game_bg = XCreatePixmap(sender->disp, \
						*sender->wnd, \
						BF_WIDTH, BF_HEIGHT, \
						DefaultDepth(sender->disp, sender->screen));

	char *buff = NULL;
	XImage *bg_img = create_frame_image(sender->disp, \
		DefaultVisual(sender->disp, sender->screen), \
		DefaultDepth(sender->disp, sender->screen), &buff);

	if (!bg_img) {
		XFreePixmap(sender->disp, *sender->game_bg);
		free(sender->game_bg);
		return;
	}

	draw_tile_grid(sender);

	if (!XGetSubImage(sender->disp, *sender->wnd, 0, 0, BF_WIDTH, BF_HEIGHT, AllPlanes, ZPixmap, bg_img, 0, 0)) {
		perror("XGetSubImage: ERROR!\n");
	}
	XSync(sender->disp, sender->screen);
	
	XPutImage(sender->disp, *sender->game_bg, \
				DefaultGC(sender->disp, 0), \
				bg_img, \
				0, 0, 0, 0, \
				BF_WIDTH, BF_HEIGHT);

	XSync(sender->disp, sender->screen);

	XDestroyImage(bg_img);

	XSetWindowBackgroundPixmap(sender->disp, \
						*sender->wnd, \
						*sender->game_bg);

	XFlush(sender->disp);
}