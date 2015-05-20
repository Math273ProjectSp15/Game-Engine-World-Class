#include "World.h"

//Constructor
World::World()
{

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
	// mario_
	if (!mario_.initialize(this, marioNS::WIDTH, marioNS::HEIGHT, marioNS::TEXTURE_COLS, &marioTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario texture"));

	mario_.setFrames(marioNS::IDLE_MARIO_START_FRAME, marioNS::IDLE_MARIO_END_FRAME);
	mario_.setCurrentFrame(marioNS::IDLE_MARIO_START_FRAME);
	mario_.setY(marioPositionVector_.y);
	mario_.setX(marioPositionVector_.x);
	mario_.setEdge(marioNS::IDLE_RECT);
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
	else
	{
		mario_.setState(marioNS::IDLEING);
		mario_.setEdge(marioNS::IDLE_RECT);
	}
	mario_.update(frameTime);
	updateScroll();
	updateWindow();
}

void World::ai()          // "
{

}

void World::collisions()  // "
{
	for (auto entity : entities_)
	{
		VECTOR2 cv;
		if (mario_.collidesWith(*entity, cv))
		{
			VECTOR2 standStill = { 0, mario_.getVelocity().y };
			//mario_.bounce(cv, *entity);
			mario_.setY(entity->getY() - mario_.getHeight());
			mario_.setVelocity(standStill);
			mario_.onGround = true;
		}
	}
}

void World::render()      // "
{
	graphics->spriteBegin();                // begin drawing sprites

	backgroundImages_[0]->draw();                     // add the background to the scene
	mario_.draw();                          // add mario to the scene

	//Draw entities that are within the bounds of the window
	if (!entities_.empty())
	{
		for (auto entity : entities_)
		{
			//if ((entity->getX() > windowRECT_.left - entity->getWidth() && entity->getX() < windowRECT_.right) &&
			//	(entity->getY() > windowRECT_.top - entity->getHeight() && entity->getY() < windowRECT_.bottom))
			//{
			//	entity->draw();
			//}
			entity->draw();
		}
	}

	graphics->spriteEnd();                  // end drawing sprites
}

void World::releaseAll()
{
	marioTexture_.onLostDevice();
	Game::releaseAll();
	return;
}

void World::resetAll()
{
	marioTexture_.onResetDevice();
	Game::resetAll();
	return;
}

void World::updateWindow()
{
	windowRECT_.left = marioPositionVector_.x - (GAME_WIDTH / 2 - mario_.getMarioWidth());
	windowRECT_.right = windowRECT_.left + GAME_WIDTH;
	//May need to change the mario_.getHeight() function, although all images are the same height
	windowRECT_.top = marioPositionVector_.y - (GAME_HEIGHT / 2 - mario_.getHeight());
	windowRECT_.bottom = windowRECT_.top + GAME_HEIGHT;

	if (marioPositionVector_.x < GAME_WIDTH / 2 - mario_.getMarioWidth() / 2)
	{
		windowRECT_.left = 0;
		windowRECT_.right = GAME_WIDTH;
	}

	if (marioPositionVector_.x > worldWidth_ - GAME_WIDTH / 2 - mario_.getMarioWidth() / 2)
	{
		windowRECT_.right = worldWidth_;
		windowRECT_.left = windowRECT_.right - GAME_WIDTH;
	}

	if (marioPositionVector_.y < GAME_HEIGHT / 2 - mario_.getHeight() / 2)
	{
		windowRECT_.top = 0;
		windowRECT_.bottom = GAME_HEIGHT;
	}

	if (marioPositionVector_.y > worldHeight_ - GAME_HEIGHT / 2 - mario_.getHeight() / 2)
	{
		windowRECT_.top = worldHeight_ - GAME_HEIGHT;
		windowRECT_.bottom = worldHeight_;
	}

}

void World::updateScroll()
{
	static const int distanceToRightEdge = worldWidth_ - (GAME_WIDTH / 2);
	marioPositionVector_.x += frameTime * mario_.getVelocity().x;

	if (marioPositionVector_.x >= (GAME_WIDTH / 2 + worldNS::EDGE_SPACER) && marioPositionVector_.x <= distanceToRightEdge - worldNS::EDGE_SPACER)
	{
		backgroundImages_[0]->setX(backgroundImages_[0]->getX() - frameTime * mario_.getVelocity().x);

		if (!entities_.empty())
		{
			for (auto entity : entities_)
			{
				entity->setX(entity->getX() - frameTime * mario_.getVelocity().x);
				//entity.second->setY(entity.second->getY() + scrollVector_.y);
			}
		}

		if (!villains_.empty())
		{
			for (auto villain : villains_)
			{
				villain->setX(villain->getX() - frameTime * mario_.getVelocity().x);
				//villain.second->setY(villain.second->getY() + scrollVector_.y);
			}
		}
	}
	else
	{
		mario_.setX(mario_.getX() + frameTime * mario_.getVelocity().x);
	}



}