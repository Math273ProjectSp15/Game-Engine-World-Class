#pragma once

#include "World.h"
#include "YellowVillain.h"
#include "CyanVillain.h"
#include "GreenVillain.h"
#include "PeriwinkleVillain.h"
#include "PurpleVillain.h"
#include "RedVillain.h"

namespace levelOneNS {
	const int worldWidth = 3072;
	const int worldHeight = 1536;
	const int marioInitialPositionX = GAME_WIDTH/2 - marioNS::WIDTH;
	const int marioInitialPositionY = (float)GAME_HEIGHT - GROUND_HEIGHT - marioNS::HEIGHT - 30.0;
}

class LevelOne : public World
{
public:
	LevelOne();
	~LevelOne();
	// inherited member functions
	// Initialize the game
	void initialize(HWND hwnd);
	//void update();      // must override pure virtual from Game
	//void ai();          // "
	//void collisions();  // "
	//void render();      // "
	void releaseAll();
	void resetAll();
private:
	//Textures
	TextureManager backgroundTexture_;
	TextureManager platformTexture_;

	//Image objects
	Image background_;

	//Entity Objects
	Entity platform_;

	RedVillain yellowVillain_;
};