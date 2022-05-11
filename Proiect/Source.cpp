//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 

#include <gl/freeglut.h>
#include <math.h>
#include "Colors.h"
#include "movingObject.h"
#include "EnemyCar.h"
#include <iostream>
#include "Ground.h"
#include "SeparatoroWhiteLines.h"
#include "GameState.h"
#include "GameOver.h"


// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
#define INITIAL_Z 5.0f;
float x = 2.5f, z = INITIAL_Z;
float y = 1.0f;

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
		glClearColor(1, 1, 1, 1);

		// Reset transformations
		glLoadIdentity();
		// Set the camera
		gluLookAt(x, y, z,
			x + lx, y, z + lz,
			0.0f, y, 0.0f);

		// Current Player
		Colors::getInstance()->setColor(Shade::Player_Car);
		glPushMatrix();
		glTranslatef(x, 0.0f, 6.1f);
		glutSolidCube(1);
		glPopMatrix();


		Ground::draw();

		// Objects
		for (int i = 0; i < toDrawObjects.size(); i++) {
			if (toDrawObjects[i]->draw() == false) {
				toDrawObjects.erase(toDrawObjects.begin() + i);
			}
		}
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
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case 'v':
		y = 2.5f;
		z += 3.5;
		if (z > 15.5) {
			z = INITIAL_Z;
			y = 1.0f;
		}
		break;
	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		x -= 5.5;
		break;
	case GLUT_KEY_RIGHT:
		x += 5.5;
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
	glutInitWindowSize(1280, 720);
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