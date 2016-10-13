#include "bitmap.h"

int main()
{
	uint8_t ** test_canvas = init_canvas(1024, 256);
	uint8_t i;
	uint32_t increment = 1024 / 16;
	struct rgba red = {0x00, 0x00, 0xFF, 0x00};

	printf("Going to write rectangles.\n");

	for (i = 0; i < 16; i++)
	{
		printf("Rectangle %i\n", i);
		rectangle(test_canvas, increment * i, 0, increment * (i + 1), 256, i);
	}

	printf("Rectangles written.\n");

	save_canvas("sample.bmp", test_canvas, 256, 1024);
	return 0;
}
