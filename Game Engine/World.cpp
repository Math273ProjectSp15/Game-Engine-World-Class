#include "World.h"

//Constructor
World::World()
{
	windowRECT_.left = 0;
	windowRECT_.right = GAME_WIDTH;
	windowRECT_.top = GAME_HEIGHT;
	windowRECT_.bottom = 0;

	dxFont_ = new TextDX(); //DirectX Font
	messageY_ = 0;
}


// Destructor
World::~World()
{
	releaseAll();           // call onLostDevice() for every graphics item
	safeDelete(dxFont_);
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
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario entity"));

	//bullets
	//firewave
	if (!fireWave_.initialize(this, &marioTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fireWave entity"));

	if (!fireball_.initialize(this, &marioTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fireball entity"));

	if (!villainBullet_.initialize(this, &villainsTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing villainBullet entity"));

	// initialize DirectX font
	// 18 pixel high Arial
	if (dxFont_->initialize(graphics, 18, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	mario_.setFrames(marioNS::IDLE_MARIO_START_FRAME, marioNS::IDLE_MARIO_END_FRAME);
	mario_.setCurrentFrame(marioNS::IDLE_MARIO_START_FRAME);
	mario_.setY(marioPositionVector_.y);
	mario_.setX(marioPositionVector_.x);
	mario_.setEdge(marioNS::IDLE_RECT);

	withinHorizonalScroll_ = false;
	withinVerticalScroll_ = false;
	distanceToRightEdge = worldWidth_ - (GAME_WIDTH / 2);
	distanceToTopEdge = (GAME_HEIGHT/2) - worldHeight_;
	marioPositionVector_.y = 0;
}

void World::update()      // must override pure virtual from Game
{
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
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
		moveRight = true;
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
		moveRight = true;
	}
	else if (input->isKeyDown(DOWN_KEY) || input->getGamepadDPadDown(0))
	{
		mario_.setState(marioNS::ROLLING);
		mario_.setEdge(marioNS::ROLLING_RECT);
	}
	else if (input->isKeyDown(UP_KEY) )
	{
		mario_.setState(marioNS::JUMPING);
		mario_.setEdge(marioNS::JUMP_UP_RECT);
		moveUp = true;
	}
	else if (input->isKeyDown(F_KEY))
	{
		mario_.setState(marioNS::HORIZONTAL_ATTACK);
	}
	else if (input->isKeyDown(D_KEY))
	{
		mario_.setState(marioNS::CLAW_ATTACK);
		fireWave temp = fireWave_;
		if (mario_.getDirection() == marioNS::LEFT)
		{
			temp.set(mario_.getX(), mario_.getY(), LEFT);
		}
		else if (mario_.getDirection() == marioNS::RIGHT)
		{
			temp.set(mario_.getX(), mario_.getY(), RIGHT);
		}
		fireWaves_.push_back(temp);
	}
	else if (input->isKeyDown(S_KEY))
	{
		mario_.setState(marioNS::SHOOT_ATTACK);
		fireball temp = fireball_;
		if (mario_.getDirection() == marioNS::LEFT)
		{
			temp.set(mario_.getX(), mario_.getY(), LEFT);
		}
		else if (mario_.getDirection() == marioNS::RIGHT)
		{
			temp.set(mario_.getX(), mario_.getY(), RIGHT);
		}
		fireballs_.push_back(temp);
	}
	else
	{
		mario_.setState(marioNS::IDLEING);
		mario_.setEdge(marioNS::IDLE_RECT);
	}
	mario_.update(frameTime);
	
	for (auto villain : villains_)
	{
		villain->update(frameTime, mario_.getX(), mario_.getY());
	}

	//bullets
	for (int i = 0; i < fireWaves_.size(); i++)
	{
		fireWaves_[i].update(frameTime);
	}
	for (int i = 0; i < fireballs_.size(); i++)
	{
		fireballs_[i].update(frameTime);
	}
	for (int i = 0; i < villainBullets_.size(); i++)
	{
		villainBullets_[i].update(frameTime);
	}

	if (moveUp && !marioStuckOnTop_)
	{
		updateScroll();
	}
	else if (moveDown && !marioStuckOnBottom_)
	{
		updateScroll();
	}
	else if (moveRight && !marioStuckOnRight_)
	{
		updateScroll();
	}
	else if (moveLeft && !marioStuckOnLeft_)
	{
		updateScroll();
	}
	else
	{
		updateScroll();
	}

	marioStuckOnTop_ = false;
	marioStuckOnBottom_ = false;
	marioStuckOnRight_ = false;
	marioStuckOnLeft_ = false;

	updateVillainContainer();

}

void World::ai()          // "
{

}

void World::collisions()  // "
{
	bool collisionDetected = false;
	for (int i = 0; i < entities_.size(); i++)
	{
		VECTOR2 cv;
		if (mario_.collidesWith(*entities_[i], cv))
		{
			VECTOR2 standStill = { 0, mario_.getVelocity().y };
			if (mario_.getX() < entities_[i]->getX() - mario_.getWidth() 
				&& mario_.getY() > entities_[i]->getY() - mario_.getHeight() 
				&& mario_.getY() < entities_[i]->getY() + entities_[i]->getHeight())
			{
				mario_.setX(entities_[i]->getX() - mario_.getWidth());
				mario_.setVelocity(standStill);
				marioStuckOnLeft_ = true;
			}
			else if (mario_.getX() > entities_[i]->getX() + entities_[i]->getWidth() 
				&& mario_.getY() > entities_[i]->getY() - mario_.getHeight()
				&& mario_.getY() < entities_[i]->getY() + entities_[i]->getHeight())
			{
				mario_.setX(entities_[i]->getX() + entities_[i]->getWidth());
				mario_.setVelocity(standStill);
				marioStuckOnRight_ = true;
			}
			/*else if (mario_.getX() > entities_[i]->getX() + entities_[i]->getWidth() + mario_.getWidth() / 2 
				&& mario_.getX() > entities_[i]->getX() + entities_[i]->getWidth() + mario_.getWidth() / 2
				&& mario_.getY() > entities_[i]->getY() - mario_.getHeight())
			{

			}*/
			else
			{
				if (mario_.getState() != marioNS::ROLLING)
				{
					mario_.setY(entities_[i]->getY() - mario_.getHeight());
				}
				else
				{
					mario_.setY(entities_[i]->getY() - mario_.getHeight() / 2);
				}

				mario_.setVelocity(standStill);
				mario_.onGround();
				marioStuckOnBottom_ = true;
				collisionDetected = true;
			}
		}

		for (auto villain : villains_)
		{
			VECTOR2 cv;
			if (villain->collidesWith(mario_, cv) && mario_.getState() == marioNS::HORIZONTAL_ATTACK)
			{
				villain->died();
			}

			if (villain->collidesWith(*entities_[i], cv))
			{
				VECTOR2 standStill = { 0, mario_.getVelocity().y };
				villain->setVelocity(standStill);
				villain->setY(entities_[i]->getY() - villain->getVillainHeight());
				villain->onGround();
			}
			else
				villain->notOnGround();
		}
	}
	if (!collisionDetected)
	{
		mario_.notOnGround();
	}
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
	//bullets
	if (!fireWaves_.empty())
	{
		for (int i = 0; i < fireWaves_.size(); i++)
		{
			fireWaves_[i].draw();
		}
	}
	if (!fireballs_.empty())
	{
		for (int i = 0; i < fireballs_.size(); i++)
		{
			fireballs_[i].draw();
		}
	}
	if (!villainBullets_.empty())
	{
		for (int i = 0; i < villainBullets_.size(); i++)
		{
			villainBullets_[i].draw();
		}
	}

	//villains
	if (!villains_.empty())
	{


		for (auto villain : villains_)
		{
			villain->draw();
		}
	}

	dxFont_->setFontColor(graphicsNS::BLACK);
	dxFont_->print(message_, 20, (int)messageY_);


	graphics->spriteEnd();                  // end drawing sprites
}

void World::releaseAll()
{
	dxFont_->onLostDevice();
	marioTexture_.onLostDevice();
	villainsTexture_.onLostDevice();
	Game::releaseAll();
	return;
}

void World::resetAll()
{
	dxFont_->onResetDevice();
	marioTexture_.onResetDevice();
	villainsTexture_.onResetDevice();
	Game::resetAll();
	return;
}


void World::updateScroll()
{
	double scrollX = mario_.getX() - GAME_WIDTH / 2;
	double scrollY = mario_.getY() - GAME_HEIGHT / 2;

	marioPositionVector_.x += scrollX;
	marioPositionVector_.y += scrollY;

	//if (marioPositionVector_.y > 100)
	//	mario_.died();

	//if (mario_.isDead())
	//	resetMarioPosition();


	if (mario_.getY() == ground_[0].getY() - marioNS::HEIGHT)
	{
		marioPositionVector_.y = 0;
	}

	message_ = "X:  ";
	message_ += std::to_string(marioPositionVector_.x);
	message_ += "    Y: ";
	message_ += std::to_string(marioPositionVector_.y);
	message_ += "    X Velocity: ";
	message_ += std::to_string(mario_.getVelocity().x);
	message_ += "    Y Velocity: ";
	message_ += std::to_string(mario_.getVelocity().y);
	message_ += "    TIMER: ";
	message_ += std::to_string(villainTimer_.check());


	if ((marioPositionVector_.x >= GAME_WIDTH / 2) &&
		marioPositionVector_.x <= worldWidth_ - GAME_WIDTH / 2)
		withinHorizonalScroll_ = true;
	else
		withinHorizonalScroll_ = false;

	if (marioPositionVector_.y <= 0 &&
		marioPositionVector_.y >= distanceToTopEdge)
		withinVerticalScroll_ = true;
	else
		withinVerticalScroll_ = false;


	if (withinHorizonalScroll_)
	{
		backgroundImages_[0]->setX(backgroundImages_[0]->getX() - scrollX * 0.40);
		//paralax scrolling 
		backgroundImages_[1]->setX(backgroundImages_[1]->getX() - (scrollX * 0.5));
		backgroundImages_[2]->setX(backgroundImages_[2]->getX() - (scrollX * 0.9));
	}

	if (withinVerticalScroll_)
	{
		backgroundImages_[0]->setY(backgroundImages_[0]->getY() - (scrollY * 0.40));
		//paralax scrolling 
		backgroundImages_[1]->setY(backgroundImages_[1]->getY() - (scrollY * 0.50));
		backgroundImages_[2]->setY(backgroundImages_[2]->getY() - (scrollY * 0.9));
	}

	if (!entities_.empty())
	{
		for (auto entity : entities_)
		{
			if (withinHorizonalScroll_)
				entity->setX(entity->getX() - scrollX);
			if (withinVerticalScroll_)
				entity->setY(entity->getY() - scrollY);
		}
	}

	if (!villains_.empty())
	{
		for (auto villain : villains_)
		{
			if (withinHorizonalScroll_)
				villain->setX(villain->getX() - scrollX);
			if (withinVerticalScroll_)
				villain->setY(villain->getY() - scrollY);
		}
	}

	if (!withinHorizonalScroll_)
	{
		if (marioPositionVector_.x <= 0)
		{
			marioPositionVector_.x = 0;
		}
		else if (marioPositionVector_.x >= worldWidth_ - mario_.getWidth())
		{
			marioPositionVector_.x = worldWidth_ - mario_.getWidth();
		}
	}

	if (marioPositionVector_.y <= 0)
	{
		mario_.setY(GAME_HEIGHT / 2);
	}

	if (withinHorizonalScroll_)
		mario_.setX(GAME_WIDTH / 2);

}

void World::resetMarioPosition()
{
	marioPositionVector_ = marioInitialPositionVector_;
	mario_.undead();
	mario_.resetMario();
}

Villain* World::createVillain()
{
	int selection = randomInteger(0, 5);

	switch(selection)
	{
	case 0:
		return new CyanVillain(this, &villainsTexture_, randomInteger(VILLAIN_EDGE_SPACER, worldWidth_ - VILLAIN_EDGE_SPACER), VILLAIN_DROP_ZONE);
	case 1:
		return new GreenVillain(this, &villainsTexture_, randomInteger(VILLAIN_EDGE_SPACER, worldWidth_ - VILLAIN_EDGE_SPACER), VILLAIN_DROP_ZONE);
	case 2:
		return new PeriwinkleVillain(this, &villainsTexture_, randomInteger(VILLAIN_EDGE_SPACER, worldWidth_ - VILLAIN_EDGE_SPACER), VILLAIN_DROP_ZONE);
	case 3:
		return new PurpleVillain(this, &villainsTexture_, randomInteger(VILLAIN_EDGE_SPACER, worldWidth_ - VILLAIN_EDGE_SPACER), VILLAIN_DROP_ZONE);
	case 4:
		return new RedVillain(this, &villainsTexture_, randomInteger(VILLAIN_EDGE_SPACER, worldWidth_ - VILLAIN_EDGE_SPACER), VILLAIN_DROP_ZONE);
	case 5:
		return new YellowVillain(this, &villainsTexture_, randomInteger(VILLAIN_EDGE_SPACER, worldWidth_ - VILLAIN_EDGE_SPACER), VILLAIN_DROP_ZONE);
	}
	return new CyanVillain(this, &villainsTexture_, randomInteger(VILLAIN_EDGE_SPACER, worldWidth_ - VILLAIN_EDGE_SPACER), VILLAIN_DROP_ZONE);
}

void World::updateVillainContainer()
{
	int deadCount = 0;

	if (!villains_.empty())
	{
		auto villain = std::begin(villains_);
		while (villain != std::end(villains_))
		{
			if ((*villain)->isDead() && (*villain)->animationComplete())
			{
				delete (*villain);
				villain = villains_.erase(villain);
				deadCount++;
			}
			else
				++villain;
		}

		if (villainTimer_.check() > VILLAIN_SPAWN_TIME)
		{
			villains_.push_back(createVillain());
			villainTimer_.reset();
		}
	}
	else 
		villains_.push_back(createVillain());
}