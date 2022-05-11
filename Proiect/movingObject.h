#pragma once
class movingObject {
private:
public:
	static float move_speed;
	virtual ~movingObject() {};
	virtual bool draw() = 0;
};
float movingObject::move_speed = 0.1f;