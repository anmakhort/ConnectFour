#include "../include/connectfour.h"

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];

static int counter;

void mouse_key_pressed_handler(XButtonPressedEvent *ev, object_t *sender) {
	if (!ev || !sender) return;
	if (sender->winner >= 0) return;

	sender->tile_idx_x = -1;

	const double tx = TILE_WIDTH+TILE_X_SPACE;
	for (char i = 0; i < BF_SIZE_X; i++) {
		if ((ev->x >= (i*tx+TILE_X_SPACE)) && (ev->x <= (tx*(i+1)))) {
			sender->tile_idx_x = i;
			break;
		}
	}

	if (sender->tile_idx_x < 0) return;
	if (bfield[(int)sender->tile_idx_x][0].value > 0) return;

	GC gc;
	if (NULL == get_GC(sender, &gc)) return;

	XClearWindow(sender->disp, *sender->wnd);

	short x = TILE_X_SPACE + (TILE_WIDTH + TILE_X_SPACE) * sender->tile_idx_x;
	uint8_t idx = (uint8_t)(bfield[(int)sender->tile_idx_x][0].player);
	XSetForeground(sender->disp, gc, player_color[idx]);
	XFillArc(sender->disp, *sender->wnd, gc, x+CIRCLE_DELTA/2, \
			TILE_Y_SPACE+CIRCLE_DELTA/2, TILE_WIDTH-CIRCLE_DELTA, \
			TILE_HEIGHT-CIRCLE_DELTA, 0, 360*64);
	
	sender->player = (sender->player + 1) % NUM_PLAYERS;
	bfield[(int)sender->tile_idx_x][0].value = 1;
	animate_falling(sender->tile_idx_x, 0, sender);

	if ((++counter) == 5) {
		get_winner(sender);
		update(sender);
		update(sender);
		counter = 0;
	}
}