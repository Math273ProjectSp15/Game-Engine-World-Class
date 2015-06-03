#pragma once
#include "Entity.h"
#include "constants.h"

namespace fireWaveNS
{
	const int WIDTH = 128;
	const int HEIGHT = 256;
	const int COLUMNS = 13;
	const int START_FRAME = 25;
	const int END_FRAME = 25;
	const int TOP_BOTTOM_SPACER = 28;
	const int ANIMATION_DELAY = 0.1;
	const float SPEED = 250;
	const RECT FIREWAVE_EDGE = { -(WIDTH / 2), -(HEIGHT / 2 - TOP_BOTTOM_SPACER),
		WIDTH / 2, HEIGHT / 2 - TOP_BOTTOM_SPACER };

}

class fireWave : public Entity
{
public:
	bool initialize(Game *gamePtr, TextureManager *textureM);
	void set(int x, int y, Direction dirc);
	void update(float frameTime);
};
