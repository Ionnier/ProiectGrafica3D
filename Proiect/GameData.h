#pragma once
#include "Textures.h"
#include <string>
#include "GameState.h"
class GameData {
private:
	static GameData* instance;
	GameData() {

	}
	
	
public:
	
	static GameData* getInstance() {
		if (!instance)
			instance = new GameData();
		return instance;
	}
};
