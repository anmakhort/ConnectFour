#include "../include/connectfour.h"

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];

uint8_t test_0_180(char player, short x, short y) {
	// 1. maximum possible left move:
	while (x > 0) {
		if (bfield[--x][y].player != player) {
			++x;
			break;
		}
	}
	// 2. counting the player's tiles:
	uint8_t cnt = 0;
	while (x < BF_SIZE_X) {
		if (bfield[x++][y].player == player) cnt++;
		else break;
	}
	// 3. if we have at least '4' tiles -> winner:
	return (cnt >= 4);
}

uint8_t test_90_270(char player, short x, short y) {
	// 1. maximum possible up move:
	while (y > 0) {
		if (bfield[x][--y].player != player) {
			++y;
			break;
		}
	}
	// 2. counting the player's tiles:
	uint8_t cnt = 0;
	while (y < BF_SIZE_Y) {
		if (bfield[x][y++].player == player) cnt++;
		else break;
	}
	// 3. if we have at least '4' tiles -> winner:
	return (cnt >= 4);
}

uint8_t test_45(char player, short x, short y) {
	// 1. maximum possible top-right move:
	while (y > 0 && x < BF_SIZE_X-1) {
		if (bfield[++x][--y].player != player) {
			++y;
			--x;
			break;
		}
	}
	// 2. counting the player's tiles:
	uint8_t cnt = 0;
	while (y < BF_SIZE_Y && x >= 0) {
		if (bfield[x--][y++].player == player) cnt++;
		else break;
	}
	// 3. if we have at least '4' tiles -> winner:
	return (cnt >= 4);
}

uint8_t test_135(char player, short x, short y) {
	// 1. maximum possible top-left move:
	while (y < BF_SIZE_Y-1 && x > 0) {
		if (bfield[--x][++y].player != player) {
			--y;
			++x;
			break;
		}
	}
	// 2. counting the player's tiles:
	uint8_t cnt = 0;
	while (y < BF_SIZE_Y && x < BF_SIZE_X) {
		if (bfield[x++][y++].player == player) cnt++;
		else break;
	}
	// 3. if we have at least '4' tiles -> winner:
	return (cnt >= 4);
}

uint8_t test_for_player(char player) {
	if (player < 0 || player >= NUM_PLAYERS) return 0;
	uint8_t win = 0;
	for (short i = 0; !win && i < BF_SIZE_X; i++) {
		for (short j = 0; !win && j < BF_SIZE_Y; j++) {
			if (bfield[i][j].player == player) {
				win = test_0_180(player, i, j) | \
						test_45(player, i, j) | \
						test_90_270(player, i, j) | \
						test_135(player, i, j);
			}
		}
	}
	return win;
}

char draw_greetings(object_t *sender) {
	GC gc;
	if (NULL == get_GC(sender, &gc)) return -1;

	XSync(sender->disp, sender->screen);

	char buff[TEXT_BUFFER_SIZE] = {0};
	Font font = XLoadFont(sender->disp, "*x16");
	XSetFont(sender->disp, gc, font);
	XTextItem text;
	text.delta = 10;
	text.font = font;

	short x = -1, y = -1;
	uint32_t color = 0;
	int n = -1;

	if (sender->winner >= 0) {
		n = sprintf(buff, GREETINGS_STRING, (sender->winner+1));
		x = GREETINGS_X;
		y = GREETINGS_Y;
		color = GREETINGS_COLOR;
	} else {
		if (sender->nmoves == (BF_SIZE_X * BF_SIZE_Y)) {
			strcpy(buff, DRAW_STRING);
			n = DRAW_SIZE;
			x = DRAW_X;
			y = DRAW_Y;
			color = DRAW_COLOR;
		}
	}

	if (n < 0 || x < 0 || y < 0) return -1;

	buff[n] = '\0';
	text.nchars = n;
	text.chars = buff;

	XSetForeground(sender->disp, gc, color);
	XDrawText(sender->disp, *sender->wnd, gc, x, y, &text, 1);

	if (!XGetSubImage(sender->disp, *sender->wnd, 0, 0, BF_WIDTH, BF_HEIGHT, \
								AllPlanes, ZPixmap, sender->frame_img, 0, 0)) {
		perror("XGetSubImage: ERROR!\n");
	}

	XPutImage(sender->disp, *sender->wnd, \
			DefaultGC(sender->disp, 0), \
			sender->frame_img, \
			0, 0, 0, 0, \
			BF_WIDTH, BF_HEIGHT);

	XSync(sender->disp, sender->screen);

	return 1;
}

void get_winner(object_t *sender) {
	if (!sender) return;

	sender->winner = -1;
	for (char player = 0; player < NUM_PLAYERS; player++) {
		if (test_for_player(player)) {
			sender->winner = player;
			break;
		}
	}
	draw_greetings(sender);
}