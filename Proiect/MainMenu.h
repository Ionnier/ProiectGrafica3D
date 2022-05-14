#pragma once

OptiuniOnScreen mainMenuOptions;

class MainMenu {
public:
	static void draw() {
		double left_x = (3* GameState::WINDOW_WIDTH / 4);
		double left_y = (3* GameState::WINDOW_HEIGHT / 4);
		double right_x = (4 * GameState::WINDOW_WIDTH / 5);
		double right_y = (4 * GameState::WINDOW_HEIGHT / 5);

		RenderString(GameState::WINDOW_WIDTH / 2 - 10 * 9, 500, "Livreaza comanda");

		mainMenuOptions.display_menu();
	}

	static void initialise() {
		std::vector<std::string> optiuni;
		if (GameState::getInstance()->isLoggedIn()) {
			optiuni.push_back("Play");
			optiuni.push_back("Exit");
		}
		else {
			optiuni.push_back("Play");
			optiuni.push_back("Login");
			optiuni.push_back("Register");
			optiuni.push_back("Exit");
		}
		OptiuniOnScreen aux(optiuni, 500, 250);
		mainMenuOptions = aux;
	}

	static void increaseOptions() {
		mainMenuOptions.increase_choice();
	}

	static void decreaseOptions() {
		mainMenuOptions.decrease_choice();
	}

	static void handle() {
		if (!GameState::getInstance()->isLoggedIn()) {
			switch (mainMenuOptions.get_current_choice()) {
			case 0: {
				GameState::getInstance()->setStartGame();
				break;
			}
			case 1: {
				GameState::getInstance()->setEnteringText(true);
				break;
			}
			case 2: {
				GameState::getInstance()->setEnteringText(false);
				break;
			}
			case 3: {
				break;
			}
			}
		}
		else {
			switch (mainMenuOptions.get_current_choice()) {
			case 0: {
				GameState::getInstance()->setStartGame();
				break;
			}
			case 1: {
				break;
			}
			}
		}
		

	}
};