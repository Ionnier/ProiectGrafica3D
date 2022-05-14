//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 

#include <gl/freeglut.h>
#include <iostream>
#include "Ground.h"
#include "EnemyCar.h"
#include "Player.h"
#include "GameState.h"
#include "GameState.h"
#include "GameOver.h"
#include "SeparatoroWhiteLines.h"
#include "Textures.h"
#include "MainMenu.h"
#include "FileComunicator.h"
#include "HUD.h"
#include "Utils2.h"
#include "Radio.h"

bool debugging = false;
double delay_politie = 10;

void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

std::vector<movingObject *> toDrawObjects;

void renderScene(void) {

	switch (GameState::getInstance()->getState()) {
	case State::Entering_Text:
	case State::Delivering:
	case State::Selecting_Order:
	case State::Main_Menu:
	case State::Started: {	

		if(GameState::getInstance()->temperatura_mancare>0 && GameState::getInstance()->getState() == State::Delivering) GameState::getInstance()->temperatura_mancare -= 0.005;
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_LIGHT1);
		GLfloat pozitial1[] = { 0.0, 20, -30, 1.0 };
		GLfloat galben[] = {0.5, 0.5, 0.0, 0.5 };
		glLightfv(GL_LIGHT1, GL_POSITION, pozitial1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, galben);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, galben);
		glLightfv(GL_LIGHT1, GL_AMBIENT, galben);
		int counter_masini = 0;
		for (int i = 0; i < toDrawObjects.size(); i++) {
			EnemyCar* car = dynamic_cast<EnemyCar*>(toDrawObjects[i]);
			if (car != NULL) {
				counter_masini++;
			}
		}
		if (counter_masini == 0) {
			int rand_liber = rand() % 3;
			int randuri[2], iterator = 0;
			for (int i = 0; i < 3; i++) {
				if (i == rand_liber) continue;
				randuri[iterator] = i;
				iterator++;
			}
			
			if (GameState::getInstance()->getState() == State::Main_Menu || GameState::getInstance()->getState() == State::Entering_Text) {
				float linie = -3 + rand_liber * 5.5f;
				while (linie != Player::getInstance()->getX()) {
					if (linie < Player::getInstance()->getX()) {
						Player::getInstance()->goLeft();
					}
					else {
						Player::getInstance()->goRight();
					}
				}

			}
			

			for (int i = 0; i < 2; i++) {
				EnemyCar* enemy = new EnemyCar(-3 + randuri[i] * 5.5f, 0.0f, -75.0f);	
				toDrawObjects.push_back(enemy);
			}
		}

		

		// Clear Color and Depth Buffers

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5, 0.5, 1, 1);

		// Reset transformations
		glLoadIdentity();
		// Set the camera
		gluLookAt(
			Player::getInstance()->getX(),
			Player::getInstance()->getY(),
			Player::getInstance()->getZ(),
			Player::getInstance()->getObX(),
			Player::getInstance()->getObY(),
			Player::getInstance()->getObZ(),
			0.0f,
			Player::getInstance()->getY(),
			0.0f);

		// Current Player Car
		// 6.1f = Initial_Z + Player Car Z + Small Number
		Colors::getInstance()->setColor(Shade::Player_Car);
		glPushMatrix();
		glTranslatef(Player::getInstance()->getX(), 0.0f, 6.1f);
		glutSolidCube(1);
		glPopMatrix();

		Ground::draw();

		// Objects
		for (int i = 0; i < toDrawObjects.size(); i++) {
			EnemyCar* car = dynamic_cast<EnemyCar*>(toDrawObjects[i]);
			if (car != NULL) {
				float playerZ = Player::getInstance()->getZ();
				float playerX = Player::getInstance()->getX();
				choordinates_vector car_pos = car->get_position();
				if (position_in_range(playerX, car_pos.x, 2)) {
					if (position_in_range(INITIAL_Z, car_pos.z, 0.5) && !debugging) {
						FileComunicator::getInstance()->sendCrashedOrder();
						GameState::getInstance()->setGameOver(Reason::Crash);
						toDrawObjects.clear();
						break;
					}
				}
			}
			if (toDrawObjects[i]->draw() == false) {
				if (delay_politie >= 0) delay_politie -= 0.5;
				if (delay_politie < 0 && dynamic_cast<EnemyCar*>(toDrawObjects[i]) != NULL) {
					delay_politie = 10;
					if (estePolitie) {
						estePolitie = false;
						urmeazaPolitie = false;
					}
					if (urmeazaPolitie) {
						estePolitie = true;
						urmeazaPolitie = false;
					}
					if (!estePolitie && !urmeazaPolitie && (rand() % 100 > 50)) {
						urmeazaPolitie = true;
					}
				}
				toDrawObjects.erase(toDrawObjects.begin() + i);
			}
		}

		switch (GameState::getInstance()->getState()) {
		case State::Main_Menu:	HUD::drawMainMenu(); break;
		case State::Entering_Text: HUD::drawText(); break;
		default: HUD::drawHUD();
		}
		break;
	}
	case State::Game_Over: {
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT1);
		HUD::drawGameOver();
		break;
	}
	}


	glutSwapBuffers();
	glFlush();
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	switch (GameState::getInstance()->getState()) {
	case State::Main_Menu: {
		switch (key) {
		case 13:
			MainMenu::handle();
			break;
		case 'v':
			Player::getInstance()->changeCamera();
			break;
		}
		break;
	}
	case State::Game_Over: {
		switch (key) {
		case 13:
			GameOver::handleGameOver();
			break;
		}
		break;
	}
	case State::Delivering:
	case State::Selecting_Order:
	case State::Started: {
		switch (key) {
		case 'l':
			Player::getInstance()->lookAroundLeft();
			break;
		case 'v':
			Player::getInstance()->changeCamera();
			break;
		case 'y':
			GameState::getInstance()->toggleOrders();
			break;
		case 13:
			if (GameState::getInstance()->getState() == State::Selecting_Order) {
				GameState::getInstance()->chooseOrder();
				FileComunicator::getInstance()->sendStartingDeliver();
			}
			break;
		case 'p': {
			if (GameState::getInstance()->getState() == State::Started) {
				FileComunicator::getInstance()->sendOrderRequest();
			}
			break;
		}
		}
		
			
		if (key == 27)
			exit(0);
		break;
	}
	case State::Entering_Text: {
		switch (key) {
		case 13:
			GameState::getInstance()->handleEnter();
			break;
		default: GameState::getInstance()->enterCharacter(key);
		}
		break;
	}
					   
	}
}

void processSpecialKeys(int key, int xx, int yy) {
	switch (GameState::getInstance()->getState()) {
		case State::Main_Menu: {
			switch (key) {
			case GLUT_KEY_LEFT:
				MainMenu::decreaseOptions();
				break;
			case GLUT_KEY_RIGHT:
				MainMenu::increaseOptions();
				break;
			}
			break;
		}
		case State::Game_Over:{
			switch (key) {
			case GLUT_KEY_LEFT:
				GameOver::decreaseGameOverOptions();
				break;
			case GLUT_KEY_RIGHT:
				GameOver::increaseGameOverOptions();
				break;
			}
			break;
		}
		case State::Selecting_Order: {
			switch (key){
			case GLUT_KEY_UP:
				GameState::getInstance()->decreaseSelectedOrder();
				break;
			case GLUT_KEY_DOWN:
				GameState::getInstance()->increaseSelectedOrder();
				break;
			}
			break;
		}
		case State::Delivering:
		case State::Started: {
			switch (key) {
			case GLUT_KEY_LEFT:
				Player::getInstance()->goLeft();
				break;
			case GLUT_KEY_RIGHT:
				Player::getInstance()->goRight();
				break;
			case GLUT_KEY_UP:
				movingObject::move_speed += 0.1f;
				break;
			case GLUT_KEY_DOWN:
				movingObject::move_speed -= 0.1f;
				break;
			case GLUT_KEY_PAGE_UP:
				Radio::getInstance()->schimba_canal();
				break;
			}
		}
	}
}

#include <thread>
void function() {
	while (true) {
		std::string data = FileComunicator::getInstance()->recieveData();
		if (data.size() > 0)
			std::cout << "\nrecieved: " << data << std::endl;
	}
}

std::thread thread(function);

int main(int argc, char** argv) {
	Radio::getInstance();
	srand(time(0));
	estePolitie = 0;
	urmeazaPolitie = 0;
	GameOver::initialiseGameOverOptions();
	MainMenu::initialise();
	resetGame();
	GameState::getInstance()->setMainMenu();
	// Create Separator lines
	float drawObjects = Ground::furtherestPoint;
	while (drawObjects <= 10.0f) {
		// Between left lane and middle lane
		toDrawObjects.push_back(new SeparatorWhiteLines(Ground::middle_point_left, drawObjects));
		// Between and middle lane and right lane
		toDrawObjects.push_back(new SeparatorWhiteLines(Ground::right_left_point, drawObjects));
		drawObjects += (10.0f);
	}
	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(GameState::WINDOW_WIDTH, GameState::WINDOW_HEIGHT);
	glutCreateWindow("Livreaza comanda");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}