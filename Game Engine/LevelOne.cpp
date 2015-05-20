#include "LevelOne.h"

LevelOne::LevelOne()
{
	worldWidth_ = levelOneNS::worldWidth;
	worldHeight_ = levelOneNS::worldHeight;
	marioPositionVector_.x = levelOneNS::marioInitialPositionX;
	marioPositionVector_.y = levelOneNS::marioInitialPositionY;
}

LevelOne::~LevelOne()
{

}

void LevelOne::initialize(HWND hwnd)
{
	World::initialize(hwnd);
	// background_ texture
	if (!backgroundTexture_.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background_ texture"));

	// platform_ texture
	if (!platformTexture_.initialize(graphics, PLATFORM_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform_ texture"));

	// background_
	if (!background_.initialize(graphics, 0, 0, 0, &backgroundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	background_.setY((float)GAME_HEIGHT - (float)MAP_HEIGHT);

	if (!platform_.initialize(this, PLATFORM_WIDTH, PLATFORM_HEIGHT, PLATFORM_COLUMNS, &platformTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform texture"));

	platform_.setFrames(PLATFORM_START_FRAME, PLATFORM_END_FRAME);
	platform_.setX(mario_.getX() + mario_.getWidth() + 250);
	platform_.setY(mario_.getY() + 100);
	RECT platformRECT;
	platformRECT.left = -PLATFORM_WIDTH / 2;
	platformRECT.top = -PLATFORM_HEIGHT / 2;
	platformRECT.right = PLATFORM_WIDTH / 2;
	platformRECT.bottom = PLATFORM_HEIGHT / 2;
	platform_.setEdge(platformRECT);
	platform_.setCollisionType(entityNS::BOX);

	entities_.push_back(&platform_);

	//Fill World containers with references to Image and Entity objects.
	backgroundImages_.push_back(&background_);

	return;
}
//
//void LevelOne::update()
//{
//	World::update();
//}
//
//void LevelOne::ai()
//{
//	World::ai();
//}
//
//void LevelOne::collisions()
//{
//	World::collisions();
//}
//
//void LevelOne::render()
//{
//	World::render();
//}
void LevelOne::releaseAll()
{
	backgroundTexture_.onLostDevice();
	World::releaseAll();
}

void LevelOne::resetAll()
{
	backgroundTexture_.onResetDevice();
	World::resetAll();
}
