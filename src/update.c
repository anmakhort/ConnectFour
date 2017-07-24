#include "../include/connectfour.h"

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];

void update(object_t *sender) {
	if (!sender) return;

	XSetWindowBackgroundPixmap(sender->disp, \
						*sender->wnd, \
						*sender->game_bg);

	XSync(sender->disp, sender->screen);

	if (sender->winner >= 0) return;

	GC gc;
	if (NULL == get_GC(sender, &gc)) return;

	XClearWindow(sender->disp, *sender->wnd);

	for (short i = 0; i < BF_SIZE_X; i++) {
		short x = TILE_X_SPACE + (TILE_WIDTH + TILE_X_SPACE) * i;
		
		for (short j = 0; j < BF_SIZE_Y; j++) {
			short y = TILE_Y_SPACE + (TILE_HEIGHT + TILE_Y_SPACE) * j;

			if (sender->player >= 0 && bfield[i][j].value > 0) {
				//
				if (bfield[i][j].player < 0) bfield[i][j].player = sender->player;
				//
				XSetForeground(sender->disp, gc, \
					player_color[(uint8_t)(bfield[i][j].player)]);
				//
				XFillArc(sender->disp, *sender->wnd, gc, x+CIRCLE_DELTA/2, \
					y+CIRCLE_DELTA/2, TILE_WIDTH-CIRCLE_DELTA, TILE_HEIGHT-CIRCLE_DELTA, \
					0, 360*64);
			}
		}
	}

	XSync(sender->disp, sender->screen);

	if (!XGetSubImage(sender->disp, *sender->wnd, 0, 0, BF_WIDTH, BF_HEIGHT, \
					AllPlanes, ZPixmap, sender->frame_img, 0, 0)) {

		perror("XGetSubImage: ERROR!\n");
	}

	XFlush(sender->disp);
}