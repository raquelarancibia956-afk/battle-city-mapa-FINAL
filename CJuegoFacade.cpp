#include "CJuegoFacade.h"
#include "Comun.h"

CJuegoFacade::CJuegoFacade() {
	mapa = new CMapa();
	jugador = new CJugador(1, 4 * ANCHO_IMAGEN, 12 * ALTO_IMAGEN, 3);
	enemigos = new CColeccionEnemigo();
}

CJuegoFacade::~CJuegoFacade() {
	delete mapa;
	delete jugador;
	delete enemigos;
}

void CJuegoFacade::iniciarNivel(int nivel, int cantidadEnemigos) {
	enemigos->limpiar();   

	switch (nivel) {
	case 1: mapa->nivel1(); break;
	case 2: mapa->nivel2(); break;
	case 3: mapa->nivel3(); break;
	case 4: mapa->nivel4(); break;
	case 5: mapa->nivel5(); break;
	}
	if (jugador != nullptr) {
		jugador->setX(4 * ANCHO_IMAGEN);
		jugador->setY(12 * ALTO_IMAGEN);
		jugador->setDireccion(EDireccion::arriba);
	}
	FEnemigoM fabrica;
	enemigos->crearVarios(&fabrica, cantidadEnemigos, mapa);   
}

void CJuegoFacade::moverJugador(EDireccion direccion) {
	if (jugador != nullptr) {
		jugador->mover(direccion, mapa);
	}
}

CJugador* CJuegoFacade::getJugador() {
	return jugador;
}

CMapa* CJuegoFacade::getMapa() {
	return mapa;
}

void CJuegoFacade::actualizar() {
	if (jugador != nullptr && enemigos != nullptr && mapa != nullptr) {
		enemigos->mover(jugador->getX(), jugador->getY(), mapa);
	}
}

void CJuegoFacade::dibujarEscena(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques,
	Bitmap^ bmpTrofeo, Bitmap^ bmpTanques) {
	actualizar();
	mapa->DibujarMapa(g, bmpPiso, bmpBloques, bmpTrofeo);
	jugador->dibujar(g, bmpTanques);
	enemigos->dibujar(g, bmpTanques);
}