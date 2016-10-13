#include "bitmap.h"

struct rgba palette[16] = {
	{0x00, 0x00, 0x00, 0x00},
	{0x59, 0x59, 0x59, 0x00},
	{0x8C, 0x8C, 0x8C, 0x00},
	{0xB2, 0xB2, 0xB2, 0x00},
	{0x8C, 0xB4, 0xD2, 0x00},
	{0x0C, 0x0C, 0x31, 0x00},
	{0x00, 0x40, 0x00, 0x00},
	{0x00, 0x80, 0x00, 0x00},
	{0xFF, 0xFF, 0x00, 0x00},
	{0xFF, 0x00, 0x00, 0x00},
	{0x80, 0x00, 0x80, 0x00},
	{0xFF, 0x00, 0xFF, 0x00},
	{0x00, 0x00, 0xFF, 0x00},
	{0x00, 0xA5, 0xFF, 0x00},
	{0x00, 0xFF, 0xFF, 0x00},
	{0xFF, 0xFF, 0xFF, 0x00} };

uint8_t ** init_canvas(uint32_t cols, 
                       uint32_t rows)
{
	uint32_t i;

	uint8_t ** result = (uint8_t**)malloc(rows * sizeof(uint8_t*));
	for (i = 0; i < rows; i++)
		result[i] = (uint8_t *)malloc(cols * sizeof(uint8_t));

	return result;
}

int fill(uint8_t ** c, 
         uint32_t rows, 
         uint32_t cols, 
         uint8_t color)
{
	uint32_t x, y;
	for (x = 0; x < rows; x++) {
		for (y = 0; y < cols; y++) {
			c[x][y] = color;
		}
	}
	return 0;
}

int square(uint8_t ** c, 
           uint32_t x, 
           uint32_t y, 
           uint32_t size, 
           uint8_t color)
{
	uint32_t a, b;
	for (a = x; a < size + x; a++) {
		for (b = y; b < size + y; b++)
			c[b][a] = color;
	}

	return 0;
}

int rectangle(uint8_t ** c, 
              uint32_t x1, 
              uint32_t y1, 
              uint32_t x2, 
              uint32_t y2, 
              uint8_t color)
{
	uint32_t a, b;

	for (a = x1; a < x2; a++) {
		for (b = y1; b < y2; b++)
			c[b][a] = color;
	}

	return 0;
}

int line(uint8_t  ** c, 
         uint32_t x1, 
         uint32_t y1, 
         uint32_t x2, 
         uint32_t y2, 
         uint32_t thickness, 
         uint8_t  color)
{
	double actual_y;
	uint32_t i;
	uint32_t half_thick = thickness / 2;

	if (x2 < x1) {
		uint32_t xcopy = x1;
		x1 = x2;
		x2 = xcopy;
	}

	double slope = (double)(y2 - y1) / (double)(x2 - x1);
	for (x1; x1 < x2; x1++) {
		for (i = 0; i < thickness; i++)
			c[(int)actual_y + i - half_thick][x1] = color;
		
		actual_y += slope;
	}

	return 0;
}

int save_canvas(const char * path, 
                uint8_t ** c,
                int32_t rows,
                int32_t cols)
{
	struct bmp_header head;
	struct dib_header dib;
	int32_t i, j;
	
	FILE * fp = fopen(path, "wb");
	if (fp == NULL)
		return -1;
	
	head.ascii[0] = 'B';
	head.ascii[1] = 'M';
	head.size = rows * (cols/2 + (cols/2)%4) + sizeof(head) + sizeof(dib);
	head.reserved1 = 0;
	head.reserved2 = 0;
	head.offset = sizeof(head) + sizeof(dib) + sizeof(palette);
	
	dib.size = sizeof(dib);
	dib.width = cols;
	dib.height = rows;
	dib.num_planes = 1;
	dib.bpp = 4;
	dib.compression = 0;
	dib.raw_size = rows * (cols/2 + (cols/2)%4);
	dib.hres = 0x0B13;
	dib.vres = 0x0B13;
	dib.num_colors = 0x10;
	dib.num_important = 0;
	
	fwrite((void*)&head, sizeof(head), 1, fp);
	fwrite((void*)&dib, sizeof(dib), 1, fp);
	
	for (i = 0; i < 16; i++)
		fwrite(&palette[i], sizeof(palette[i]), 1, fp);

	//Write the pixel array.
	uint8_t byte, padding = ((cols / 2) % 4);
	uint32_t zero = 0;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j+= 2) {
			byte = c[i][j + 1];
			byte += (c[i][j] << 4);
			fwrite(&byte, sizeof(byte), 1, fp);
		}

		fwrite(&zero, 1, padding, fp);
	}

	return 0;
}

