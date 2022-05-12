//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 

#include <gl/freeglut.h>
#include "Colors.h"
#include "movingObject.h"
#include "EnemyCar.h"
#include <iostream>
#include "Ground.h"
#include "SeparatoroWhiteLines.h"
#include "GameState.h"
#include "GameOver.h"
#include "Player.h"
#include "HUD.h"
#include "GameData.h"

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
	case State::Started: {		
		if (time(NULL) % 10 == 0) {
			if (rand() % 5 == 0) {
				EnemyCar* enemy = new EnemyCar(-3 + (rand() % 3) * 5.5f, 0.0f, -75.0f);
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
					if (position_in_range(INITIAL_Z, car_pos.z, 0.5)) {
						GameState::getInstance()->setGameOver(Reason::None);
					}
				}
				//if(toDrawObjects[i]->)
			}
			if (toDrawObjects[i]->draw() == false) {
				toDrawObjects.erase(toDrawObjects.begin() + i);
			}
		}

		HUD::drawHUD();
		break;
	}
	case State::Game_Over: {
		deseneaza_ecran_game_over();
		break;
	}
	}


	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	switch (key) {
	case 'l':
		Player::getInstance()->lookAroundLeft();
		break;
	case 'v':
		Player::getInstance()->changeCamera();
		break;
	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

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
	}
}



int main(int argc, char** argv) {
	GameState::getInstance()->setStartGame();
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
	glutInitWindowSize(GameData::WINDOW_WIDTH, GameData::WINDOW_HEIGHT);
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