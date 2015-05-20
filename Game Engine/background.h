#pragma once
#include "constants.h"

namespace backgroundNS
{
	const int MAP_WIDTH = 3072;
	const int MAP_HEIGHT = 1536;
	const int GRID_LENGTH = 32;
	const int GRID_WIDTH = 96;
	const int GRID_HEIGHT = 48;
	const int GROUND_HEIGHT = 192;

	// G = ground, AG = air ground, L = lava, S = spike
	const int G = 0, AG = 1, L = 2, S = 3;
	// empty tile
	const int __ = -1;                 
}

class Background 
{
public:
	Background();
	
	void update(float X,  float Y);

	//convert the window coordnates to map coordinates 

	float getGroundHeight();
	bool movable(float mapX_, float mapY_, int Height, int width);
private:
	float screenX_;
	float screenY_;

	int level_;
	int grid_[backgroundNS::GRID_WIDTH][backgroundNS::GRID_HEIGHT];
	//(upper left corner coordinate of the screen in the map)
	
	//Enemy enemy_;
	//(There can be many this entities)

};