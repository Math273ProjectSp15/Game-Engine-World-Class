#include "GreenVillain.h"

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
