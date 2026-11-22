#include "Enemigo.h"
#include "Mapa.h"
#include <cmath>

CEnemigo::CEnemigo(short id, short tipo, int posx, int posy, int vidas) : CTanque(id, posx, posy, vidas) {
	this->tipo = (ETipoTanque)tipo;
	this->setDireccion(EDireccion::abajo);
	this->setVelocidad(4);
}

void CEnemigo::setTipo(ETipoTanque tipo) {
	this->tipo = tipo;
}
ETipoTanque CEnemigo::getTipo() {
	return this->tipo;
}

void CEnemigo::dibujar(Graphics^ g, Bitmap^ bmpTanques) {
	int t = (int)tipo;
	if (t >= MAX_TIPOS_ENEMIGO) t = MAX_TIPOS_ENEMIGO - 1;
	dibujarSprite(g, bmpTanques, FILA_ENEMIGO + t * FILAS_POR_TIPO, 0);
}

bool CEnemigo::puedeMoverEnemigo(int nx, int ny, CMapa* mapa, const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual) {
	if (!puedeMover(nx, ny, mapa)) {
		return false;
	}

	if (otrosEnemigos != nullptr) {
		int margen = 4;
		for (size_t i = 0; i < otrosEnemigos->size(); i++) {
			if ((int)i != indiceActual && (*otrosEnemigos)[i] != nullptr) {
				CEnemigo* otro = (*otrosEnemigos)[i];
				if (nx < otro->getX() + ANCHO_TANQUE - margen &&
					nx + ANCHO_TANQUE - margen > otro->getX() &&
					ny < otro->getY() + ALTO_TANQUE - margen &&
					ny + ALTO_TANQUE - margen > otro->getY()) {
					return false;
				}
			}
		}
	}
	return true;
}

void CEnemigo::mover(int jugadorX, int jugadorY, CMapa* mapa, const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual) {
	int dx = jugadorX - this->getX();
	int dy = jugadorY - this->getY();

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

	EDireccion opciones[4] = { dirPrincipal, dirSecundaria, dirOpuestaSec, dirOpuestaPrin };

	int vel = this->getVelocidad();
	if (vel <= 0) vel = 4;

	for (int k = 0; k < 4; k++) {
		EDireccion dir = opciones[k];
		if (dir == EDireccion::ninguno) continue;

		int actX = this->getX();
		int actY = this->getY();

		// Alineación a cuadrícula en giros (corner snapping)
		if (dir == EDireccion::arriba || dir == EDireccion::abajo) {
			int restoX = actX % ANCHO_IMAGEN;
			if (restoX != 0) {
				if (restoX <= vel && puedeMoverEnemigo(actX - restoX, actY, mapa, otrosEnemigos, indiceActual)) {
					actX -= restoX;
					this->setX(actX);
				} else if ((ANCHO_IMAGEN - restoX) <= vel && puedeMoverEnemigo(actX + (ANCHO_IMAGEN - restoX), actY, mapa, otrosEnemigos, indiceActual)) {
					actX += (ANCHO_IMAGEN - restoX);
					this->setX(actX);
				}
			}
		} else if (dir == EDireccion::derecha || dir == EDireccion::izquierda) {
			int restoY = actY % ALTO_IMAGEN;
			if (restoY != 0) {
				if (restoY <= vel && puedeMoverEnemigo(actX, actY - restoY, mapa, otrosEnemigos, indiceActual)) {
					actY -= restoY;
					this->setY(actY);
				} else if ((ALTO_IMAGEN - restoY) <= vel && puedeMoverEnemigo(actX, actY + (ALTO_IMAGEN - restoY), mapa, otrosEnemigos, indiceActual)) {
					actY += (ALTO_IMAGEN - restoY);
					this->setY(actY);
				}
			}
		}

		int stepX = 0, stepY = 0;
		switch (dir) {
		case EDireccion::arriba:    stepY = -1; break;
		case EDireccion::abajo:     stepY =  1; break;
		case EDireccion::derecha:   stepX =  1; break;
		case EDireccion::izquierda: stepX = -1; break;
		default: break;
		}

		if (puedeMoverEnemigo(this->getX() + stepX, this->getY() + stepY, mapa, otrosEnemigos, indiceActual)) {
			this->setDireccion(dir);
			for (int s = 0; s < vel; s++) {
				int nx = this->getX() + stepX;
				int ny = this->getY() + stepY;
				if (puedeMoverEnemigo(nx, ny, mapa, otrosEnemigos, indiceActual)) {
					this->setX(nx);
					this->setY(ny);
				} else {
					break;
				}
			}
			return;
		}
	}
}