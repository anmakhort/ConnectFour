#include "../include/connectfour.h"

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];

void new_game(object_t *sender) {
	for (short i = 0; i < BF_SIZE_X; i++) {
		for (short j = 0; j < BF_SIZE_Y; j++) {
			bfield[i][j].value = -1;
			bfield[i][j].player = -1;
		}
	}
	if (sender) update(sender);
}