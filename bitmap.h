#ifndef BITMAP_H
#define BITMAP_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>


typedef enum {	
	BLACK = 0, 
	DARK_GRAY, 
	MEDIUM_GRAY, 
	LIGHT_GRAY,
	TAN, 
	BROWN, 
	DARK_GREEN, 
	GREEN, 
	CYAN,
	BLUE, 
	PURPLE, 
	MAGENTA, 
	RED, 
	ORANGE, 
	YELLOW, 
	WHITE 
} colors;

struct rgba {
	uint8_t b;
	uint8_t g;
	uint8_t r;
	uint8_t a;
} __attribute__ ((__packed__));

struct bmp_header {
	char ascii[2];
	uint32_t size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset;
} __attribute__ ((__packed__));

struct dib_header {
	uint32_t size;
	int32_t  width;
	int32_t  height;
	uint16_t num_planes;
	uint16_t bpp;
	uint32_t compression;
	uint32_t raw_size;
	uint32_t hres;
	uint32_t vres;
	uint32_t num_colors;
	uint32_t num_important;	
} __attribute__ ((__packed__));

uint8_t ** init_canvas(uint32_t max_x, 
                       uint32_t max_y);

int fill(uint8_t ** canvas, 
         uint32_t rows, 
         uint32_t cols, 
         uint8_t color);

int square(uint8_t ** canvas, 
           uint32_t x, 
           uint32_t y, 
           uint32_t length, 
           uint8_t color);

int rect(uint8_t ** canvas, 
         uint32_t x1, 
         uint32_t y1, 
         uint32_t x2, 
         uint32_t y2, 
         uint8_t color);
         
int line(uint8_t ** canvas, 
         uint32_t x1, 
         uint32_t y1, 
         uint32_t x2, 
         uint32_t y2, 
         uint32_t thickness, 
         uint8_t color);

int save_canvas(const char * path, 
                uint8_t ** canvas, 
                int32_t rows, 
                int32_t cols);



#endif
