#include "World.h"

//Constructor
World::World()
{
	windowRECT_.left = 0;
	windowRECT_.right = GAME_WIDTH;
	windowRECT_.top = GAME_HEIGHT;
	windowRECT_.bottom = 0;
}


// Destructor
World::~World()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

// Initialize the game
void World::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	// mario_ texture
	if (!marioTexture_.initialize(graphics, DARK_MARIO_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario_ texture"));
	// Villains texture
	if (!villainsTexture_.initialize(graphics, VILLAINS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario_ texture"));
	// mario_
	if (!mario_.initialize(this, marioNS::WIDTH, marioNS::HEIGHT, marioNS::TEXTURE_COLS, &marioTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario texture"));

	mario_.setFrames(marioNS::IDLE_MARIO_START_FRAME, marioNS::IDLE_MARIO_END_FRAME);
	mario_.setCurrentFrame(marioNS::IDLE_MARIO_START_FRAME);
	mario_.setY(marioPositionVector_.y);
	mario_.setX(marioPositionVector_.x);
	mario_.setEdge(marioNS::IDLE_RECT);

	distanceToRightEdge = worldWidth_ - (GAME_WIDTH / 2);
}

void World::update()      // must override pure virtual from Game
{

	if (input->isKeyDown(LEFT_KEY) || input->getGamepadDPadLeft(0))
	{
		mario_.setDirection(marioNS::LEFT);
		mario_.setState(marioNS::WALKING);
		mario_.setEdge(marioNS::RUN_RECT);
		if (input->isKeyDown(UP_KEY))
		{
			mario_.setState(marioNS::JUMPING);
			mario_.setEdge(marioNS::JUMP_UP_RECT);
		}
	}
	else if (input->isKeyDown(RIGHT_KEY) && !input->isKeyDown(DOWN_KEY) || input->getGamepadDPadRight(0))
	{
		mario_.setDirection(marioNS::RIGHT);
		mario_.setState(marioNS::WALKING);
		mario_.setEdge(marioNS::RUN_RECT);
		if (input->isKeyDown(UP_KEY))
		{
			mario_.setState(marioNS::JUMPING);
			mario_.setEdge(marioNS::JUMP_UP_RECT);
		}
	}
	else if (input->isKeyDown(DOWN_KEY) || input->getGamepadDPadDown(0))
	{
		mario_.setState(marioNS::ROLLING);
		mario_.setEdge(marioNS::ROLLING_RECT);
	}
	else if (input->isKeyDown(UP_KEY) || input->getGamepadDPadUp(0))
	{
		mario_.setState(marioNS::JUMPING);
		mario_.setEdge(marioNS::JUMP_UP_RECT);
	}
	else if (input->isKeyDown(ALT_KEY))
	{
		mario_.setState(marioNS::HORIZONTAL_ATTACK);
	}
	else
	{
		mario_.setState(marioNS::IDLEING);
		mario_.setEdge(marioNS::IDLE_RECT);
	}
	mario_.update(frameTime);
	villains_[0]->update(frameTime);
	updateScroll();
}

void World::ai()          // "
{

}

void World::collisions()  // "
{
	bool collisionDetected = false;
	for (auto entity : entities_)
	{
		VECTOR2 cv ;
		if (mario_.collidesWith(*entity, cv))
		{
			VECTOR2 standStill = { 0, mario_.getVelocity().y };
			/*if (mario_.getX() < entity->getX() && mario_.getY() > entity->getY() - mario_.getHeight())
			{
				mario_.setX(entity->getX() - mario_.getWidth());
				mario_.setVelocity(standStill);
			}
			else*/
				mario_.setY(entity->getY() - mario_.getHeight());
			mario_.setVelocity(standStill);
			mario_.onGround();
			collisionDetected = true;
		}
	}
	if (!collisionDetected)
		mario_.notOnGround();
}

void World::render()      // "
{
	graphics->spriteBegin();                // begin drawing sprites


	if (!backgroundImages_.empty())
	{
		for (auto background : backgroundImages_)
		{
			background->draw();
		}
	}


	mario_.draw();                          // add mario to the scene

	//Draw entities that are within the bounds of the window
	if (!entities_.empty())
	{
		for (auto entity : entities_)
		{
			if ((entity->getX() + entity->getWidth() > windowRECT_.left  && entity->getX() < windowRECT_.right)) //TODO: Fix this code&& (entity->getY() > windowRECT_.top - entity->getHeight() && entity->getY() < windowRECT_.bottom))
			{
				entity->draw();
			}
		}
	}

	if (!villains_.empty())
	{
		for (auto villain : villains_)
		{
			villain->draw();
		}
	}

	graphics->spriteEnd();                  // end drawing sprites
}

void World::releaseAll()
{
	marioTexture_.onLostDevice();
	villainsTexture_.onLostDevice();
	Game::releaseAll();
	return;
}

void World::resetAll()
{
	marioTexture_.onResetDevice();
	villainsTexture_.onResetDevice();
	Game::resetAll();
	return;
}


void World::updateScroll()
{
	double scrollX = frameTime * mario_.getVelocity().x;
	double scrollY = frameTime * mario_.getVelocity().y;
	marioPositionVector_.x += scrollX;
	marioPositionVector_.y += scrollY;

	//TODO: Add in this effect for the y direction.  Should only scroll in y direction if within its bounds. 
	if (marioPositionVector_.x >= (GAME_WIDTH / 2 + worldNS::EDGE_SPACER) && marioPositionVector_.x <= distanceToRightEdge - worldNS::EDGE_SPACER)
	{
		backgroundImages_[0]->setX(backgroundImages_[0]->getX() - scrollX * 0.25);
		//paralax scrolling 
		backgroundImages_[1]->setX(backgroundImages_[1]->getX() - (scrollX * 0.5));

		if (!entities_.empty())
		{
			for (auto entity : entities_)
			{
				entity->setX(entity->getX() - scrollX);
				//entity.second->setY(entity.second->getY() + scrollVector_.y);
			}
		}

		//if (!villains_.empty())
		//{
		//	for (auto villain : villains_)
		//	{
		//		villain->setX(villain->getX() - scrollX);
		//		//villain.second->setY(villain.second->getY() + scrollVector_.y);
		//	}
		//}

	}
	else
	{
		mario_.setX(mario_.getX() + frameTime * mario_.getVelocity().x);
	}



}

void World::resetMarioPosition()
{
	marioPositionVector_ = marioInitialPositionVector_;
	mario_.resetMario();
}