#include "GameOfLife.h"
#define PAD 3

GameOfLife::GameOfLife(uint16_t w, uint16_t h, uint8_t s) {
	width = w;
	height = h;
	size = s;
	universe = new bool*[height];
	newUniverse = new bool*[height];
	for(int row = 0; row < height; row++) {
		universe[row] = new bool[width];
		newUniverse[row] = new bool[width];
	}
}

void GameOfLife::reset() {
	for(uint16_t row = 0; row < height; row++) {
		for(uint16_t col = 0; col < width; col++) {
			universe[row][col] = random(0,99) < 10;
			newUniverse[row][col] = false;
		}	
	}
}

void GameOfLife::draw(Adafruit_ILI9341 &gfx) {
	for(uint16_t row = 0; row < height; row++) {
		for(uint16_t col = 0; col < width; col++) {
			if(universe[row][col]) {
				drawCell(gfx, row, col, GREEN);
			} else {
				drawCell(gfx, row, col, BLACK);
			}
		}	
	}

	evolve();
}

void GameOfLife::evolve() {
	for(uint16_t row = 0; row < height; row++) {
		for(uint16_t col = 0; col < width; col++) {
			uint8_t neighbors = countNeighbors(row, col);
			bool isAlive = universe[row][col];
			if(isAlive && neighbors == 0 || neighbors == 1) {
				newUniverse[row][col] = false;
			} else if(isAlive && neighbors > 3) {
				newUniverse[row][col] = false;
			} else if(isAlive && neighbors == 2 || neighbors == 3) {
				newUniverse[row][col] = true;
			} else if(!isAlive && neighbors == 3) {
				newUniverse[row][col] = true;
			} else {
				newUniverse[row][col] = false;
			}
		}
	}

	for(uint16_t row = 0; row < height; row++) {
		for(uint16_t col = 0; col < width; col++) {
			universe[row][col] = newUniverse[row][col];
		}
	}
}

uint8_t GameOfLife::countNeighbors(uint16_t row, uint16_t col) {
	uint8_t alive = 0;
	bool upLeft = row > 0 && col > 0 && universe[row-1][col-1];
	alive += upLeft ? 1 : 0;
	bool upMiddle = row > 0 && universe[row-1][col];
	alive += upMiddle ? 1 : 0;
	bool upRight = row > 0 && col < width-1 && universe[row-1][col+1];
	alive += upRight ? 1 : 0;
	
	bool middleLeft = col > 0 && universe[row][col-1];
	alive += middleLeft ? 1 : 0;
	bool middleRight = col < width-1 && universe[row][col+1];
	alive += middleRight ? 1 : 0;
	
	bool bottomLeft = row < height-1 && col > 0 && universe[row+1][col-1];
	alive += bottomLeft ? 1 : 0;
	bool bottomMiddle = row < height-1 && universe[row+1][col];
	alive += bottomMiddle ? 1 : 0;
	bool bottomRight = row < height-1 && col < width-1 && universe[row+1][col+1];
	alive += bottomRight ? 1 : 0;
	return alive;
}

void GameOfLife::drawCell(Adafruit_ILI9341 &gfx,
		uint16_t row, uint16_t col, uint16_t color) {
	gfx.drawRect(col * size + PAD, row * size + PAD,
		size-PAD*2, size-PAD*2, color);
}
