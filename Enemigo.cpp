#include "Enemigo.h"
#include "Mapa.h"
#include "EstrategiaPerseguir.h"
#include <cmath>

CEnemigo::CEnemigo(short id, short tipo, int posx, int posy, int vidas) : CTanque(id, posx, posy, vidas) {
	this->tipo = (ETipoTanque)tipo;
	this->setDireccion(EDireccion::abajo);
	this->setVelocidad(8);
	this->estrategia = new EstrategiaPerseguir();
	this->objX = -1000;
	this->objY = -1000;
}

CEnemigo::~CEnemigo() {
	delete estrategia;
	estrategia = nullptr;
}

void CEnemigo::setTipo(ETipoTanque tipo) {
	this->tipo = tipo;
}
ETipoTanque CEnemigo::getTipo() {
	return this->tipo;
}

void CEnemigo::setEstrategia(IEstrategiaMovimiento* nuevaEstrategia) {
	if (nuevaEstrategia != nullptr && nuevaEstrategia != this->estrategia) {
		delete this->estrategia;
		this->estrategia = nuevaEstrategia;
	}
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

	// Evitar superposición con el jugador
	if (objX >= 0 && objY >= 0) {
		if (nx < objX + ANCHO_TANQUE &&
			nx + ANCHO_TANQUE > objX &&
			ny < objY + ALTO_TANQUE &&
			ny + ALTO_TANQUE > objY) {
			return false;
		}
	}

	if (otrosEnemigos != nullptr) {
		for (size_t i = 0; i < otrosEnemigos->size(); i++) {
			if ((int)i != indiceActual && (*otrosEnemigos)[i] != nullptr) {
				CEnemigo* otro = (*otrosEnemigos)[i];
				if (nx < otro->getX() + ANCHO_TANQUE &&
					nx + ANCHO_TANQUE > otro->getX() &&
					ny < otro->getY() + ALTO_TANQUE &&
					ny + ALTO_TANQUE > otro->getY()) {
					return false;
				}
			}
		}
	}
	return true;
}

bool CEnemigo::intentarAvanzar(EDireccion dir, CMapa* mapa, const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual) {
	if (dir == EDireccion::ninguno) return false;

	int vel = this->getVelocidad();
	if (vel <= 0) vel = 4;

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
		return true;
	}
	return false;
}

void CEnemigo::mover(int jugadorX, int jugadorY, CMapa* mapa, const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual) {
	this->objX = jugadorX;
	this->objY = jugadorY;

	int dx = jugadorX - this->getX();
	int dy = jugadorY - this->getY();
	bool mismaColumna = (std::abs(dx) < ANCHO_TANQUE / 2);
	bool mismaFila = (std::abs(dy) < ALTO_TANQUE / 2);
	int gapY = std::abs(dy) - ALTO_TANQUE;
	int gapX = std::abs(dx) - ANCHO_TANQUE;

	// Detenerse como maximo a 1 casilla en direccion ortogonal al jugador (no en diagonal)
	if (mismaColumna && gapY <= ALTO_IMAGEN) {
		this->setDireccion((dy > 0) ? EDireccion::abajo : EDireccion::arriba);
		return;
	}
	if (mismaFila && gapX <= ANCHO_IMAGEN) {
		this->setDireccion((dx > 0) ? EDireccion::derecha : EDireccion::izquierda);
		return;
	}

	if (estrategia != nullptr) {
		estrategia->mover(this, jugadorX, jugadorY, mapa, otrosEnemigos, indiceActual);
	}
}
