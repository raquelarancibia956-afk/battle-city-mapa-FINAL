#include "CColeccionEnemigo.h"
#include "Comun.h"
#include "EstrategiaPerseguir.h"
#include "EstrategiaAleatoria.h"

CColeccionEnemigo::CColeccionEnemigo() {
	siguienteId = 100;
}

CColeccionEnemigo::~CColeccionEnemigo() {
	for (CEnemigo* e : enemigos) delete e;
	enemigos.clear();
}

void CColeccionEnemigo::crear(CFabricaEnemigo* fabrica, int x, int y) {
	enemigos.push_back(fabrica->crearEnemigo(siguienteId++, x, y));
}

// CAMBIA: solo coloca enemigos sobre bloques de tipo piso
void CColeccionEnemigo::crearVarios(CFabricaEnemigo* fabrica, int cantidad, CMapa* mapa) {
	int creados = 0;
	for (int i = 0; i < MAX_FILAS && creados < cantidad; i++) {
		for (int j = 0; j < MAX_COLUMNAS && creados < cantidad; j += 4) {
			if (mapa->getBloque(i, j)->getTipo() == ETipoBloque::piso) {
				crear(fabrica, j * ANCHO_IMAGEN, i * ALTO_IMAGEN);
				CEnemigo* nuevo = enemigos.back();
				if (creados % 2 == 0) {
					nuevo->setEstrategia(new EstrategiaPerseguir());
				} else {
					nuevo->setEstrategia(new EstrategiaAleatoria());
				}
				creados++;
			}
		}
	}
}

void CColeccionEnemigo::eliminar(int indice) {
	if (indice >= 0 && indice < (int)enemigos.size()) {
		delete enemigos[indice];
		enemigos.erase(enemigos.begin() + indice);
	}
}

void CColeccionEnemigo::limpiar() {
	for (CEnemigo* e : enemigos) delete e;
	enemigos.clear();
	siguienteId = 100;
}

CEnemigo* CColeccionEnemigo::obtener(int indice) {
	return enemigos[indice];
}

int CColeccionEnemigo::cantidad() {
	return (int)enemigos.size();
}

void CColeccionEnemigo::mover(int jugadorX, int jugadorY, CMapa* mapa) {
	for (size_t i = 0; i < enemigos.size(); i++) {
		if (enemigos[i] != nullptr) {
			enemigos[i]->mover(jugadorX, jugadorY, mapa, &enemigos, (int)i);
		}
	}
}

void CColeccionEnemigo::dibujar(Graphics^ g, Bitmap^ bmpTanques) {
	for (CEnemigo* e : enemigos) {
		e->dibujar(g, bmpTanques);
	}
}