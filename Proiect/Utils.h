#pragma once
#include <gl/freeglut.h>
#include "SeparatoroWhiteLines.h"

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
	}

	int get_current_choice() { return current_choice; }

	void appendOption(std::string aux) { optiuni.push_back(aux); }

};