#pragma once
#include <gl/freeglut.h>
#include "SeparatoroWhiteLines.h"
#include<string>

void RenderString(float x, float y, std::string to_render, Shade shade = Shade::Black, void* font = GLUT_BITMAP_HELVETICA_18)
{
	Colors::getInstance()->setColor(shade);
	glRasterPos2f(x, y);
	glutBitmapString(font, (const unsigned char*)to_render.c_str());
}

bool position_in_range(float pos1, float pos2, float threshold) {
	return(pos1 < pos2 + threshold && pos1 > pos2 - threshold);
}


class OptiuniOnScreen {
private:
	std::vector<std::string> optiuni;
	int initial_x;
	int initial_y;
	int current_choice;
public:

	OptiuniOnScreen(std::vector<std::string> optiuni = *(new std::vector<std::string>()), int initial_x=0, int initial_y=0) {
		this->optiuni = optiuni;
		this->initial_x = initial_x;
		this->initial_y = initial_y;
		current_choice = 0;
	}

	void increase_choice() {
		current_choice = (current_choice + 1) % optiuni.size();
	}

	void decrease_choice() {
		if (current_choice == 0)
			current_choice = optiuni.size() - 1;
		else
			current_choice--;
	}


    void draw_beziere(GLfloat ctrlpoints[4][3])
    {
        glShadeModel(GL_FLAT);
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4,
            &ctrlpoints[0][0]);

        glEnable(GL_MAP1_VERTEX_3);

        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);

        for (int i = 0; i <= 30; i++)
            glEvalCoord1f((GLfloat)i / 30.0);

        glEnd();
    }

    void display_beziere(void)
    {
        int i;

        GLfloat ctrlpoints[4][3]
            = { { 10.00, 2.00, 0.0 },
                { 2.00, 2.00, 0.0 },
                { 2.00, 1.00, 0.0 },
                { 0.00, 1.00, 0.0 } };
        draw_beziere(ctrlpoints);

        GLfloat ctrlpoints2[4][3]
            = { { 100.0, 10.00, 0.0 },
                { 5.55, 6.65, 0.0 },
                { 6.65, 2.25, 0.0 },
                { 0.00, 7.70, 0.0 } };

        draw_beziere(ctrlpoints2);
        GLfloat ctrlpoints3[4][3]
            = { { 200.0, 70.70, 0.0 },
                { 101.15, 74.70, 0.0 },
                { 82.25, 67.70, 0.0 },
                { 76.65, 47.700, 0.0 } };

        draw_beziere(ctrlpoints3);
        GLfloat ctrlpoints4[4][3]
            = { { 96.65, 87.70, 0.0 },
                { 56.65, 79.90, 0.0 },
                { 66.65, 47.70, 0.0 },
                { 26.65, 81.00, 0.0 } };

        draw_beziere(ctrlpoints4);

    }
    void drawBitmapText(char* string, float x,
        float y, float z)
    {
        char* c;
        glRasterPos2f(x, y);

        // Traverse the string
        for (c = string; *c != '\0'; c++) {
            glutBitmapCharacter(
                GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }
    }
	void display_menu() {
		float acc_x = initial_x;
		for (int i = 0; i < optiuni.size(); i++) {
			if (i == current_choice) {
				RenderString(acc_x, initial_y, optiuni[i], Shade::Red);
			}
			else {
				RenderString(acc_x, initial_y, optiuni[i], Shade::Black);
			}
			acc_x += (12 * optiuni[i].size());
		}
        display_beziere();
	}

	int get_current_choice() { return current_choice; }

	void appendOption(std::string aux) { optiuni.push_back(aux); }

};