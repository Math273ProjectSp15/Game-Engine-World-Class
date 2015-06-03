#include "fireball.h"

bool fireball::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, fireballNS::WIDTH, fireballNS::HEIGHT, fireballNS::COLUMNS, textureM);
	setFrames(fireballNS::START_FRAME, fireballNS::END_FRAME);
	setCurrentFrame(fireballNS::START_FRAME);
	setFrameDelay(fireballNS::ANIMATION_DELAY);
	setVelocity({ fireballNS::SPEED, 0 });
	setEdge(fireballNS::FIREBALL_EDGE);
	return true;
}

void fireball::set(int x, int y, Direction dirc)
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


void fireball::update(float frameTime)
{
	spriteData.x += velocity.x * frameTime ;
}