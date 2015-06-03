#include "PurpleVillain.h"

PurpleVillain::PurpleVillain(Game *gamePtr, TextureManager *textureM, int X, int Y)
{
	initialize(gamePtr, textureM);
	setX(X);
	setY(Y);
}

bool PurpleVillain::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, purpleVillainNS::WIDTH, purpleVillainNS::HEIGHT, purpleVillainNS::TEXTURE_COLS, textureM);
	setFrames(purpleVillainNS::START_FRAME, purpleVillainNS::END_FRAME);
	setCurrentFrame(purpleVillainNS::START_FRAME);
	setFrameDelay(purpleVillainNS::ANIMATION_DELAY);
	setEdge(purpleVillainNS::EDGE_RECT);
	setCollisionType(entityNS::BOX);

	//Villain::initialize(gamePtr, textureM);
	return true;
}


