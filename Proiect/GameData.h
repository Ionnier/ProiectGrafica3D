#pragma once
enum class Status { FREE_ROAM, WAITING_FOR_ORDER, DELIVERING_ORDER, NONE};
class GameData {
private:
	static GameData* instance;
	Status status;
	GameData() {
		status = Status::NONE;
	}
public:
	static float WINDOW_HEIGHT;
	static float WINDOW_WIDTH;
	static GameData* getInstance() {
		if (!instance)
			instance = new GameData();
		return instance;
	}
	Status getStatus() { return status; }
	void setStatus(Status status) { this->status=status; }
};
GameData* GameData::instance = 0;
float GameData::WINDOW_HEIGHT = 720.0f;
float GameData::WINDOW_WIDTH = 1280.0f;