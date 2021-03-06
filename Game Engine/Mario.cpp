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

	clawAttack_.initialize(gamePtr->getGraphics(), marioNS::CLAW_ATTACK_IMAGE_WIDTH,
		marioNS::CLAW_ATTACK_IMAGE_HEIGHT, marioNS::CLAW_ATTACK_TEXTURE_COLS, textureM);
	clawAttack_.setFrames(marioNS::CLAW_ATTACK_START_FRAME, marioNS::CLAW_ATTACK_END_FRAME);
	clawAttack_.setCurrentFrame(marioNS::CLAW_ATTACK_START_FRAME);
	clawAttack_.setFrameDelay(marioNS::CLAW_ATTACK_ANIMATION_DELAY);

	shootAttack_.initialize(gamePtr->getGraphics(), marioNS::SHOOT_ATTACK_IMAGE_WIDTH,
		marioNS::SHOOT_ATTACK_IMAGE_HEIGHT, marioNS::SHOOT_ATTACK_TEXTURE_COLS, textureM);
	shootAttack_.setFrames(marioNS::SHOOT_ATTACK_START_FRAME, marioNS::SHOOT_ATTACK_END_FRAME);
	shootAttack_.setCurrentFrame(marioNS::SHOOT_ATTACK_START_FRAME);
	shootAttack_.setFrameDelay(marioNS::SHOOT_ATTACK_ANIMATION_DELAY);

	dying_.initialize(gamePtr->getGraphics(), marioNS::DYING_IMAGE_WIDTH,
		marioNS::DYING_IMAGE_HEIGHT, marioNS::DYING_TEXTURE_COLS, textureM);
	dying_.setFrames(marioNS::DYING_IMAGE_START_FRAME, marioNS::DYING_IMAGE_END_FRAME);
	dying_.setCurrentFrame(marioNS::DYING_IMAGE_START_FRAME);
	dying_.setFrameDelay(marioNS::DYING_IMAGE_ANIMATION_DELAY);

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

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH)  // if hit right map edge
	{
		spriteData.x = GAME_WIDTH;
		velocity.x = 0;
	} 
	else if (spriteData.x < 0)                       // else if hit left map edge
	{
		spriteData.x = 0;
		velocity.x = 0;
	}

	setEdge(marioNS::IDLE_RECT);

	if (getState() == marioNS::IDLEING)
	{

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
			velocity.y = -6 * marioNS::SPEED;
			notOnGround();
		}
	}
	else if (getState() == marioNS::HORIZONTAL_ATTACK)
	{
		horizontalAttack_.update(frameTime);
		setEdge(marioNS::HORIZONTAL_ATTACK_RECT);
	}
	else if (getState() == marioNS::CLAW_ATTACK)
	{
		clawAttack_.update(frameTime);
	}
	else if (getState() == marioNS::SHOOT_ATTACK)
	{
		shootAttack_.update(frameTime);
	}
	else if (getState() == marioNS::DYING)
	{
		dying_.update(frameTime);
	}

	if (!isOnGround())
	{
		velocity.y += frameTime * 3 * GRAVITY;
	}
	else
	{
		velocity.y = 0;
	}

	spriteData.y += velocity.y * frameTime;
	spriteData.x += velocity.x * frameTime;
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
	else if (state_ == marioNS::CLAW_ATTACK)
	{
		clawAttack_.draw(spriteData);
	}
	else if (state_ == marioNS::SHOOT_ATTACK)
	{
		shootAttack_.draw(spriteData);
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

