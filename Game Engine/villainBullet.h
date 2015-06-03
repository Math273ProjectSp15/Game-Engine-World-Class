#pragma once
#include "Entity.h" 
#include "constants.h"

namespace villainBulletNS
{
	const int WIDTH = 256;
	const int HEIGHT = 128;
	const int COLUMNS = 1;
	const int START_FRAME = 11;
	const int END_FRAME = 11;
	const int LEFT_RIGHT_SPACER = 20;
	const int ANIMATION_DELAY = 0.1;
	const float SPEED = 250;
	const RECT VILLAIN_BULLET_EDGE = { -(WIDTH / 2 - LEFT_RIGHT_SPACER), -(HEIGHT / 2),
		WIDTH / 2 - LEFT_RIGHT_SPACER, HEIGHT / 2 };
}

class villainBullet : public Entity
{
public:
	bool initialize(Game *gamePtr, TextureManager *textureM);
	void set(int x, int y, Direction dirc);
	void update(float frameTime);
};