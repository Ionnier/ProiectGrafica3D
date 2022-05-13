#pragma once
#include "Textures.h"
#include <algorithm>
class Comanda {
	int id;
	int castig;
	std::string nume;
	std::string textura;
public:
	int getId() { return id; }
	std::string getNume() { return nume; }
	int getCastig() { return castig; }
	std::string getTextura() { return textura; }
	Comanda(int id, std::string nume, int castig) : id(id), nume(nume), castig(castig) {
		std::transform(nume.begin(), nume.end(), nume.begin(), ::tolower);
		textura = "./Texturi/" + nume + ".jpg";
		Textures::getInstance()->addTexture(textura);
	}
};