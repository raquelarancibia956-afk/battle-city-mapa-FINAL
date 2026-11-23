#pragma once
#include <vector>
#include <algorithm>
#include "IObservadorJuego.h"

// Patron Observer: clase sujeto que mantiene y notifica a los observadores
class CSujetoJuego {
	std::vector<IObservadorJuego*> observadores;
public:
	virtual ~CSujetoJuego() {}

	void agregarObservador(IObservadorJuego* obs) {
		if (obs != nullptr) {
			observadores.push_back(obs);
		}
	}

	void quitarObservador(IObservadorJuego* obs) {
		observadores.erase(
			std::remove(observadores.begin(), observadores.end(), obs),
			observadores.end()
		);
	}

	void notificar(int vidas, int puntuacion, int nivel, const std::string& estadoJugador) {
		for (IObservadorJuego* obs : observadores) {
			if (obs != nullptr) {
				obs->alCambiarEstado(vidas, puntuacion, nivel, estadoJugador);
			}
		}
	}
};
