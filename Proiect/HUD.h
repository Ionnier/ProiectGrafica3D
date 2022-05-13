#pragma once
#include <GL/freeglut.h>
#include "GameState.h"
#include "Colors.h"
#include "Utils.h"
#include "GameOver.h"
#include "MainMenu.h"

class HUD {
private:
	static void switchTo2D() {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0f, GameState::WINDOW_WIDTH, 0.0f, GameState::WINDOW_HEIGHT, 0.0, 1.0);
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
		switch (GameState::getInstance()->getStatus()) {
		case Status::FREE_ROAM: toDrawString += "Free roaming"; break;
		case Status::WAITING_FOR_ORDER: toDrawString += "Waiting for orders"; break;
		case Status::DELIVERING_ORDER: toDrawString += "Delivering order"; break;
		}
		float initialX = GameState::WINDOW_WIDTH - (9 * toDrawString.size());
		float initialY = GameState::WINDOW_HEIGHT - 20;
		RenderString(initialX, initialY, toDrawString);
	}
public:
	static void drawHUD() {
		switchTo2D();

		drawCurrentStatus();
		GameState::getInstance()->drawOrders();

		resetTo3D();
	}

	static void drawText() {
		switchTo2D();

		GameState::getInstance()->drawText();

		resetTo3D();
	}

	static void drawGameOver() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glPushMatrix();
		switchTo2D();

		GameOver::drawGameOver();

		resetTo3D();
	}

	static void drawMainMenu() {
		switchTo2D();

		MainMenu::draw();

		resetTo3D();
	}
};