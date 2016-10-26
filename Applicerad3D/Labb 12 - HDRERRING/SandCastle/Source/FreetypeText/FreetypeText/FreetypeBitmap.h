#pragma once

struct FreetypeBitmap
{
	unsigned int    rows;
	unsigned int    width;
	int             pitch;
	unsigned char*  buffer;
	unsigned short  num_grays;
	unsigned char   pixel_mode;
	unsigned char   palette_mode;
	void*           palette;

};