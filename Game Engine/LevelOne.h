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
	const int marioInitialPositionY = 200;//(float)GAME_HEIGHT - GROUND_HEIGHT - marioNS::HEIGHT - 30.0;
	//							left, top, right, bottom
	const RECT platformRECT = { -PLATFORM_WIDTH / 2, -PLATFORM_HEIGHT / 2, PLATFORM_WIDTH / 2, PLATFORM_HEIGHT / 2 };
	const RECT groundRECT = { -GROUND_ENTITY_WIDTH / 2, -GROUND_ENTITY_HEIGHT / 2, GROUND_ENTITY_WIDTH / 2, GROUND_ENTITY_HEIGHT / 2 };
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
	TextureManager backgroundTexture1_;
	TextureManager platformTexture_;
	TextureManager groundTexture_;

	//Image objects
	Image background_;
	Image background1_;

	//Entity Objects
	Entity platform_;
	Entity ground_;

	RedVillain yellowVillain_;
};