#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

// main window params:
#define WND_TITLE	"Connect Four"
#define WND_X		0
#define WND_Y		0
#define WND_WIDTH	700
#define WND_HEIGHT	600
#define WND_BRD_W	0
#define WND_BG_C	0x0ce0fc

// battlefield:
#define BF_OFFSET_X	0
#define BF_OFFSET_Y	0
#define BF_WIDTH	(WND_WIDTH-2*BF_OFFSET_X)
#define BF_HEIGHT	(WND_HEIGHT-2*BF_OFFSET_Y)
#define BF_SIZE_X	7
#define BF_SIZE_Y	6

// tiles:
#define TILE_WIDTH	70
#define TILE_HEIGHT	70

// space between two tiles:
#define TILE_X_SPACE (BF_WIDTH-BF_SIZE_X*TILE_WIDTH)/(BF_SIZE_X+1)
#define TILE_Y_SPACE (BF_HEIGHT-BF_SIZE_Y*TILE_HEIGHT)/(BF_SIZE_Y+1)

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

// returned by key_released_handler
// when exit(quit) key was pressed:
#define EXIT_STATUS		~0
// returned by key_released_handler
// when NO exit/quit key was pressed:
#define NORMAL_STATUS	0

typedef struct object_s {
	Display *disp;
	Window *wnd;
	XImage *frame_img;
	char *img_ptr;
} object_t;

extern uint8_t endian;
extern char bfield[BF_SIZE_Y][BF_SIZE_X];

uint8_t _isBigEndian();

uint32_t get_color_rgb(uint8_t red, uint8_t green, uint8_t blue);
uint32_t get_color_hex(uint32_t argb);

XImage *create_frame_image(Display *disp, Visual *vis, int depth, char **img_buff);

void clean_up(object_t *sender);
void update(object_t *sender);
void exposed_handler(XExposeEvent *ev, object_t *sender);
void key_released_handler(XKeyEvent *ev, object_t *sender);

#endif