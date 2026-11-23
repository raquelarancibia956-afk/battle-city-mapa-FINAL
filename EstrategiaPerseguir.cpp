#include "EstrategiaPerseguir.h"
#include "Enemigo.h"
#include <cmath>
#include <cstdlib>

EstrategiaPerseguir::EstrategiaPerseguir() {
	dirRodeo = EDireccion::ninguno;
	pasosRodeo = 0;
}

void EstrategiaPerseguir::mover(CEnemigo* enemigo, int jugadorX, int jugadorY, CMapa* mapa,
	const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual) {

	// Si esta rodeando un obstaculo, mantiene la decision tomada durante unos pasos
	if (pasosRodeo > 0 && dirRodeo != EDireccion::ninguno) {
		if (enemigo->intentarAvanzar(dirRodeo, mapa, otrosEnemigos, indiceActual)) {
			pasosRodeo--;
			return;
		} else {
			pasosRodeo = 0;
			dirRodeo = EDireccion::ninguno;
		}
	}

	int dx = jugadorX - enemigo->getX();
	int dy = jugadorY - enemigo->getY();

	EDireccion dirPrincipal = EDireccion::ninguno;
	EDireccion dirSecundaria = EDireccion::ninguno;
	EDireccion dirOpuestaSec = EDireccion::ninguno;
	EDireccion dirOpuestaPrin = EDireccion::ninguno;

	if (std::abs(dx) > std::abs(dy)) {
		dirPrincipal = (dx > 0) ? EDireccion::derecha : EDireccion::izquierda;
		dirOpuestaPrin = (dx > 0) ? EDireccion::izquierda : EDireccion::derecha;

		dirSecundaria = (dy > 0) ? EDireccion::abajo : EDireccion::arriba;
		dirOpuestaSec = (dy > 0) ? EDireccion::arriba : EDireccion::abajo;
	} else {
		dirPrincipal = (dy > 0) ? EDireccion::abajo : EDireccion::arriba;
		dirOpuestaPrin = (dy > 0) ? EDireccion::arriba : EDireccion::abajo;

		dirSecundaria = (dx > 0) ? EDireccion::derecha : EDireccion::izquierda;
		dirOpuestaSec = (dx > 0) ? EDireccion::izquierda : EDireccion::derecha;
	}

	// 1. Intentar avanzar en la direccion principal hacia el jugador
	if (enemigo->intentarAvanzar(dirPrincipal, mapa, otrosEnemigos, indiceActual)) {
		return;
	}

	// 2. Si choco estando en la misma columna o fila que el jugador, decidir por que lado rodear
	bool mismaColumna = (std::abs(dx) < ANCHO_TANQUE / 2);
	bool mismaFila = (std::abs(dy) < ALTO_TANQUE / 2);

	if ((dirPrincipal == EDireccion::arriba || dirPrincipal == EDireccion::abajo) && mismaColumna) {
		bool izqLibre = enemigo->puedeMoverEnemigo(enemigo->getX() - 1, enemigo->getY(), mapa, otrosEnemigos, indiceActual);
		bool derLibre = enemigo->puedeMoverEnemigo(enemigo->getX() + 1, enemigo->getY(), mapa, otrosEnemigos, indiceActual);

		EDireccion elegida = EDireccion::ninguno;
		if (izqLibre && derLibre) {
			elegida = (std::rand() % 2 == 0) ? EDireccion::derecha : EDireccion::izquierda;
		} else if (derLibre) {
			elegida = EDireccion::derecha;
		} else if (izqLibre) {
			elegida = EDireccion::izquierda;
		}

		if (elegida != EDireccion::ninguno && enemigo->intentarAvanzar(elegida, mapa, otrosEnemigos, indiceActual)) {
			dirRodeo = elegida;
			pasosRodeo = 8; // Rodea 1 bloque completo antes de volver a intentar hacia el jugador
			return;
		}
	} else if ((dirPrincipal == EDireccion::izquierda || dirPrincipal == EDireccion::derecha) && mismaFila) {
		bool arrLibre = enemigo->puedeMoverEnemigo(enemigo->getX(), enemigo->getY() - 1, mapa, otrosEnemigos, indiceActual);
		bool abjLibre = enemigo->puedeMoverEnemigo(enemigo->getX(), enemigo->getY() + 1, mapa, otrosEnemigos, indiceActual);

		EDireccion elegida = EDireccion::ninguno;
		if (arrLibre && abjLibre) {
			elegida = (std::rand() % 2 == 0) ? EDireccion::arriba : EDireccion::abajo;
		} else if (arrLibre) {
			elegida = EDireccion::arriba;
		} else if (abjLibre) {
			elegida = EDireccion::abajo;
		}

		if (elegida != EDireccion::ninguno && enemigo->intentarAvanzar(elegida, mapa, otrosEnemigos, indiceActual)) {
			dirRodeo = elegida;
			pasosRodeo = 8;
			return;
		}
	}

	// 3. Alternativas normales si no estaba alineado o los lados directos estaban cerrados
	EDireccion alternativas[3] = { dirSecundaria, dirOpuestaSec, dirOpuestaPrin };
	for (int k = 0; k < 3; k++) {
		if (enemigo->intentarAvanzar(alternativas[k], mapa, otrosEnemigos, indiceActual)) {
			dirRodeo = alternativas[k];
			pasosRodeo = 4;
			return;
		}
	}
}
