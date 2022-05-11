#pragma once
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>
#include <vector>
#include <map>
#include <utility>
#include <stdexcept>

enum class Mode{Normal, Alternative, Random};
enum class Shade{Green, Black, Blue, Yellow, White, 
				Orange, Very_Light_Blue, Grass, Player_Car,
				Enemy_Car, Red, Radio, Background, 
				Gray, Sosea};
class Colors{
	static Colors* instance;
	std::mt19937 g1;
	unsigned int seed;
	Mode color_mode;

	Colors() {
		color_mode = Mode::Normal;
		changeSeed();
	}

	void setSeed() {
		g1.seed(seed);
	}

	void changeSeed() {
		this->seed = time(0);
		setSeed();
	}

	float getColorX(Shade shade) {
		switch (shade) {
		case Shade::Black: return 0.0f;
		case Shade::Yellow: return 1.0f; 
		case Shade::White: return 1.0f;  
		case Shade::Orange: return 1.0f;
		case Shade::Very_Light_Blue: return 0.0f;  
		case Shade::Grass: return 0.55f;
		case Shade::Player_Car: return 0.996f;
		case Shade::Enemy_Car: return 0.471f;
		case Shade::Red: return 1.0f;
		case Shade::Radio: return 0.55f;
		case Shade::Background: return 0.98f;
		case Shade::Blue: return 0.0f;
		case Shade::Gray: return 0.5f;
		case Shade::Sosea: return 0.98f;
		default: throw std::invalid_argument("No such color");
		}
	}

	float getColorY(Shade shade) {
		switch (shade) {
		case Shade::Black: return 0.0f;
		case Shade::Yellow: return 1.0f;
		case Shade::White: return 1.0f;
		case Shade::Orange: return 0.4f;
		case Shade::Very_Light_Blue: return 1.0f;
		case Shade::Grass: return 0.788f;
		case Shade::Player_Car: return 0.365f;
		case Shade::Enemy_Car: return 0.667f;
		case Shade::Red:return 0.0f;
		case Shade::Radio: return 0.788f;
		case Shade::Background: return 0.929f;
		case Shade::Blue: return 0.0f;
		case Shade::Gray: return 0.5f;
		case Shade::Sosea: return 0.929f;
		default: throw std::invalid_argument("No such color");
		}
	}

	float getColorZ(Shade shade) {
		switch (shade) {
		case Shade::Black: return 0.0f; 
		case Shade::Yellow: return 0.0f;
		case Shade::White: return 1.0f;  
		case Shade::Orange: return 0.0f;  
		case Shade::Very_Light_Blue:return 1.0f;  
		case Shade::Grass: return 0.451f;  
		case Shade::Player_Car: return 0.149f;  
		case Shade::Enemy_Car: return 0.949f;  
		case Shade::Red: return 0.0f;  
		case Shade::Radio: return  0.451f;  
		case Shade::Background: return 0.792f;  
		case Shade::Blue: return 1.0f;
		case Shade::Gray: return 0.5f;
		case Shade::Sosea: return 0.792f;
		default: throw std::invalid_argument("No such color");
		}
	}

public:
	static Colors* getInstance() {
		if (!instance)
			instance = new Colors();
		return instance;
	}
	void setMode(Mode mode) {
		this->color_mode = mode;
	}
	void setColor(Shade shade, float opacity = 1.0f, bool keepColor = false) {
		if (color_mode == Mode::Random && !keepColor) {
			return glColor4f((float)(g1() % 10 / 10.0f), (float)(g1() % 10 / 10.0f), (float)(g1() % 10 / 10.0f), (float)(g1() % 10 / 10.0f));
		}
		if (color_mode == Mode::Alternative && !keepColor) {
			return glColor4f(1.0f - getColorX(shade), 1.0f - getColorY(shade), 1.0f - getColorZ(shade), opacity);
		}
		else {
			return glColor4f(getColorX(shade), getColorY(shade), getColorZ(shade), opacity);
		}
	}
};
Colors* Colors::instance = 0;