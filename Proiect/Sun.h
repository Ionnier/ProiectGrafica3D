#pragma once
#include <gl/freeglut.h>
#include "SOIL.h"
unsigned char* image;
int width, height;

void load_sun() {
    image = SOIL_load_image("./Texturi/soare.png", &width, &height, 0, SOIL_LOAD_RGB);
}

void draw_sun() {
    glEnable(GL_TEXTURE_2D);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glBegin(GL_QUADS);
    glTexCoord3f(-5.0, 10.0, -5.0); glColor3f(1.0, 0.1, 0.1);  glVertex3f(-2.0, -1.0, 0.0);
    glTexCoord3f(5.0, 10.0, -5.0); glColor3f(0.1, 1.0, 0.1);  glVertex3f(-2.0, 1.0, 0.0);
    glTexCoord3f(5.0, 20.0, -5.0); glColor3f(1.0, 1.0, 0.1); glVertex3f(0.0, 1.0, 0.0);
    glTexCoord3f(-5.0, 0.0, -5.0); glColor3f(0.0, 0.1, 1.0); glVertex3f(0.0, -1.0, 0.0);
    glEnd();
}