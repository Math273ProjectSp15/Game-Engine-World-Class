#include "CyanVillain.h"

bool CyanVillain::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, cyanVillainNS::WIDTH, cyanVillainNS::HEIGHT, cyanVillainNS::TEXTURE_COLS, textureM);
	setFrames(cyanVillainNS::START_FRAME, cyanVillainNS::END_FRAME);
	setCurrentFrame(cyanVillainNS::START_FRAME);
	setFrameDelay(cyanVillainNS::ANIMATION_DELAY);
	setEdge(cyanVillainNS::EDGE_RECT);
	setCollisionType(entityNS::BOX);

	//Villain::initialize(gamePtr, textureM);
	return true;
}
