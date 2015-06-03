#include "GreenVillain.h"

GreenVillain::GreenVillain(Game *gamePtr, TextureManager *textureM, int X, int Y)
{
	initialize(gamePtr, textureM);
	setX(X);
	setY(Y);
}

bool GreenVillain::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, greenVillainNS::WIDTH, greenVillainNS::HEIGHT, greenVillainNS::TEXTURE_COLS, textureM);
	setFrames(greenVillainNS::START_FRAME, greenVillainNS::END_FRAME);
	setCurrentFrame(greenVillainNS::START_FRAME);
	setFrameDelay(greenVillainNS::ANIMATION_DELAY);
	setEdge(greenVillainNS::EDGE_RECT);
	setCollisionType(entityNS::BOX);

	//Villain::initialize(gamePtr, textureM);
	return true;
}
