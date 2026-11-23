#pragma once
#include <string>

// Patron Observer: interfaz para los observadores de eventos del juego
class IObservadorJuego {
public:
	virtual ~IObservadorJuego() {}
	virtual void alCambiarEstado(int vidas, int puntuacion, int nivel, const std::string& estadoJugador) = 0;
};
