#include "../include/connectfour.h"

void exposed_handler(XExposeEvent *ev, object_t *sender) {
	if (!sender || !ev) return;
	update(sender);
}