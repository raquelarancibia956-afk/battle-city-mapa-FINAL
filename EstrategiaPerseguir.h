#pragma once
#include "IEstrategiaMovimiento.h"

// Estrategia concreta: persigue activamente la posicion del jugador y decide rodeo ante obstaculos
class EstrategiaPerseguir : public IEstrategiaMovimiento {
	EDireccion dirRodeo;
	int pasosRodeo;
public:
	EstrategiaPerseguir();
	void mover(CEnemigo* enemigo, int jugadorX, int jugadorY, CMapa* mapa,
		const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual) override;
};
