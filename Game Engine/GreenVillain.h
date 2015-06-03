#pragma once
#include "Villain.h"

namespace greenVillainNS
{
	const int WIDTH = 256;                   // image width
	const int HEIGHT = 128;                  // image height
	const int TEXTURE_COLS = 5;
	const int START_FRAME = 20;
	const int END_FRAME = 28;
	const double ANIMATION_DELAY = 0.1;
	const float SPEED = 90;                // pixels per second
	const float MASS = 1.0e6f;

	//Collision RECTS      left, top, right, bottom
	const RECT EDGE_RECT = { -64, -128, 64, 128 };
}

class GreenVillain : public Villain
{
public:
	// inherited member functions
	bool initialize(Game *gamePtr, TextureManager *textureM);
	//int getVillainHeight() { return 128; }
};