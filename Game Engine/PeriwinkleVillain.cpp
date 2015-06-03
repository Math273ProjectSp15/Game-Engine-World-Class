#include "PeriwinkleVillain.h"

bool PeriwinkleVillain::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, periwinkleVillainNS::WIDTH, periwinkleVillainNS::HEIGHT, periwinkleVillainNS::TEXTURE_COLS, textureM);
	setFrames(periwinkleVillainNS::START_FRAME, periwinkleVillainNS::END_FRAME);
	setCurrentFrame(periwinkleVillainNS::START_FRAME);
	setFrameDelay(periwinkleVillainNS::ANIMATION_DELAY);
	setEdge(periwinkleVillainNS::EDGE_RECT);
	setCollisionType(entityNS::BOX);

	//Villain::initialize(gamePtr, textureM);
	return true;
}
