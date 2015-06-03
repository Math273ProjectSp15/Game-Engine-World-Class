//World Class 
//By: Jorge Avila
//Email: avilajorge314@gmail.com
//This class will manage coordinate system
//This class should oversee all collisions and contains the main player entity.  
//Any class the derives from this could be considered a "level" or "stage" of the game.

#pragma once

#include "image.h"
#include "entity.h"
#include "Villain.h"
#include "Mario.h"
#include <string>
#include <sstream>
#include "textDX.h"
#include "fireball.h"
#include "fireWave.h"
#include "villainBullet.h"

struct WINDOWRECT 
{
	double left;
	double right;
	double top;
	double bottom;
};

namespace worldNS
{
	const int EDGE_SPACER = 10;
}

class World : public Game
{
	//Origin is the bottom left corner of the background
protected:
	//This is the entity for the main character of the game (Mario)
	//Need this for collision detection within World
	Mario mario_;
	bool marioStuckOnLeft_;
	bool marioStuckOnRight_;
	bool marioStuckOnTop_;
	bool marioStuckOnBottom_;

	TextureManager marioTexture_;
	//Marios position in World
	VECTOR2	marioPositionVector_;
	VECTOR2 marioInitialPositionVector_;
	//World width and height
	int worldWidth_, worldHeight_;
	//Determine where the window edges are in World
	WINDOWRECT windowRECT_;
	//Entity map for platforms, ground, etc...
	//Maps each entity to its coordinates in World
	std::vector<Entity*> entities_;
	//Entity map for villains 
	//Maps each villain to its coordinates in World
	std::vector<Villain*> villains_;
	TextureManager villainsTexture_;

	
	//Bullets
	fireWave fireWave_;
	fireball fireball_;
	villainBullet villainBullet_;

	std::vector<fireWave> fireWaves_;
	std::vector<fireball> fireballs_;
	std::vector<villainBullet> villainBullets_;

	//Image background for background layers.
	std::vector<Image*> backgroundImages_;
	std::vector <Entity> ground_;
	std::vector <Entity> airground_;

	//Set scrollVector_ so that mario_ is centered in the window unless at the edges of the map
	void updateScroll();
	void resetMarioPosition();

	int distanceToRightEdge;
	int distanceToTopEdge;

	bool withinHorizonalScroll_;
	bool withinVerticalScroll_;

	//Text used for debugging
	TextDX *dxFont_;
	std::string message_;
	float messageY_;

public:
	World();
	virtual ~World();

	// inherited member functions
	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();

	//Get Functions
	const int getWorldWidth() { return worldWidth_; }
	const int getWorldHeight() { return worldHeight_; }
	const WINDOWRECT getWindowRect() { return windowRECT_; }

	//Set Functions
	void setWindowLeft(double windowLeft) { windowRECT_.left = windowLeft; }
	void setWindowRight(double windowRight) { windowRECT_.right = windowRight; }
	void setWindowTop(double windowTop) { windowRECT_.top = windowTop; }
	void setWindowBottom(double windowBottom) { windowRECT_.bottom = windowBottom; }
	void setWindowRECT(WINDOWRECT windowRECT) { windowRECT_ = windowRECT; }
};