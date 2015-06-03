#include "RedVillain.h"

bool RedVillain::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, redVillainNS::WIDTH, redVillainNS::HEIGHT, redVillainNS::TEXTURE_COLS, textureM);
	setFrames(redVillainNS::START_FRAME, redVillainNS::END_FRAME);
	setCurrentFrame(redVillainNS::START_FRAME);
	setFrameDelay(redVillainNS::ANIMATION_DELAY);
	setEdge(redVillainNS::EDGE_RECT);
	setCollisionType(entityNS::BOX);

	Villain::initialize(gamePtr, textureM);
	return true;
}
