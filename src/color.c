#include "../include/connectfour.h"

uint8_t endian;

uint8_t _isBigEndian() {
	uint32_t a = 0xAA0000FF;
	return (uint8_t)(((uint8_t *)&a)[0] == 0xAA);
}

uint32_t get_color_rgb(uint8_t red, uint8_t green, uint8_t blue) {
	if (!endian) { // Little Endian:
		return (uint32_t)((uint32_t)blue | (((uint32_t)green)<<0x8) | (((uint32_t)red)<<0x10));
	} else { // else Big Endian:
		return (uint32_t)((uint32_t)red | (((uint32_t)green)<<0x8) | (((uint32_t)blue)<<0x10));
	}
}

uint32_t get_color_hex(uint32_t argb) {
	return argb;
}