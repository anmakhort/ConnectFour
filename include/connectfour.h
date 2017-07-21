#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

// main window params:
#define WND_TITLE	"Connect Four"
#define WND_X		0
#define WND_Y		0
#define WND_WIDTH	700
#define WND_HEIGHT	500
#define WND_BRD_W	10
#define WND_BRD_C	0x0
#define WND_BG_C	0xffffff

// quit(exit) keys:
#define KEYBOARD_ESC	0xff1b
#define KEYBOARD_Q		0x71
// navigation player1:
#define KEYBOARD_A		0x61
#define KEYBOARD_D		0x64
#define KEYBOARD_SPACE	0x20
// navigation player2:
#define KEYBOARD_LEFT	0xff51
#define KEYBOARD_RIGHT	0xff53
#define KEYBOARD_DOWN	0xff54
// save/load last game:
#define KEYBOARD_S		0x73
#define KEYBOARD_L		0x6c
// printscreen:
#define KEYBOARD_P		0x70
// new game:
#define KEYBOARD_N		0x6e
// game mode:
#define KEYBOARD_M		0x6d
// undo move:
#define KEYBOARD_BSPACE	0xff08

typedef struct object_s {
	Display *disp;
	Window wnd;
} object_t;

void exposed_handler(XExposeEvent *ev, object_t *sender);
void key_released_handler(XKeyEvent *ev, object_t *sender);

#endif