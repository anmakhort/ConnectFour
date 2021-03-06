#include "../include/connectfour.h"

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];
point_t last_move_pt;

void animate_falling(uint8_t i, uint8_t j, object_t *sender) {
	if (!sender) return;
	if (i >= BF_SIZE_X || j >= BF_SIZE_Y) return;
	update(sender);
	j = j+1;
	while (bfield[i][j].value <= 0 && (j < BF_SIZE_Y)) {
		bfield[i][j].value = 1;
		bfield[i][j].player = sender->player;
		bfield[i][j-1].value = -1;
		bfield[i][j-1].player = -1;
		update(sender);
		j++;
	}
	last_move_pt.x = (short)i;
	last_move_pt.y = (short)(j-1);
}