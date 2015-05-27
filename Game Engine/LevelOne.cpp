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
	if (!backgroundTexture_.initialize(graphics, BACKGROUND_LAYER1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background_ texture"));

	if (!backgroundTexture1_.initialize(graphics, BACKGROUND_LAYER2))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background_ texture"));

	// platform_ texture
	if (!platformTexture_.initialize(graphics, PLATFORM_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform_ texture"));

	//ground_ texture
	if (!groundTexture_.initialize(graphics, GROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground texture"));

	// background_
	if (!background_.initialize(graphics, 0, 0, 0, &backgroundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background1_.initialize(graphics, 0, 0, 0, &backgroundTexture1_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	background_.setY((float)GAME_HEIGHT - (float)MAP_HEIGHT);
	background1_.setY((float)GAME_HEIGHT - (float)MAP_HEIGHT);


	//Entities
	if (!platform_.initialize(this, PLATFORM_WIDTH, PLATFORM_HEIGHT, PLATFORM_COLUMNS, &platformTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform entity"));

	if (!ground_.initialize(this, GROUND_ENTITY_WIDTH, GROUND_ENTITY_HEIGHT, GROUND_ENTITY_COLUMNS, &groundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground entity"));

	if (!yellowVillain_.initialize(this, &villainsTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing villain entity"));
	yellowVillain_.setX(GAME_WIDTH / 2);
	yellowVillain_.setY(GAME_HEIGHT / 2);

	platform_.setFrames(PLATFORM_START_FRAME, PLATFORM_END_FRAME);
	platform_.setX(mario_.getX() + mario_.getWidth() + 250);
	platform_.setY(mario_.getY() + 100);
	platform_.setEdge(levelOneNS::platformRECT);
	platform_.setCollisionType(entityNS::BOX);

	ground_.setFrames(GROUND_ENTITY_START_FRAME, GROUND_ENTITY_END_FRAME);
	ground_.setX(mario_.getX() - 200);
	ground_.setY(500);
	ground_.setEdge(levelOneNS::groundRECT);
	ground_.setCollisionType(entityNS::BOX);

	entities_.push_back(&platform_);
	entities_.push_back(&ground_);
	villains_.push_back(&yellowVillain_);

	//Fill World containers with references to Image and Entity objects.
	backgroundImages_.push_back(&background_);
	backgroundImages_.push_back(&background1_);
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
