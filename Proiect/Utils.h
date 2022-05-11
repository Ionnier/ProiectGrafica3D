#pragma once
#include "Colors.h"
#include <gl/freeglut.h>

void drawGroundObject(float leftestPoint, float rightestPoint, float nearestPoint, float fartestPoint, float y = 0.0f) {
	glBegin(GL_QUADS);
		glVertex3f(leftestPoint, y, nearestPoint);
		glVertex3f(leftestPoint, y, fartestPoint);
		glVertex3f(rightestPoint, y, fartestPoint);
		glVertex3f(rightestPoint, y, nearestPoint);
	glEnd();
}