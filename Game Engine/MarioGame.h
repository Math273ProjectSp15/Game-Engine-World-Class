#pragma once
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "Mario.h"
#include "LevelOne.h"

class MarioGame
{
public:
	// Constructor
	MarioGame();
	// Destructor
	~MarioGame();
	// Initialize the game
	void initialize(HWND hwnd);
	//Run the game
	void run(HWND hwnd);
	void deleteAll();
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//=============================================================================
// This class is the core of the game
//=============================================================================
private:
	LevelOne* levelOne_;
};

