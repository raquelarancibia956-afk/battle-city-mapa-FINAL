#include "Proyectil.h"
#include "Mapa.h"

Proyectil::Proyectil(int x, int y, EDireccion dir, bool esDelJugador) {
	this->ancho = 10;
	this->alto = 10;
	this->posX = x - this->ancho / 2;
	this->posY = y - this->alto / 2;
	this->velocidad = 16;
	this->direccion = (dir == EDireccion::ninguno) ? EDireccion::arriba : dir;
	this->activo = true;
	this->esDelJugador = esDelJugador;
}

void Proyectil::mover(CMapa* mapa) {
	if (!activo) return;

	int dx = 0, dy = 0;
	switch (direccion) {
	case EDireccion::arriba:    dy = -velocidad; break;
	case EDireccion::abajo:     dy =  velocidad; break;
	case EDireccion::izquierda: dx = -velocidad; break;
	case EDireccion::derecha:   dx =  velocidad; break;
	default: break;
	}

	posX += dx;
	posY += dy;

	// Limites del mapa
	if (posX < 0 || posY < 0 ||
		posX + ancho > MAX_COLUMNAS * ANCHO_IMAGEN ||
		posY + alto > MAX_FILAS * ALTO_IMAGEN) {
		activo = false;
		return;
	}

	// Colision con bloques del mapa
	if (mapa != nullptr) {
		int centroX = posX + ancho / 2;
		int centroY = posY + alto / 2;
		int col = centroX / ANCHO_IMAGEN;
		int fila = centroY / ALTO_IMAGEN;

		CBloque* bloque = mapa->getBloque(fila, col);
		if (bloque != nullptr) {
			ETipoBloque tipo = bloque->getTipo();
			if (tipo == ETipoBloque::destruible || tipo == ETipoBloque::arbol) {
				short dur = bloque->getDurabilidad() - 1;
				bloque->setDurabilidad(dur);
				if (dur <= 0) {
					bloque->setTipo(ETipoBloque::piso);
				}
				activo = false;
			} else if (tipo == ETipoBloque::noDestruible || tipo == ETipoBloque::trofeo) {
				activo = false;
			}
		}
	}
}

void Proyectil::dibujar(Graphics^ g) {
	if (!activo) return;
	Brush^ brocha = esDelJugador ? Brushes::Gold : Brushes::OrangeRed;
	g->FillEllipse(brocha, posX, posY, ancho, alto);
}

int Proyectil::getX() const { return posX; }
int Proyectil::getY() const { return posY; }
int Proyectil::getAncho() const { return ancho; }
int Proyectil::getAlto() const { return alto; }
bool Proyectil::estaActivo() const { return activo; }
void Proyectil::desactivar() { activo = false; }
bool Proyectil::getEsDelJugador() const { return esDelJugador; }
