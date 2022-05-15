#pragma once
#include <GL/freeglut.h>
#include "GameState.h"
#include "Colors.h"
#include "Utils.h"
#include "GameOver.h"
#include "MainMenu.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>

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

	static void drawProgress() {
		GameState::getInstance()->progres += movingObject::move_speed * 20;
		double left_pos = double(GameState::WINDOW_WIDTH / 2) - 300;

		glPushMatrix();
		double pozitie_progres = left_pos + (600 * GameState::getInstance()->progres / GameState::getInstance()->total_drum);

		if (GameState::getInstance()->progres / GameState::getInstance()->total_drum > 1) {
			GameState::getInstance()->progres = 0;
			//score += temp_mancare;
			GameState::getInstance()->temperatura_mancare = 100;
			FileComunicator::getInstance()->sendDelivered();
			GameState::getInstance()->setStartGame();
		}

		Colors::getInstance()->setColor(Shade::Yellow);
		glRecti(pozitie_progres - 10, 5, pozitie_progres + 10, 25);

		glPopMatrix();

		glPushMatrix();

		Colors::getInstance()->setColor(Shade::Black);
		glRecti(left_pos, 5, left_pos+600, 25);

		glPopMatrix();
	}

	static void foodTemperature() {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << GameState::getInstance()->temperatura_mancare;
		std::string var = "Temperatura mancare: " + stream.str();
		RenderString(20.0f, 5.0f, var.c_str(), Shade::White);
		glPushMatrix();
		Colors::getInstance()->setColor(Shade::Black);
		glRecti(15, 0, 270, 20);
		glPopMatrix();
	}

	static void speedometer() {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << abs(movingObject::move_speed * 1250);
		std::string var = "Viteza: " + stream.str() + " km/h";
		RenderString(1000, 5.0f, var.c_str(), Shade::Black);
		glPushMatrix();
		Colors::getInstance()->setColor(Shade::Black);
		glRecti(950, 0, 1200, 25);
		glPopMatrix();
	}


public:
	static void drawHUD() {
		switchTo2D();

		speedometer();

		if (GameState::getInstance()->getState() == State::Delivering) {
			foodTemperature();
			drawProgress();
		}

		if (GameState::getInstance()->getState() == State::Started 
			|| GameState::getInstance()->getState() == State::Delivering
			|| GameState::getInstance()->getState() == State::Selecting_Order) {
			GameState::getInstance()->drawOrders();
		}

		drawCurrentStatus();

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