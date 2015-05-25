#pragma once
#include "Entity.h"

namespace purpleVillainNS
{
	const int WIDTH = 256;                   // image width
	const int HEIGHT = 128;                  // image height
	const int TEXTURE_COLS = 5;
	const int START_FRAME = 40;
	const int END_FRAME = 44;
	const double ANIMATION_DELAY = 0.1;
	const float SPEED = 200;                // pixels per second
	const float MASS = 1.0e6f;

	//Collision RECTS      left, top, right, bottom
	const RECT EDGE_RECT = { -69, -128, 69, 128 };
}

class PurpleVillain : public Entity
{
public:
	// inherited member functions
	bool initialize(Game *gamePtr, TextureManager *textureM);
};