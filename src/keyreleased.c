#include "../include/connectfour.h"

void key_released_handler(XKeyEvent *ev, object_t *sender) {
	if (!sender || !ev) return;

	switch ( XLookupKeysym(ev, 0) ) {
		case KEYBOARD_ESC:
		case KEYBOARD_Q:
			clean_up_exit(sender);
			break;

		case KEYBOARD_N:
			sender->winner = -1;
			new_game(sender);
			break;

		case KEYBOARD_P:
			print_screen(sender->frame_img, "prntscrn.png");
			break;

		case KEYBOARD_BSPACE:
			undo_move(sender);
			break;

		case KEYBOARD_S:
			save_game(sender, "game.bin");
			break;
			
		default:
			break;
	}
}