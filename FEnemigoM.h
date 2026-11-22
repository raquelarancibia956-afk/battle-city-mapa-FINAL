#pragma once
#include "CFabricaEnemigo.h"

class FEnemigoM : public CFabricaEnemigo {
public:
	CEnemigo* crearEnemigo(short id, int x, int y) override {
		return new CEnemigo(id, 0, x, y, 1);   
	}
};
