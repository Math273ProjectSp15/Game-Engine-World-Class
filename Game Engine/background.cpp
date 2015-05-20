#include "background.h"

Background::Background()
{
	screenX_ = 0;
	screenY_ = MAP_HEIGHT - GAME_HEIGHT;
	level_ = 0;
	for (int i = 0; i < backgroundNS::GRID_WIDTH; i++)
	{
		for (int j = 0; j < backgroundNS::GRID_HEIGHT; j++)
		{
			grid_[i][j] == backgroundNS::__;
		}
	}
	if (level_ == 0)
	{
		//initialize ground
		for (int j = 42; j < 48; j++)
		{
			for (int i = 0; i < 24; i++)
			{
				grid_[i][j] = backgroundNS::G;
			}
			for (int i = 49; i < 73; i++)
			{
				grid_[i][j] = backgroundNS::G;
			}
			for (int i = 93; i < 96; i++)
			{
				grid_[i][j] = backgroundNS::G;
			}
		}

		//initialize air ground
		for (int i = 16; i < 21; i++)
		{
			for (int j = 32; j < 35; j++)
			{
				grid_[i][j] = backgroundNS::AG;
			}
		}
		for (int i = 26; i < 31; i++)
		{
			for (int j = 26; j < 29; j++)
			{
				grid_[i][j] = backgroundNS::AG;
			}
		}
		for (int i = 45; i < 53; i++)
		{
			for (int j = 25; j < 28; j++)
			{
				grid_[i][j] = backgroundNS::AG;
			}
		}
		for (int i = 60; i < 66; i++)
		{
			for (int j = 25; j < 28; j++)
			{
				grid_[i][j] = backgroundNS::AG;
			}
		}
		for (int i = 85; i < 90; i++)
		{
			for (int j = 15; j < 18; j++)
			{
				grid_[i][j] = backgroundNS::AG;
			}
		}

		//intialize lava
		for (int i = 25; i < 49; i++)
		{
			for (int j = 44; j < 48; j++)
			{
				grid_[i][j] = backgroundNS::L;
			}
		}

		//initialize spike
		for (int i = 73; i < 93; i++)
		{
			for (int j =45 ; j < 48; j++)
			{
				grid_[i][j] = backgroundNS::S;
			}
		}
	}


}

float Background::getGroundHeight() 
{
	return (float)(5 * backgroundNS::GRID_LENGTH);
}

bool Background::movable(float mapX_, float mapY_, int Height, int width)
{
	return true;
}