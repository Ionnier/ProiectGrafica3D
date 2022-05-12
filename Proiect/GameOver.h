#pragma once
#include <GL/freeglut.h>
#include "Utils.h"
#include "GameData.h"

OptiuniOnScreen gameOverOptions;

class GameOver {
public:
	static void drawGameOver() {
		double left_x = (GameData::WINDOW_WIDTH / 4);
		double left_y = (GameData::WINDOW_HEIGHT / 4);
		double right_x = (3 * GameData::WINDOW_WIDTH / 4);
		double right_y = (3 * GameData::WINDOW_HEIGHT / 4);

		RenderString(GameData::WINDOW_WIDTH / 2 - 10 * 9, 500, "GAME OVER");

		gameOverOptions.display_menu();

		// Chenar
		Colors::getInstance()->setColor(Shade::White);
		glBegin(GL_POLYGON);
		glVertex2i(left_x, left_y);
		glVertex2i(left_x, right_y);
		glVertex2i(right_x, right_y);
		glVertex2i(right_x, left_y);
		glEnd();


		// Fundal
		Colors::getInstance()->setColor(Shade::Black);
		glBegin(GL_POLYGON);
		glVertex2i((0), (0));
		glVertex2i((0), (GameData::WINDOW_HEIGHT));
		glVertex2i((GameData::WINDOW_WIDTH), (GameData::WINDOW_HEIGHT));
		glVertex2i((GameData::WINDOW_WIDTH), (0));
		glEnd();
	}

	static void initialiseGameOverOptions() {
		std::vector<std::string> optiuni;
		optiuni.push_back("Retry");
		optiuni.push_back("Exit");
		OptiuniOnScreen aux(optiuni, 500, 250);
		gameOverOptions = aux;
	}

	static void increaseGameOverOptions() {
		gameOverOptions.increase_choice();
	}

	static void decreaseGameOverOptions() {
		gameOverOptions.decrease_choice();
	}

	static void handleGameOver() {
		switch (gameOverOptions.get_current_choice()) {
		case 0: {
			GameState::getInstance()->setStartGame();
			break;
		}
		case 1: {
			exit(0);
			break;
		}
		}

	}
};