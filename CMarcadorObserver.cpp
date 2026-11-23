#include "CMarcadorObserver.h"
#include <iostream>

CMarcadorObserver::CMarcadorObserver() {
	vidas = 3;
	puntuacion = 0;
	nivel = 1;
	estadoJugador = "Normal";
}

void CMarcadorObserver::alCambiarEstado(int vidas, int puntuacion, int nivel, const std::string& estadoJugador) {
	this->vidas = vidas;
	this->puntuacion = puntuacion;
	this->nivel = nivel;
	this->estadoJugador = estadoJugador;

	std::cout << "[HUD] Nivel: " << nivel
		<< " | Vidas: " << vidas
		<< " | Puntos: " << puntuacion
		<< " | Estado: " << estadoJugador << std::endl;
}

int CMarcadorObserver::getVidas() const { return vidas; }
int CMarcadorObserver::getPuntuacion() const { return puntuacion; }
int CMarcadorObserver::getNivel() const { return nivel; }
std::string CMarcadorObserver::getEstadoJugador() const { return estadoJugador; }
