#include "Jugador.h"
#include "Mapa.h"

CJugador::CJugador(short id, int posX, int posY, int vidas) : CTanque(id, posX, posY, vidas) {
	this->nombre = "Jugador 1";
	this->puntuacion = 0;
	this->setDireccion(EDireccion::arriba);
}

void CJugador::setNombre(std::string nombre) {
	this->nombre = nombre;
}
void CJugador::setPuntuacion(int puntuacion) {
	this->puntuacion = puntuacion;
}
std::string CJugador::getNombre() {
	return this->nombre;
}
int CJugador::getPuntuacion() {
	return this->puntuacion;
}

void CJugador::dibujar(Graphics^ g, Bitmap^ bmpTanques) {
	dibujarSprite(g, bmpTanques, FILA_JUGADOR, 0);
}

bool CJugador::puedeMover(int nuevoX, int nuevoY, CMapa* mapa) {
	// Límites del mapa en pantalla (13 x 13 bloques de 64x64)
	if (nuevoX < 0 || nuevoY < 0) return false;
	if (nuevoX + ANCHO_TANQUE > MAX_COLUMNAS * ANCHO_IMAGEN) return false;
	if (nuevoY + ALTO_TANQUE > MAX_FILAS * ALTO_IMAGEN) return false;

	if (mapa != nullptr) {
		int colInicio = nuevoX / ANCHO_IMAGEN;
		int colFin = (nuevoX + ANCHO_TANQUE - 1) / ANCHO_IMAGEN;
		int filInicio = nuevoY / ALTO_IMAGEN;
		int filFin = (nuevoY + ALTO_TANQUE - 1) / ALTO_IMAGEN;

		for (int f = filInicio; f <= filFin; f++) {
			for (int c = colInicio; c <= colFin; c++) {
				CBloque* b = mapa->getBloque(f, c);
				if (b == nullptr) return false;
				ETipoBloque tipo = b->getTipo();
				// Solo piso y árbol son transitables para el tanque
				if (tipo != ETipoBloque::piso && tipo != ETipoBloque::arbol) {
					return false;
				}
			}
		}
	}
	return true;
}

void CJugador::mover(EDireccion direccion, CMapa* mapa) {
	this->setDireccion(direccion);

	int vel = this->getVelocidad();
	int actX = this->getX();
	int actY = this->getY();

	// Alineación suave a la cuadrícula (corner snapping estilo Battle City)
	if (direccion == EDireccion::arriba || direccion == EDireccion::abajo) {
		int restoX = actX % ANCHO_IMAGEN;
		if (restoX != 0) {
			if (restoX <= vel && puedeMover(actX - restoX, actY, mapa)) {
				actX -= restoX;
				this->setX(actX);
			} else if ((ANCHO_IMAGEN - restoX) <= vel && puedeMover(actX + (ANCHO_IMAGEN - restoX), actY, mapa)) {
				actX += (ANCHO_IMAGEN - restoX);
				this->setX(actX);
			}
		}
	} else if (direccion == EDireccion::izquierda || direccion == EDireccion::derecha) {
		int restoY = actY % ALTO_IMAGEN;
		if (restoY != 0) {
			if (restoY <= vel && puedeMover(actX, actY - restoY, mapa)) {
				actY -= restoY;
				this->setY(actY);
			} else if ((ALTO_IMAGEN - restoY) <= vel && puedeMover(actX, actY + (ALTO_IMAGEN - restoY), mapa)) {
				actY += (ALTO_IMAGEN - restoY);
				this->setY(actY);
			}
		}
	}

	// Movimiento paso a paso para colisión precisa
	int dx = 0, dy = 0;
	switch (direccion) {
	case EDireccion::arriba:    dy = -1; break;
	case EDireccion::abajo:     dy =  1; break;
	case EDireccion::izquierda: dx = -1; break;
	case EDireccion::derecha:   dx =  1; break;
	default: break;
	}

	for (int i = 0; i < vel; i++) {
		int proxX = this->getX() + dx;
		int proxY = this->getY() + dy;
		if (puedeMover(proxX, proxY, mapa)) {
			this->setX(proxX);
			this->setY(proxY);
		} else {
			break;
		}
	}
}

void CJugador::mover(CMapa* mapa) {
	mover(this->getDireccion(), mapa);
}

void CJugador::mover() {
	mover(this->getDireccion(), nullptr);
}