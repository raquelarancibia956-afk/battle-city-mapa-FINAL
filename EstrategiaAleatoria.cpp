#include "EstrategiaAleatoria.h"
#include "Enemigo.h"
#include <cstdlib>

EstrategiaAleatoria::EstrategiaAleatoria() {
	pasosEnDireccion = 0;
}

void EstrategiaAleatoria::mover(CEnemigo* enemigo, int jugadorX, int jugadorY, CMapa* mapa,
	const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual) {
	EDireccion actual = enemigo->getDireccion();
	if (actual == EDireccion::ninguno) {
		actual = EDireccion::abajo;
	}

	// Cada cierto numero de pasos intenta cambiar de direccion aleatoriamente
	pasosEnDireccion++;
	if (pasosEnDireccion < 25) {
		if (enemigo->intentarAvanzar(actual, mapa, otrosEnemigos, indiceActual)) {
			return;
		}
	}

	pasosEnDireccion = 0;
	EDireccion dirs[4] = {
		EDireccion::arriba,
		EDireccion::abajo,
		EDireccion::izquierda,
		EDireccion::derecha
	};

	int inicio = std::rand() % 4;
	for (int i = 0; i < 4; i++) {
		EDireccion candidata = dirs[(inicio + i) % 4];
		if (enemigo->intentarAvanzar(candidata, mapa, otrosEnemigos, indiceActual)) {
			return;
		}
	}
}
