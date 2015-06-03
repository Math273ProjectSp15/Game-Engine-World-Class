#pragma once
#include "entity.h"

namespace villainNS {
	const int WIDTH = 256;                   // image width
	const int HEIGHT = 128;                  // image height
	const int TEXTURE_COLS = 6;
	const int START_FRAME = 60;
	const int END_FRAME = 65;
	const double ANIMATION_DELAY = 0.1;
	const float SPEED = 90;                // pixels per second
	const float MASS = 1.0e6f;
}

class Villain : public Entity
{
public:
	// inherited member functions
	virtual void draw();
	bool initialize(Game *gamePtr, TextureManager *textureM);
	//void update(float frameTime, VECTOR2 marioPosition);

	virtual int getVillainHeight() = 0;

	//set and get for onGround_
	void onGround() { onGround_ = true; }
	void notOnGround() { onGround_ = false; }
	bool isOnGround() { return onGround_; }

	//set and get for dead_
	bool isDead() { return dead_; }
	void died() { dead_ = true; }
	void undead() { dead_ = false; }

protected:
	bool onGround_;
	bool dead_;

	//Dead image 
	Image deadImage_;
};