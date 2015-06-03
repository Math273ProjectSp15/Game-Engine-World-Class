#include "Villain.h"


bool Villain::initialize(Game *gamePtr, TextureManager *textureM)
{
	deadImage_.initialize(gamePtr->getGraphics(), villainNS::WIDTH, villainNS::HEIGHT, villainNS::TEXTURE_COLS, textureM);
	deadImage_.setFrames(villainNS::START_FRAME, villainNS::END_FRAME);
	deadImage_.setCurrentFrame(villainNS::START_FRAME);
	deadImage_.setFrameDelay(villainNS::ANIMATION_DELAY);
	deadImage_.setLoop(false);

	onGround_ = false;
	dead_ = false;

	return true;
}

void Villain::update(float frameTime, int marioX, int marioY)
{
	if (dead_)
		deadImage_.update(frameTime);
	else
	{

		if (!isOnGround())
		{
			velocity.y += frameTime * 3 * GRAVITY;
		}
		else
		{
			velocity.y = 0;
		}
		spriteData.y += velocity.y * frameTime;

		if (marioX < spriteData.x)
		{
			flipHorizontal(false);
			velocity.x = -abs(villainNS::SPEED);
		}
		else
		{
			flipHorizontal(true);
			velocity.x = abs(villainNS::SPEED);
		}
		spriteData.x += velocity.x * frameTime;

		Entity::update(frameTime);
	}

}

void Villain::draw()
{
	if (dead_)
	{
		deadImage_.draw(spriteData);
	}
	else
	{
		Image::draw();
	}

}


bool Villain::animationComplete()
{
	return deadImage_.getAnimationComplete();
}