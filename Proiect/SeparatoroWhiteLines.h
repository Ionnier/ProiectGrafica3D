#pragma once
#include "movingObject.h"
#include "Colors.h"
#include "Utils.h"

extern std::vector<movingObject*> toDrawObjects;

class SeparatorWhiteLines : virtual public movingObject {
private:
	const float laneX;
	const float initialZ;
	float positionModifier;
	static float halfWidth;
public:
	static float height;
	static float spaceBetween;
	SeparatorWhiteLines(float laneX, float initialZ) : laneX(laneX), initialZ(initialZ) {
		positionModifier = 0.1f;
	}
	bool draw() {
		Colors::getInstance()->setColor(Shade::White);
		drawGroundObject(laneX - SeparatorWhiteLines::halfWidth,
			laneX + SeparatorWhiteLines::halfWidth,
			initialZ + positionModifier,
			initialZ + positionModifier + SeparatorWhiteLines::height, 0.01f);
		positionModifier += movingObject::move_speed;
		if (initialZ + positionModifier > 10.f) {
			toDrawObjects.push_back(new SeparatorWhiteLines(laneX, -70.0f));
			return false;
		}
		return true;
	}
};
float SeparatorWhiteLines::height = 2.0f;
float SeparatorWhiteLines::halfWidth = 0.10f;
float SeparatorWhiteLines::spaceBetween = 5.0f;