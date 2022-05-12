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


void RenderString(float x, float y, std::string to_render, Shade shade = Shade::Black, void* font = GLUT_BITMAP_HELVETICA_18)
{
	Colors::getInstance()->setColor(shade);
	glRasterPos2f(x, y);
	glutBitmapString(font, (const unsigned char*)to_render.c_str());
}