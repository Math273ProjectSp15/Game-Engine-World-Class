#include "PurpleVillain.h"

bool PurpleVillain::initialize(Game *gamePtr, TextureManager *textureM)
{
	Entity::initialize(gamePtr, purpleVillainNS::WIDTH, purpleVillainNS::HEIGHT, purpleVillainNS::TEXTURE_COLS, textureM);
	setFrames(purpleVillainNS::START_FRAME, purpleVillainNS::END_FRAME);
	setCurrentFrame(purpleVillainNS::START_FRAME);
	setFrameDelay(purpleVillainNS::ANIMATION_DELAY);
	setEdge(purpleVillainNS::EDGE_RECT);
	return true;
}