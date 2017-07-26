#include "../include/connectfour.h"

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];
point_t last_move_pt;

void undo_move(object_t *sender) {
	if (!sender) return;
	if (last_move_pt.x < 0 || last_move_pt.y < 0) \
		return;
	if (sender->winner >= 0) return;
	
	bfield[last_move_pt.x][last_move_pt.y].value = -100;
	bfield[last_move_pt.x][last_move_pt.y].player = -1;
	
	last_move_pt.x = -1;
	last_move_pt.y = -1;
	
	sender->player = (sender->player == 0) ? \
			(NUM_PLAYERS-1) : (sender->player-1);
	sender->nmoves -= 1;

	update(sender);
}