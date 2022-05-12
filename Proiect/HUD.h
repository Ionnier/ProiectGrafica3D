#pragma once
#include <GL/freeglut.h>
#include "GameData.h"
#include "Colors.h"
#include "Utils.h"

class HUD {
private:
	static void switchTo2D() {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0f, GameData::WINDOW_WIDTH, 0.0f, GameData::WINDOW_HEIGHT, 0.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}

	static void resetTo3D() {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	static void drawCurrentStatus() {
		std::string toDrawString = "";
		switch (GameData::getInstance()->getStatus()) {
		case Status::FREE_ROAM: toDrawString += "Free roaming"; break;
		case Status::WAITING_FOR_ORDER: toDrawString += "Waiting for orders"; break;
		case Status::DELIVERING_ORDER: toDrawString += "Delivering order"; break;
		}
		float initialX = GameData::WINDOW_WIDTH - (9 * toDrawString.size());
		float initialY = GameData::WINDOW_HEIGHT - 20;
		RenderString(initialX, initialY, toDrawString);
	}
public:
	static void drawHUD() {
		switchTo2D();

		drawCurrentStatus();

		resetTo3D();
	}
};