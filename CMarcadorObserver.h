#pragma once
#include "IObservadorJuego.h"

// Observador concreto: mantiene el marcador y estado actual para mostrarlo en la interfaz
class CMarcadorObserver : public IObservadorJuego {
	int vidas;
	int puntuacion;
	int nivel;
	std::string estadoJugador;
public:
	CMarcadorObserver();
	void alCambiarEstado(int vidas, int puntuacion, int nivel, const std::string& estadoJugador) override;

	int getVidas() const;
	int getPuntuacion() const;
	int getNivel() const;
	std::string getEstadoJugador() const;
};
