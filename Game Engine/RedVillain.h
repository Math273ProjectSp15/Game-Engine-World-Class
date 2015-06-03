#pragma once
#include "Villain.h"

namespace redVillainNS
{
	const int WIDTH = 256;                   // image width
	const int HEIGHT = 128;                  // image height
	const int TEXTURE_COLS = 5;
	const int START_FRAME = 45;
	const int END_FRAME = 49;
	const double ANIMATION_DELAY = 0.1;
	const float SPEED = 90;                // pixels per second
	const float MASS = 1.0e6f;

	//Collision RECTS      left, top, right, bottom
	const RECT EDGE_RECT = { -64, -128, 64, 256 };
}

class RedVillain : public Villain
{
public:
	RedVillain(Game *gamePtr, TextureManager *textureM, int X, int Y);
	// inherited member functions
	bool initialize(Game *gamePtr, TextureManager *textureM);
	int getVillainHeight() { return 256; }
};