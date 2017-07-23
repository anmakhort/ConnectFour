#include "../include/connectfour.h"

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];
int iii = 0, jjj = 0, cntr = 0;

void key_released_handler(XKeyEvent *ev, object_t *sender) {
	if (!sender || !ev) return;

	switch ( XLookupKeysym(ev, 0) ) {
		case KEYBOARD_ESC:
		case KEYBOARD_Q:
			clean_up_exit(sender);
			break;

		case KEYBOARD_N:
			new_game(sender);
			iii = jjj = cntr = 0;
			break;
			
		default:
			sender->player = (cntr++) % NUM_PLAYERS;
			bfield[iii][jjj].value = 1;
			animate_falling(iii, jjj, sender);
			if (iii < BF_SIZE_X) iii++;
			else iii = 0;
			if (bfield[iii][0].value > 0) break;
			break;
	}
}