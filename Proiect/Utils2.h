#pragma once
extern std::vector<movingObject*> toDrawObjects;

void resetGame() {
	toDrawObjects.clear();
	// Create Separator lines
	float drawObjects = Ground::furtherestPoint;
	while (drawObjects <= 10.0f) {
		// Between left lane and middle lane
		toDrawObjects.push_back(new SeparatorWhiteLines(Ground::middle_point_left, drawObjects));
		// Between and middle lane and right lane
		toDrawObjects.push_back(new SeparatorWhiteLines(Ground::right_left_point, drawObjects));
		drawObjects += (10.0f);
	}
	Player::getInstance()->resetPlayer();
}
