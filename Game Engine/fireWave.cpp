#include "fireWave.h"

bool fireWave::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, fireWaveNS::WIDTH, fireWaveNS::HEIGHT, fireWaveNS::COLUMNS, textureM);
	setFrames(fireWaveNS::START_FRAME, fireWaveNS::END_FRAME);
	setCurrentFrame(fireWaveNS::START_FRAME);
	setFrameDelay(fireWaveNS::ANIMATION_DELAY);
	setVelocity({ fireWaveNS::SPEED, 0 });
	setEdge(fireWaveNS::FIREWAVE_EDGE);
	return true;
}

void fireWave::set(int x, int y, Direction dirc)
{
	
	if (dirc == RIGHT)
	{
		setX(x + marioNS::WALKING_IMAGE_WIDTH / 1.5);
		setY(y - 20);
	}
	else
	{
		setX(x - marioNS::WALKING_IMAGE_WIDTH / 1.5);
		setY(y - 20);
		flipHorizontal(true);
		setVelocity(-getVelocity());
	}
}

void fireWave::update(float frameTime)
{
	spriteData.x += velocity.x * frameTime;
}