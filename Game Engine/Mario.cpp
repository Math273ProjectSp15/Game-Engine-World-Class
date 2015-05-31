#include "Mario.h"

Mario::Mario() : Entity()
{
	spriteData.width = marioNS::WIDTH ;         // size of Mario
	spriteData.height = marioNS::HEIGHT;
	spriteData.x = marioNS::X;                 // location on screen
	spriteData.y = marioNS::Y;
	spriteData.rect.bottom = marioNS::HEIGHT;  // rectangle to select parts of an image
	spriteData.rect.right = marioNS::WIDTH;
	frameDelay = 0.1;
	startFrame = 0;                             // first frame of animation
	endFrame = 0;                           // last frame of animation
	currentFrame = startFrame;
	edge.top = -marioNS::HEIGHT / 2 ;             // set collision edges
	edge.bottom = marioNS::HEIGHT / 2 ;
	edge.left = -marioNS::WIDTH / 2 ;
	edge.right = marioNS::WIDTH / 2 ;

	collisionType = entityNS::BOX;
	mass = marioNS::MASS;

	velocity.x = 0;
	velocity.y = 0;

	state_ = marioNS::IDLEING;
	direction_ = marioNS::RIGHT;
	onGround();
	dead_ = false;
}

//=============================================================================
// Initialize Mario.
// Post: returns true if successful, false if failed
//=============================================================================
bool Mario::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	marioWalking_.initialize(gamePtr->getGraphics(), marioNS::WALKING_IMAGE_WIDTH, 
		marioNS::WALKING_IMAGE_HEIGHT, marioNS::WALKING_TEXTURE_COLS, textureM);

	marioWalking_.setFrames(marioNS::WALKING_MARIO_START_FRAME, marioNS::WALKING_MARIO_END_FRAME);
	marioWalking_.setCurrentFrame(marioNS::WALKING_MARIO_START_FRAME);
	marioWalking_.setFrameDelay(marioNS::WALKING_ANIMATION_DELAY);

	marioRolling_.initialize(gamePtr->getGraphics(), marioNS::ROLLING_IMAGE_WIDTH,
		marioNS::ROLLING_IMAGE_HEIGHT, marioNS::ROLLING_TEXTURE_COLS, textureM);
	marioRolling_.setFrames(marioNS::ROLLING_MARIO_START_FRAME, marioNS::ROLLING_MARIO_END_FRAME);
	marioRolling_.setCurrentFrame(marioNS::ROLLING_MARIO_START_FRAME);
	marioRolling_.setFrameDelay(marioNS::ROLLING_ANIMATION_DELAY);

	marioJumpUp_.initialize(gamePtr->getGraphics(), marioNS::JUMP_UP_IMAGE_WIDTH,
		marioNS::JUMP_UP_IMAGE_HEIGHT, marioNS::JUMP_UP_TEXTURE_COLS, textureM);
	marioJumpUp_.setFrames(marioNS::JUMP_UP_MARIO_START_FRAME, marioNS::JUMP_UP_MARIO_END_FRAME);
	marioJumpUp_.setCurrentFrame(marioNS::JUMP_UP_MARIO_START_FRAME);
	marioJumpUp_.setFrameDelay(marioNS::JUMP_UP_ANIMATION_DELAY);

	marioJumpFall_.initialize(gamePtr->getGraphics(), marioNS::JUMP_FALL_IMAGE_WIDTH,
		marioNS::JUMP_FALL_IMAGE_HEIGHT, marioNS::JUMP_FALL_TEXTURE_COLS, textureM);
	marioJumpFall_.setFrames(marioNS::JUMP_FALL_MARIO_START_FRAME, marioNS::JUMP_FALL_MARIO_END_FRAME);
	marioJumpFall_.setCurrentFrame(marioNS::JUMP_FALL_MARIO_START_FRAME);
	marioJumpFall_.setFrameDelay(marioNS::JUMP_FALL_ANIMATION_DELAY);

	horizontalAttack_.initialize(gamePtr->getGraphics(), marioNS::HORIZONTAL_ATTACK_IMAGE_WIDTH,
		marioNS::HORIZONTAL_ATTACK_IMAGE_HEIGHT, marioNS::HORIZONTAL_ATTACK_TEXTURE_COLS, textureM);
	horizontalAttack_.setFrames(marioNS::HORIZONTAL_ATTACK_START_FRAME, marioNS::HORIZONTAL_ATTACK_END_FRAME);
	horizontalAttack_.setCurrentFrame(marioNS::HORIZONTAL_ATTACK_START_FRAME);
	horizontalAttack_.setFrameDelay(marioNS::HORIZONTAL_ATTACK_ANIMATION_DELAY);

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Mario::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.y += velocity.y * frameTime;

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH)  // if hit right map edge
	{
		spriteData.x = GAME_WIDTH;
		velocity.x = 0;
	} 
	else if (spriteData.x < 50)                       // else if hit left map edge
	{
		spriteData.x = 50;
		velocity.x = 0;
		velocity.y = 0;
	}
	else if (spriteData.y > GROUND_Y_POSITION) // else if below ground
	{
	//	spriteData.y = GAME_HEIGHT - backgroundNS::GROUND_HEIGHT - marioNS::HEIGHT;
	//	onGround();
		marioDied();
	}

	if (getState() == marioNS::IDLEING)
	{
		setFrames(marioNS::IDLE_MARIO_START_FRAME, marioNS::IDLE_MARIO_END_FRAME);
		//if (spriteData.y == GAME_HEIGHT - backgroundNS::GROUND_HEIGHT - marioNS::HEIGHT)
		//{
		//	velocity.x = 0;
		//}
	}
	else if (getState() == marioNS::WALKING)
	{
		if (getDirection() != marioNS::RIGHT)
		{
			flipHorizontal(true);
			velocity.x = -abs(marioNS::SPEED);
		}
		else if (getDirection() == marioNS::RIGHT)
		{
			flipHorizontal(false);
			velocity.x = abs(marioNS::SPEED);
		}
		marioWalking_.update(frameTime);
	}
	else if (getState() == marioNS::ROLLING)
	{
		spriteData.y = (spriteData.y + getHeight()) - marioNS::ROLLING_IMAGE_HEIGHT;
		if (getDirection() == marioNS::LEFT)
		{
			flipHorizontal(true);
			velocity.x = -abs(marioNS::SPEED);
		}
		else if (getDirection() == marioNS::RIGHT)
		{
			flipHorizontal(false);
			velocity.x = abs(marioNS::SPEED);
		}
		marioRolling_.update(frameTime);
	}
	else if (getState() == marioNS::JUMPING)
	{
		if (isOnGround())
		{
			velocity.y = -4 * marioNS::SPEED;
			notOnGround();
		}
		//if (spriteData.y == GAME_HEIGHT - backgroundNS::GROUND_HEIGHT - marioNS::HEIGHT)
		//{
		//	velocity.y = -4 * marioNS::SPEED;
		//}
	}
	if (!isOnGround())
		velocity.y += frameTime * 3 * GRAVITY;
	else
		velocity.y = 0;
}

//=============================================================================
// draw the different mario states
//=============================================================================
void Mario::draw()
{
	if (state_ == marioNS::WALKING)
	{
		marioWalking_.draw(spriteData);
	}
	else if (state_ == marioNS::ROLLING)
	{
		marioRolling_.draw(spriteData);
	}
	else if (state_ == marioNS::JUMPING)
	{
		if (velocity.y < 0)
			marioJumpUp_.draw(spriteData);
		else
			marioJumpFall_.draw(spriteData);
	}
	else if (state_ == marioNS::HORIZONTAL_ATTACK)
	{
		horizontalAttack_.draw(spriteData);
	}
	else
	{
		Image::draw();
	}

}

void Mario::setState(marioNS::State state)
{
	state_ = state;
}

marioNS::State Mario::getState()
{
	return state_;
}

void Mario::setDirection(marioNS::Direction direction)
{
	direction_ = direction;
}

marioNS::Direction Mario::getDirection()
{
	return direction_;
}

int Mario::getMarioWidth()
{
	if (state_ == marioNS::WALKING)
	{
		return marioWalking_.getWidth();
	}
	else if (state_ == marioNS::ROLLING)
	{
		return marioRolling_.getWidth();
	}
	else if (state_ == marioNS::JUMPING)
	{
		if (velocity.y < 0)
			return marioJumpUp_.getWidth();
		else
			return marioJumpFall_.getWidth();
	}
	else
	{
		return Image::getWidth();
	}
}

void Mario::resetMario()
{ 
	spriteData.x = marioNS::X;                 // location on screen
	spriteData.y = marioNS::Y;
	velocity.x = 0;
	velocity.y = 0;
	onGround();
}

