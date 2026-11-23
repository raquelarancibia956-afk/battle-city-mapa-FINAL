#pragma once
#include <vector>
#include "Comun.h"

class CEnemigo;
class CMapa;

// Patron Strategy: interfaz para el comportamiento de movimiento de los enemigos
class IEstrategiaMovimiento {
public:
	virtual ~IEstrategiaMovimiento() {}
	virtual void mover(CEnemigo* enemigo, int jugadorX, int jugadorY, CMapa* mapa,
		const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual) = 0;
};
