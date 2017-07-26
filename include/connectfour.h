#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h> // for strlen(...)

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
#define BF_WIDTH	(WND_WIDTH)
#define BF_HEIGHT	(WND_HEIGHT)
#define BF_SIZE_X	7
#define BF_SIZE_Y	6

// tiles:
#define TILE_WIDTH		85
#define TILE_HEIGHT		85
#define CIRCLE_DELTA 	10

// space between two tiles:
#define TILE_X_SPACE (BF_WIDTH-BF_SIZE_X*TILE_WIDTH)/(BF_SIZE_X+1)
#define TILE_Y_SPACE (BF_HEIGHT-BF_SIZE_Y*TILE_HEIGHT)/(BF_SIZE_Y+1)

// quit(exit) keys:
#define KEYBOARD_ESC	0xff1b
#define KEYBOARD_Q		0x71
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

// max players allowed:
#define NUM_PLAYERS		2

// buffer size for greetings:
#define TEXT_BUFFER_SIZE	64

// if winner was found:
#define GREETINGS_STRING	"Player %i won this game! To start new one - press 'N'"
#define GREETINGS_X			(BF_WIDTH / 4 - 35)
#define GREETINGS_Y			(BF_HEIGHT / 2 - 25)
#define GREETINGS_COLOR		0x0039e6

// if the game is draw:
#define DRAW_STRING			"This game is draw. To start new one - press 'N'"
#define DRAW_SIZE			strlen(DRAW_STRING)
#define DRAW_X				(BF_WIDTH / 4 - 50)
#define DRAW_Y				(BF_HEIGHT / 2 - 25)
#define DRAW_COLOR			0xff1ac6

#pragma pack (1)
typedef struct object_s {
	Display *disp;
	Window *wnd;
	Pixmap *game_bg;
	XImage *frame_img;
	char *img_ptr;
	int screen;
	char player;
	char tile_idx_x;
	char winner;
	char nmoves;
} object_t;

typedef struct battlefield_s {
	char value;
	char player;
} bfield_t;

typedef struct point_s {
	short x;
	short y;
} point_t;

static const uint32_t player_color[NUM_PLAYERS] = {0xff0000, 0x00ff00};

extern uint8_t endian;
extern bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];
extern point_t last_move_pt;

// color handling:
uint8_t _isBigEndian();
uint32_t get_color_rgb(uint8_t red, uint8_t green, uint8_t blue);

// to create XImage as window's frame buffer:
XImage *create_frame_image(Display *disp, Visual *vis, int depth, char **img_buff);

// clean-up functions:
void clean_up_exit(object_t *sender);

// game state drawing/updating functions:
void new_game(object_t *sender); // clean game board
void update(object_t *sender); // draw to window & copy to XImage
void draw_game_field(object_t *sender); // put Pixmap to window
void animate_falling(uint8_t i, uint8_t j, object_t *sender);

// undo last move if backspace key was pressed:
void undo_move(object_t *sender);

// eval game (get the winner):
void get_winner(object_t *sender);

// get default GC + some drawing settings:
GC *get_GC(object_t *sender, GC *out);

// make a screenshot and save it to png:
void print_screen(XImage *pImage, const char *path);

// save current game state:
void save_game(object_t *sender, const char *path);

// event handlers:
void exposed_handler(XExposeEvent *ev, object_t *sender);
void key_released_handler(XKeyEvent *ev, object_t *sender);
//void mouse_move_handler(XMotionEvent *ev, object_t *sender);
void mouse_key_pressed_handler(XButtonPressedEvent *ev, object_t *sender);

#endif