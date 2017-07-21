#include "../include/connectfour.h"

void key_released_handler(XKeyEvent *ev, object_t *sender) {
	if (!sender || !ev) return;

	switch ( XLookupKeysym(ev, 0) ) {
		case KEYBOARD_ESC:
		case KEYBOARD_Q:
			clean_up(sender);
		default:
			break;
	}
}