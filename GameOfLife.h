
#include "Adafruit_ILI9341.h"
#ifndef _GAMEOFLIFE_
#define _GAMEOFLIFE_


#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */

#define ROTATE_NONE 0
#define ROTATE_90 1
#define ROTATE_180 2
#define ROTATE_270 3

class GameOfLife {
public:
	GameOfLife(uint16_t w, uint16_t h, uint8_t s);
	void reset();
	void draw(Adafruit_ILI9341 &gfx);
	void evolve();
private:
	void drawCell(Adafruit_ILI9341 &gfx,
		uint16_t row, uint16_t col, uint16_t color);
	uint8_t countNeighbors(uint16_t row, uint16_t col);
	uint16_t width, height;
	uint8_t size;
	bool **universe;
	bool **newUniverse;
};

#endif
