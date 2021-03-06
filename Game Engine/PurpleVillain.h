#pragma once
#include "Villain.h"

namespace purpleVillainNS
{
	const int WIDTH = 256;                   // image width
	const int HEIGHT = 128;                  // image height
	const int TEXTURE_COLS = 5;
	const int START_FRAME = 40;
	const int END_FRAME = 44;
	const double ANIMATION_DELAY = 0.1;
	const float SPEED = 90;                // pixels per second
	const float MASS = 1.0e6f;

	//Collision RECTS      left, top, right, bottom
	const RECT EDGE_RECT = { -69, -128, 69, 256 };
}

class PurpleVillain : public Villain
{
public:
	PurpleVillain(Game *gamePtr, TextureManager *textureM, int X, int Y);
	// inherited member functions
	bool initialize(Game *gamePtr, TextureManager *textureM);
    int getVillainHeight() { return 256; }

};