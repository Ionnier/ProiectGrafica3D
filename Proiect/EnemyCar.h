#pragma once
#include "movingObject.h"
#include "Colors.h"
#include <gl/freeglut.h>

bool urmeazaPolitie = false, estePolitie = false;

class EnemyCar : virtual public movingObject {
private:
	const float initialX;
	const float initialY;
	const float initialZ;
	float positionModifier;
	float flash_counter;
	bool flashuri_aprinse;
public:
	EnemyCar(float initialX, float initialY, float initialZ) : initialX(initialX), initialY(initialY), initialZ(initialZ) {
		positionModifier = 0.1f;
		flash_counter = 100;
		flashuri_aprinse = false;
		
	}
	EnemyCar(const EnemyCar& aux) : initialX(initialX), initialY(initialY), initialZ(initialZ) {
		positionModifier = aux.positionModifier;
		flash_counter = 10;
		flashuri_aprinse = false;
	}

	void da_flash() {
		if (urmeazaPolitie) {
			if (this->flashuri_aprinse) {
				glPushMatrix();
				Colors::getInstance()->setColor(Shade::Yellow);
				glTranslatef(initialX - 0.25, initialY + 0.2, initialZ + 0.5 + positionModifier);
				glutSolidCube(0.2);
				glPopMatrix();
				glPushMatrix();
				Colors::getInstance()->setColor(Shade::Yellow);
				glTranslatef(initialX + 0.25, initialY + 0.2, initialZ + 0.5 + positionModifier);
				glutSolidCube(0.2);
				glPopMatrix();
			}
			this->flash_counter -= 0.05;
			if (this->flash_counter < 0) {
				if (this->flashuri_aprinse) {
					this->flash_counter = 2.5;
				}
				else {
					this->flash_counter = 5;
				}
				this->flashuri_aprinse = !this->flashuri_aprinse;
			}
		}
	}

	void deseneaza_girofar() {
		glPushMatrix();
		Colors::getInstance()->setColor(Shade::Red);
		glTranslatef(initialX - 0.15, initialY + 0.5, initialZ + 0.2 + positionModifier);
		glutSolidCube(0.2);
		glPopMatrix();
		glPushMatrix();
		Colors::getInstance()->setColor(Shade::Blue);
		glTranslatef(initialX + 0.15, initialY + 0.5, initialZ + 0.2 + positionModifier);
		glutSolidCube(0.2);
		glPopMatrix();
		glPushMatrix();
		Colors::getInstance()->setColor(Shade::Black);
		glTranslatef(initialX, initialY + 0.5, initialZ + 0.2 + positionModifier);
		glutSolidCube(0.2);
		glPopMatrix();
	}

	bool draw() {
		
		glPushMatrix();
		if (urmeazaPolitie) {
			da_flash();
		}
		if (estePolitie) {
			deseneaza_girofar();
		}
		Colors::getInstance()->setColor(Shade::Black);
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