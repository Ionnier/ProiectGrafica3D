#pragma once
#include "movingObject.h"
#include "Colors.h"
#include <gl/freeglut.h>

class EnemyCar : virtual public movingObject {
private:
	const float initialX;
	const float initialY;
	const float initialZ;
	float positionModifier;
public:
	EnemyCar(float initialX, float initialY, float initialZ) : initialX(initialX), initialY(initialY), initialZ(initialZ) {
		positionModifier = 0.1f;
		
	}
	EnemyCar(const EnemyCar& aux) : initialX(initialX), initialY(initialY), initialZ(initialZ) {
		positionModifier = aux.positionModifier;
	}
	bool draw() {
		Colors::getInstance()->setColor(Shade::Red);
		glPushMatrix();
		glTranslatef(initialX, initialY, initialZ + positionModifier);
		glutSolidCube(1);
		glPopMatrix();
		positionModifier += movingObject::move_speed;
		if (initialZ + positionModifier > 10.f) {
			return false;
		}
		return true;
	}

	choordinates_vector get_position() {
		choordinates_vector res;
		res.x = this->initialX;
		res.y = this->initialY;
		res.z = this->initialZ + positionModifier;
		return(res);
	}
};