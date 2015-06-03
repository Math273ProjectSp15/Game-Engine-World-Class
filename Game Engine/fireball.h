#pragma once
#include "entity.h"
#include "constants.h"

namespace fireballNS
{
	const int WIDTH = 256;
	const int HEIGHT = 128;
	const int COLUMNS = 4;
	const int START_FRAME = 56;
	const int END_FRAME = 59;
	const int LEFT_RIGHT_SPACER = 28;
	const int ANIMATION_DELAY = 0.1;
	const float SPEED = 250;
	const RECT FIREBALL_EDGE = { -(WIDTH / 2 - LEFT_RIGHT_SPACER), -(HEIGHT / 2),
		WIDTH / 2 - LEFT_RIGHT_SPACER, HEIGHT / 2 };
}

class fireball : public Entity
{
public:
	bool initialize(Game *gamePtr, TextureManager *textureM);
	void set(int x, int y, Direction dirc);
	void update(float frameTime);
};