#include "MarioGame.h"

// Constructor
MarioGame::MarioGame()
{
	levelOne_ = new LevelOne();
}

// Destructor
MarioGame::~MarioGame()
{

}

// Initialize the game
void MarioGame::initialize(HWND hwnd)
{
	levelOne_->initialize(hwnd);
}

void MarioGame::run(HWND hwnd)
{
	levelOne_->run(hwnd);
}

void MarioGame::deleteAll()
{
	levelOne_->deleteAll();
}

LRESULT MarioGame::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return levelOne_->messageHandler(hwnd, msg, wParam, lParam);
}