#pragma once
struct choordinates_vector {
	float x, y, z;
};

class movingObject {
private:
public:
	static float move_speed;
	virtual ~movingObject() {};
	virtual bool draw() = 0;
	virtual choordinates_vector get_position() {
		choordinates_vector empty;
		empty.x = 0;
		empty.y = 0;
		empty.z = 0;
		return(empty);
	}
};
float movingObject::move_speed = 0.1f;