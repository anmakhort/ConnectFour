#include <png.h>
#include "../include/connectfour.h"

void print_screen(XImage *pImage, const char *path) {
	FILE *fp = fopen(path, "wb");
    if (!fp) return;
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
    	fprintf(stderr, "Can't create file: %s\n", path);
    	fclose(fp);
    	return;
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
    	fprintf(stderr, "Can't create PNG Info Structure\n");
    	png_destroy_write_struct(&png_ptr, NULL);
    	fclose(fp);
    	return;
    }
    if (setjmp(png_jmpbuf(png_ptr))) {
    	fprintf(stderr, "Can't set JMP\n");
    	png_destroy_write_struct(&png_ptr, &info_ptr);
    	fclose(fp);
    	return;
    }
    png_init_io(png_ptr, fp);
    const int bit_depth = 8;
    png_set_IHDR(png_ptr, info_ptr, pImage->width, pImage->height, \
    	bit_depth, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, \
    	PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_text _text[4];
    _text[0].compression = _text[1].compression = \
    	_text[2].compression = _text[3].compression = \
    		PNG_TEXT_COMPRESSION_zTXt;
    _text[0].key = "Title";
    _text[0].text = "Connect Four";
    _text[1].key = "Author";
    _text[1].text = "Anatolii Makhort";
    _text[2].key = "Software";
    _text[2].text = "Connect Four";
    _text[3].key = "Source";
    _text[3].text = "Connect Four & libpng";
    png_set_text(png_ptr, info_ptr, _text, 4);

    png_write_info(png_ptr, info_ptr);

    png_bytep png_row = (png_bytep)malloc(3*pImage->width*sizeof(png_byte));

    unsigned long red_mask = (pImage->red_mask ? pImage->red_mask : 0xff0000);
    unsigned long green_mask = (pImage->red_mask ? pImage->green_mask : 0xff00);
    unsigned long blue_mask = (pImage->blue_mask ? pImage->blue_mask : 0xff);

    for (int y = 0; y < pImage->height; y++) {
    	for (int x = 0; x < pImage->width; x++) {
    		unsigned long pixel = XGetPixel(pImage, x, y);
    		unsigned char blue = pixel & blue_mask;
    		unsigned char green = (pixel & green_mask) >> 8;
    		unsigned char red = (pixel & red_mask) >> 16;
    		png_byte *ptr = &(png_row[x*3]);
    		ptr[0] = red;
    		ptr[1] = green;
    		ptr[2] = blue;
    	}
    	png_write_row(png_ptr, png_row);
    }
    
    png_write_end(png_ptr, NULL);

    fclose(fp);
    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct (&png_ptr, NULL);
    free(png_row);
}