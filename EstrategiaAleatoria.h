#pragma once
#include "IEstrategiaMovimiento.h"

// Estrategia concreta: patrulla por el mapa cambiando de direccion al encontrar obstaculos
class EstrategiaAleatoria : public IEstrategiaMovimiento {
	int pasosEnDireccion;
public:
	EstrategiaAleatoria();
	void mover(CEnemigo* enemigo, int jugadorX, int jugadorY, CMapa* mapa,
		const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual) override;
};
