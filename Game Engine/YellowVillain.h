#pragma once
#include "Villain.h"

namespace yellowVillainNS
{
	const int WIDTH = 256;                   // image width
	const int HEIGHT = 128;                  // image height
	const int TEXTURE_COLS = 5; 
	const int START_FRAME = 0; 
	const int END_FRAME = 8;  
	const double ANIMATION_DELAY = 0.1;
	const float SPEED = 90;                // pixels per second
	const float MASS = 1.0e6f;

	//Collision RECTS      left, top, right, bottom
	const RECT EDGE_RECT = { -77, -128, 76, 128 };
}

class YellowVillain : public Villain
{
public:
	YellowVillain(Game *gamePtr, TextureManager *textureM, int X, int Y);
	// inherited member functions
	virtual bool initialize(Game *gamePtr, TextureManager *textureM);
	int getVillainHeight() { return 128; }
};