#include "LevelOne.h"

LevelOne::LevelOne()
{
	worldWidth_ = levelOneNS::worldWidth;
	worldHeight_ = levelOneNS::worldHeight;
	marioPositionVector_.x = GAME_WIDTH / 2;
	marioPositionVector_.y = levelOneNS::marioInitialPositionY;
	marioInitialPositionVector_.x = marioPositionVector_.x;
	marioInitialPositionVector_.y = marioPositionVector_.y;
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

	if (!backgroundTexture2_.initialize(graphics, BACKGROUND_LAYER3))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background_ texture"));

	if (!groundTexture_.initialize(graphics, GROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground_ texture"));

	if (!ground1Texture_.initialize(graphics, GROUND1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground1_ texture"));

	if (!lavaTexture_.initialize(graphics, LAVA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing lava_ texture"));

	if (!spikeTexture_.initialize(graphics, SPIKE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spike_ texture"));

	if (!airground1Texture_.initialize(graphics, AIR_GROUND1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground1_ texture"));

	if (!airground2Texture_.initialize(graphics, AIR_GROUND2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground2_ texture"));

	if (!airground3Texture_.initialize(graphics, AIR_GROUND3_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airgound3_ texture"));

	// background_
	if (!background_.initialize(graphics, 0, 0, 0, &backgroundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background1_.initialize(graphics, 0, 0, 0, &backgroundTexture1_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background2_.initialize(graphics, 0, 0, 0, &backgroundTexture2_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	background_.setY((float)GAME_HEIGHT - (float)MAP_HEIGHT * MAIN_BACKGROUND_SHIFT);
	background1_.setY((float)GAME_HEIGHT - (float)MAP_HEIGHT);
	background2_.setY((float)GAME_HEIGHT - (float)MAP_HEIGHT * 0.6);

	//initialize ground
	ground_.resize(3);
	if (!ground_[0].initialize(this, 0, 0, 0, &groundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground0 texture"));
	ground_[0].setCollisionType(entityNS::BOX);
	ground_[0].setEdge(levelOneNS::GROUND_EDGE);

	ground_[0].setX(levelOneNS::GROUND1_X);
	ground_[0].setY(levelOneNS::GROUND_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&ground_[0]);

	if (!ground_[1].initialize(this, 0, 0, 0, &groundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground1 texture"));
	ground_[1].setCollisionType(entityNS::BOX);
	ground_[1].setEdge(levelOneNS::GROUND_EDGE);
	ground_[1].setX(levelOneNS::GROUND2_X);
	ground_[1].setY(levelOneNS::GROUND_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&ground_[1]);

	if (!ground_[2].initialize(this, 0, 0, 0, &ground1Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground2 texture"));
	ground_[2].setCollisionType(entityNS::BOX);
	ground_[2].setEdge(levelOneNS::GROUND1_EDGE);
	ground_[2].setX(levelOneNS::GROUND3_X);
	ground_[2].setY(levelOneNS::GROUND_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&ground_[2]);

	//initialize lava
	if (!lava_.initialize(this, 0, 0, 0, &lavaTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing lava texture"));
	lava_.setCollisionType(entityNS::BOX);
	lava_.setEdge(levelOneNS::LAVA_EDGE);
	lava_.setX(levelOneNS::LAVA_X);
	lava_.setY(levelOneNS::LAVA_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&lava_);

	//initialize spike
	if (!spike_.initialize(this, 0, 0, 0, &spikeTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spike texture"));
	spike_.setCollisionType(entityNS::BOX);
	spike_.setEdge(levelOneNS::SPIKE_EDGE);
	spike_.setX(levelOneNS::SPIKE_X);
	spike_.setY(levelOneNS::SPIKE_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&spike_);

	//initialize airground
	airground_.resize(5);

	if (!airground_[0].initialize(this, 0, 0, 0, &airground1Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground0 texture"));
	airground_[0].setCollisionType(entityNS::BOX);
	airground_[0].setEdge(levelOneNS::AIRGROUND1_EDGE);
	airground_[0].setX(levelOneNS::AIRGROUND1_X);
	airground_[0].setY(levelOneNS::AIRGROUND1_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&airground_[0]);

	if (!airground_[1].initialize(this, 0, 0, 0, &airground1Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground1 texture"));
	airground_[1].setCollisionType(entityNS::BOX);
	airground_[1].setEdge(levelOneNS::AIRGROUND1_EDGE);
	airground_[1].setX(levelOneNS::AIRGROUND2_X);
	airground_[1].setY(levelOneNS::AIRGROUND2_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&airground_[1]);

	if (!airground_[2].initialize(this, 0, 0, 0, &airground2Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground2 texture"));
	airground_[2].setCollisionType(entityNS::BOX);
	airground_[2].setEdge(levelOneNS::AIRGROUND2_EDGE);
	airground_[2].setX(levelOneNS::AIRGROUND3_X);
	airground_[2].setY(levelOneNS::AIRGROUND3_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&airground_[2]);

	if (!airground_[3].initialize(this, 0, 0, 0, &airground3Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground3 texture"));
	airground_[3].setCollisionType(entityNS::BOX);
	airground_[3].setEdge(levelOneNS::AIRGROUND3_EDGE);
	airground_[3].setX(levelOneNS::AIRGROUND4_X);
	airground_[3].setY(levelOneNS::AIRGROUND4_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&airground_[3]);

	if (!airground_[4].initialize(this, 0, 0, 0, &airground1Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground4 texture"));
	airground_[4].setCollisionType(entityNS::BOX);
	airground_[4].setEdge(levelOneNS::AIRGROUND1_EDGE);
	airground_[4].setX(levelOneNS::AIRGROUND5_X);
	airground_[4].setY(levelOneNS::AIRGROUND5_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	entities_.push_back(&airground_[4]);


	if (SPAWN_CONTROL)
		villains_.push_back(createVillain());

	//Fill World containers with references to Image and Entity objects.
	backgroundImages_.push_back(&background_);
	backgroundImages_.push_back(&background2_);
	backgroundImages_.push_back(&background1_);
	return;
}

void LevelOne::releaseAll()
{
	backgroundTexture_.onLostDevice();
	backgroundTexture1_.onLostDevice();
	backgroundTexture2_.onLostDevice();
	marioTexture_.onLostDevice();
	groundTexture_.onLostDevice();
	ground1Texture_.onLostDevice();
	lavaTexture_.onLostDevice();
	spikeTexture_.onLostDevice();
	airground1Texture_.onLostDevice();
	airground2Texture_.onLostDevice();
	airground3Texture_.onLostDevice();
	World::releaseAll();
}

void LevelOne::resetAll()
{
	backgroundTexture_.onResetDevice();
	backgroundTexture1_.onResetDevice();
	backgroundTexture2_.onResetDevice();
	marioTexture_.onResetDevice();
	groundTexture_.onResetDevice();
	ground1Texture_.onResetDevice();
	lavaTexture_.onResetDevice();
	spikeTexture_.onResetDevice();
	airground1Texture_.onResetDevice();
	airground2Texture_.onResetDevice();
	airground3Texture_.onResetDevice();
	World::resetAll();
}
