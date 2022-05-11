#pragma once
#include <math.h>
#include "Ground.h"

#define INITIAL_Z 5.0f

class Player {
private:
	//position of the camera
	float x, y, z;
	// actual vector representing the camera's direction
	float lx, ly, lz;
	// angle of rotation for the camera direction
	float angle = 0.0;
	static Player* instance;
	Player() {
		lx = 0.0f;
		lz = -1.0f;
		ly = 0.0f;
		x = 2.5f;
		y = 1.0f;
		z = INITIAL_Z;
	}
public:
	static Player* getInstance() {
		if (!instance)
			instance = new Player;
		return instance;
	}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getObX() { return x + lx; }
	float getObY() { return y + ly; }
	float getObZ() { return z + lz; }
	float getLX() { return lx; };
	float getLY() { return ly; };
	float getLZ() { return lz; };

	void changeCamera() {
		y = 2.5f;
		z += 3.5f;
		if (z > 15.5) {
			z = INITIAL_Z;
			y = 1.0f;
		}
	}

	void goLeft() {
		if (x - 5.5 > Ground::leftest_point) {
			x -= 5.5;
		}
	}
	void goRight() {
		if (x + 5.5 < Ground::right_end_point) {
			x += 5.5;
		}
	}

	void lookAroundLeft() {
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
	}

};
Player* Player::instance = 0;