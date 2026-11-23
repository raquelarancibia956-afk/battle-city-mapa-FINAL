#include "Tanque.h"
#include "Mapa.h"
#include "EstadosTanque.h"

CTanque::CTanque(short id, int posX, int posY, int vidas) {
	this->id = id;
	this->vidas = vidas;
	this->velocidad = 20;
	this->posX = posX;
	this->posY = posY;
	this->direccion = EDireccion::arriba;
	this->estado = new EstadoNormal();
}

CTanque::~CTanque() {
	delete estado;
	estado = nullptr;
}

void CTanque::setEstado(IEstadoTanque* nuevoEstado) {
	if (nuevoEstado != nullptr && nuevoEstado != this->estado) {
		delete this->estado;
		this->estado = nuevoEstado;
		this->estado->aplicar(this);
	}
}

IEstadoTanque* CTanque::getEstado() {
	return this->estado;
}

void CTanque::setId(short id) {
	this->id = id;
}
void CTanque::setVidas(short vidas) {
	this->vidas = vidas;
}
void CTanque::setDireccion(EDireccion direccion) {
	this->direccion = direccion;
}
void CTanque::setVelocidad(short velocidad) {
	this->velocidad = velocidad;
}
void CTanque::setX(int posX) {
	this->posX = posX;
}
void CTanque::setY(int posY) {
	this->posY = posY;
}

short CTanque::getId() {
	return this->id;
}
short CTanque::getVidas() {
	return this->vidas;
}
EDireccion CTanque::getDireccion() {
	return this->direccion;
}
short CTanque::getVelocidad() {
	return this->velocidad;
}
int CTanque::getX() {
	return this->posX;
}
int CTanque::getY() {
	return this->posY;
}
//////////////////////////////////
void CTanque::dibujarSprite(Graphics^ g, Bitmap^ bmpTanques, int filaBase, int columna) {
	// Orden de las filas en tanques.png: arriba, derecha, abajo, izquierda
	int desplazamiento = 0;
	switch (direccion) {
	case EDireccion::arriba:    desplazamiento = 0; break;
	case EDireccion::derecha:   desplazamiento = 1; break;
	case EDireccion::abajo:     desplazamiento = 2; break;
	case EDireccion::izquierda: desplazamiento = 3; break;
	default: break;
	}

	Rectangle origen = Rectangle(columna * ANCHO_TANQUE,
		(filaBase + desplazamiento) * ALTO_TANQUE,
		ANCHO_TANQUE, ALTO_TANQUE);
	Rectangle destino = Rectangle(posX, posY, ANCHO_IMAGEN, ALTO_IMAGEN);
	g->DrawImage(bmpTanques, destino, origen, GraphicsUnit::Pixel);
}

bool CTanque::puedeMover(int nuevoX, int nuevoY, CMapa* mapa) {
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
				if (tipo != ETipoBloque::piso) {
					return false;
				}
			}
		}
	}
	return true;
}