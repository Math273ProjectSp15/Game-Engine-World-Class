#include "YellowVillain.h"

bool YellowVillain::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, yellowVillainNS::WIDTH, yellowVillainNS::HEIGHT, yellowVillainNS::TEXTURE_COLS, textureM);
	setFrames(yellowVillainNS::START_FRAME, yellowVillainNS::END_FRAME);
	setCurrentFrame(yellowVillainNS::START_FRAME);
	setFrameDelay(yellowVillainNS::ANIMATION_DELAY);
	setEdge(yellowVillainNS::EDGE_RECT);
	setCollisionType(entityNS::BOX);

	Villain::initialize(gamePtr, textureM);
	return true;
}