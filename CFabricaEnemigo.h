#pragma once
#include "Enemigo.h"

class CFabricaEnemigo {
public:
	virtual ~CFabricaEnemigo() {}

	// FACTORY METHOD
	virtual CEnemigo* crearEnemigo(short id, int x, int y) = 0;
};
