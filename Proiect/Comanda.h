#pragma once
#include "Textures.h"
class Comanda {
	int id;
	int castig;
	std::string nume;
	std::string textura;
public:
	int getId() { return id; }
	std::string getNume() { return nume; }
	int getCastig() { return castig; }
	Comanda(int id, std::string nume, int castig) : id(id), nume(nume), castig(castig) {
		textura = "./Texturi/" + nume;
		Textures::getInstance()->addTexture(textura);
	}
};