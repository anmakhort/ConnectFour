#include "../include/connectfour.h"

XImage *create_frame_image(Display *disp, Visual *vis, int depth, char **buff) {
	if (!disp || !vis || depth < 24 || !buff) return NULL;
	if (*buff) free(*buff);
	*buff = malloc(4 * sizeof(char) * BF_WIDTH * BF_HEIGHT);
	return XCreateImage(disp, vis, depth, ZPixmap, 0, *buff, \
		BF_WIDTH, BF_HEIGHT, 32, 0/*4*BF_WIDTH*/);
}