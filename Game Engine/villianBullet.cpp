#include "villainBullet.h"

bool villainBullet::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, villainBulletNS::WIDTH, villainBulletNS::HEIGHT, villainBulletNS::COLUMNS, textureM);
	setFrames(villainBulletNS::START_FRAME, villainBulletNS::END_FRAME);
	setCurrentFrame(villainBulletNS::START_FRAME);
	setFrameDelay(villainBulletNS::ANIMATION_DELAY);
	setVelocity({ villainBulletNS::SPEED, 0 });
	setEdge(villainBulletNS::VILLAIN_BULLET_EDGE);
	return true;
}

void villainBullet::set(int x, int y, Direction dirc)
{
	setX(x);
	setY(y);
	if (dirc == RIGHT)
	{

	}
	else
	{
		flipHorizontal(true);
	}
}


void villainBullet::update(float frameTime)
{
	spriteData.x += velocity.x * frameTime;
}