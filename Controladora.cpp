#include "Controladora.h"
#include "FEnemigoM.h"

CControladora::CControladora() {
	mapa = new CMapa();
	jugador = new CJugador(1, 4 * ANCHO_IMAGEN, 12 * ALTO_IMAGEN, 3);
	enemigos = new CColeccionEnemigo();

	mapa->nivel1();                          
	FEnemigoM fabrica;
	enemigos->crearVarios(&fabrica, 4, mapa); 
}
void CControladora::Inicializar() {
	mapa->nivel1();
};

void CControladora::InicializarNivel2() {
	mapa->nivel2();
};
void CControladora::InicializarNivel3() {
	mapa->nivel3();
};
void CControladora::InicializarNivel4() {
	mapa->nivel4();
};
void CControladora::InicializarNivel5() {
	mapa->nivel5();
};

void CControladora::DibujarMapa(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo) {
	mapa->DibujarMapa(g, bmpPiso, bmpBloques, bmpTrofeo);
};

void CControladora::DibujarTanques(Graphics^ g, Bitmap^ bmpTanques) {
	Actualizar();
	jugador->dibujar(g, bmpTanques);
	enemigos->dibujar(g, bmpTanques);
}

void CControladora::Actualizar() {
	if (jugador != nullptr && enemigos != nullptr && mapa != nullptr) {
		enemigos->mover(jugador->getX(), jugador->getY(), mapa);
	}
}

void CControladora::MoverJugador(EDireccion direccion) {
	if (jugador != nullptr) {
		jugador->mover(direccion, mapa);
	}
}

CJugador* CControladora::GetJugador() {
	return jugador;
}

CMapa* CControladora::GetMapa() {
	return mapa;
}