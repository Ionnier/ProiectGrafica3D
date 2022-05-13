#pragma once
#include <gl/freeglut.h>
#include "Textures.h"

void draw_sun() {
    Textures::getInstance()->enableTexture("./Texturi/soare.png");
    glBegin(GL_QUADS);
    glTexCoord3f(-5.0, 10.0, -5.0); glColor3f(1.0, 0.1, 0.1);  glVertex3f(-2.0, -1.0, 0.0);
    glTexCoord3f(5.0, 10.0, -5.0); glColor3f(0.1, 1.0, 0.1);  glVertex3f(-2.0, 1.0, 0.0);
    glTexCoord3f(5.0, 20.0, -5.0); glColor3f(1.0, 1.0, 0.1); glVertex3f(0.0, 1.0, 0.0);
    glTexCoord3f(-5.0, 0.0, -5.0); glColor3f(0.0, 0.1, 1.0); glVertex3f(0.0, -1.0, 0.0);
    glEnd();
}