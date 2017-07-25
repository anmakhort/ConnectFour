#include "../include/connectfour.h"

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];

void new_game(object_t *sender) {
	for (short i = 0; i < BF_SIZE_X; i++) {
		for (short j = 0; j < BF_SIZE_Y; j++) {
			bfield[i][j].value = -1;
			bfield[i][j].player = ~0;
		}
	}
	if (sender) {
		sender->player = -1;
		sender->tile_idx_x = -1;
		sender->winner = -1;
		sender->nmoves = 0;
		update(sender);
	}
}