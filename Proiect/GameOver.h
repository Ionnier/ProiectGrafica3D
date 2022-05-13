#pragma once
#include <GL/freeglut.h>
#include "Utils.h"
#include "Textures.h"

OptiuniOnScreen gameOverOptions;

class GameOver {
public:
	static void drawGameOver() {
		double left_x = (GameState::WINDOW_WIDTH / 4);
		double left_y = (GameState::WINDOW_HEIGHT / 4);
		double right_x = (3 * GameState::WINDOW_WIDTH / 4);
		double right_y = (3 * GameState::WINDOW_HEIGHT / 4);

		RenderString(GameState::WINDOW_WIDTH / 2 - 10 * 9, 500, "GAME OVER");

		glEnable(GL_TEXTURE_2D);
		switch (GameState::getInstance()->getGameOverReason()) {
		case Reason::Crash: Textures::getInstance()->enableTexture("./Texturi/explosion.jpg");break;
		case Reason::Police: Textures::getInstance()->enableTexture("./Texturi/police.jpg");break;
		case Reason::Cold: Textures::getInstance()->enableTexture("./Texturi/cold.jpg");break;
		}

		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glColor3f(1.0, 0.1, 0.1);  glVertex2f(2 * GameState::WINDOW_WIDTH / 5, 2 * GameState::WINDOW_HEIGHT / 5);
		glTexCoord2f(1.0, 0.0); glColor3f(0.1, 1.0, 0.1);  glVertex2f(2 * GameState::WINDOW_WIDTH/5, 3 * GameState::WINDOW_HEIGHT / 5);
		glTexCoord2f(0.0, 0.0); glColor3f(1.0, 1.0, 0.1); glVertex2f(3 * GameState::WINDOW_WIDTH / 5, 3 * GameState::WINDOW_HEIGHT / 5);
		glTexCoord2f(0.0, 1.0); glColor3f(0.0, 0.1, 1.0); glVertex2f(3 * GameState::WINDOW_WIDTH / 5, 2 * GameState::WINDOW_HEIGHT / 5);
		glEnd();

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
		glVertex2i((0), (GameState::WINDOW_HEIGHT));
		glVertex2i((GameState::WINDOW_WIDTH), (GameState::WINDOW_HEIGHT));
		glVertex2i((GameState::WINDOW_WIDTH), (0));
		glEnd();
	}

	static void initialiseGameOverOptions() {
		std::vector<std::string> optiuni;
		optiuni.push_back("Retry");
		optiuni.push_back("Main Menu");
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
			GameState::getInstance()->setMainMenu();
			break;
		}
		case 2: {
			exit(0);
			break;
		}
		}

	}
};