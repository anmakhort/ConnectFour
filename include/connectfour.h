#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>

#define WND_TITLE	"Connect Four"
#define WND_X		0
#define WND_Y		0
#define WND_WIDTH	700
#define WND_HEIGHT	500
#define WND_BRD_W	10
#define WND_BRD_C	0x0
#define WND_BG_C	0xffffff

#define KEYBOARD_ESC_KEY	0x09

#define KEYBOARD_LEFT_ARROW
#define KEYBOARD_RIGHT_ARROW
#define KEYBOARD_DOWN_ARROW
#define KEYBOARD_A_KEY
#define KEYBOARD_D_KEY
#define KEYBOARD_S_KEY
#define KEYBOARD_O_KEY
#define KEYBOARD_P_KEY
#define KEYBOARD_N_KEY
#define KEYBOARD_M_KEY
#define KEYBOARD_SPACE_KEY

typedef struct object_s {
	Display *disp;
	Window wnd;
} object_t;

void exposed_handler(object_t *sender);
void key_released_handler(int key, object_t *sender);

#endif