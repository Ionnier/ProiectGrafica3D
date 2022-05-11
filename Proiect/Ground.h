#pragma once
#include <gl/freeglut.h>
#include "Colors.h"
#include "Utils.h"

class Ground {
public:
	static float distance_between_lanes;
	static float leftest_point;
	static float middle_point_left;
	static float right_left_point;
	static float right_end_point;

	static float nearest_point;
	static float size_of_lane;
	static float farthest_point;
	static float infinite;
	static float furtherestPoint;
	static void draw() {

		// Road
		// Left
		Colors::getInstance()->setColor(Shade::Sosea, 1);
		drawGroundObject(leftest_point, middle_point_left, nearest_point, farthest_point);

		// Middle
		drawGroundObject(middle_point_left, right_left_point, nearest_point, farthest_point);
		// Right
		drawGroundObject(right_left_point, right_end_point, nearest_point, farthest_point);

		// Draw SideWalk
		float sideWalkLength = 2.5f;
		float rightSideWalkLeftStart = right_end_point;
		float rightSideWalkRightStart = rightSideWalkLeftStart + sideWalkLength;

		float leftSideWalkLeftStart = leftest_point;
		float leftSideWalkRightStart = leftest_point - sideWalkLength;

		Colors::getInstance()->setColor(Shade::Gray, 1);
		drawGroundObject(rightSideWalkLeftStart, rightSideWalkRightStart, nearest_point, farthest_point);
		drawGroundObject(leftSideWalkRightStart, leftSideWalkLeftStart, nearest_point, farthest_point);

		// Draw Grass
		Colors::getInstance()->setColor(Shade::Grass, 1);
		drawGroundObject(rightSideWalkRightStart, rightSideWalkRightStart + infinite, nearest_point, farthest_point);
		drawGroundObject(leftSideWalkRightStart - infinite, leftSideWalkRightStart, nearest_point, farthest_point);

	}
};
float Ground::distance_between_lanes = 5;
float Ground::leftest_point = -5;
float Ground::middle_point_left = leftest_point + distance_between_lanes;
float Ground::right_left_point = middle_point_left + distance_between_lanes;
float Ground::right_end_point = right_left_point + distance_between_lanes;
float Ground::furtherestPoint = -70.0f; // farest point where objects can appear

float Ground::nearest_point = 10.0f;
float Ground::size_of_lane = -1000.0f;
float Ground::farthest_point = nearest_point + size_of_lane;
float Ground::infinite = 1000.0f;