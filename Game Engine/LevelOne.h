#pragma once

#include "World.h"
#include "YellowVillain.h"
#include "CyanVillain.h"
#include "GreenVillain.h"
#include "PeriwinkleVillain.h"
#include "PurpleVillain.h"
#include "RedVillain.h"

namespace levelOneNS 
{
	const int worldWidth = 3000;
	const int worldHeight = 1536;
	
	const int MAP_WIDTH = 3072;
	const int MAP_HEIGHT = 1536;
	const int GRID_LENGTH = 32;
	const int GRID_WIDTH = 96;
	const int GRID_HEIGHT = 48;
	const int GROUND_HEIGHT = 190;

	// collision box {left, top, right ,bottom} relative to center
	const RECT GROUND_EDGE = { -12 * 32, -3 * 32, 12 * 32, 3 * 32 };
	const RECT GROUND1_EDGE = { -1.5 * 32, -3 * 32, 1.5 * 32, 3 * 32 };

	const RECT LAVA_EDGE = { -12 * 32, -2 * 32, 12 * 32, 2 * 32 };
	const RECT SPIKE_EDGE = { -10 * 32, -2 * 32, 10 * 32, 2 * 32 };

	const RECT AIRGROUND1_EDGE = { -2.5 * 32, -1.5 * 32, 2.5 * 32, 1.5 * 32 };
	const RECT AIRGROUND2_EDGE = { -4 * 32, -1.5 * 32, 4 * 32, 1.5 * 32 };
	const RECT AIRGROUND3_EDGE = { -3 * 32, -1.5 * 32, 3 * 32, 1.5 * 32 };

	//Ground Position
	const float GROUND_Y = 42 * 32;

	const float GROUND1_X = 0;

	const float GROUND2_X = 49 * 32;

	const float GROUND3_X = 93 * 32;

	//Lava Position
	const float LAVA_X = 24 * 32;
	const float LAVA_Y = 44 * 32;

	//Spike Position
	const float SPIKE_X = 73 * 32;
	const float SPIKE_Y = 44 * 32;

	//Air Ground Position
	const float AIRGROUND1_X = 26 * 32;
	const float AIRGROUND1_Y = 31 * 32;

	const float AIRGROUND2_X = 36 * 32;
	const float AIRGROUND2_Y = 28 * 32;

	const float AIRGROUND3_X = 45 * 32;
	const float AIRGROUND3_Y = 25 * 32;

	const float AIRGROUND4_X = 60 * 32;
	const float AIRGROUND4_Y = 25 * 32;

	const float AIRGROUND5_X = 85 * 32;
	const float AIRGROUND5_Y = 15 * 32;

	//Initial Position for mario
	const int marioInitialPositionX = 200;
	const int marioInitialPositionY = 352;
}

class LevelOne : public World
{
public:
	LevelOne();
	~LevelOne();
	// inherited member functions
	// Initialize the game
	void initialize(HWND hwnd);

	void releaseAll();
	void resetAll();
private:
	//Textures
	TextureManager backgroundTexture_;
	TextureManager backgroundTexture1_;
	TextureManager backgroundTexture2_;

	// game items
	TextureManager marioTexture_;     // mario texture
	TextureManager groundTexture_;
	TextureManager ground1Texture_;
	TextureManager lavaTexture_;
	TextureManager spikeTexture_;
	TextureManager airground1Texture_;
	TextureManager airground2Texture_;
	TextureManager airground3Texture_;

	//Image objects
	Image background_;
	Image background1_;
	Image background2_;

	//Entity
	Entity lava_;
	Entity spike_;

};