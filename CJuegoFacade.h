#pragma once
#include "Mapa.h"
#include "Jugador.h"
#include "CColeccionEnemigo.h"
#include "FEnemigoM.h"

class CJuegoFacade {
	CMapa* mapa;
	CJugador* jugador;
	CColeccionEnemigo* enemigos;
public:
	CJuegoFacade();
	~CJuegoFacade();

	// Interfaz simple para el cliente
	void iniciarNivel(int nivel, int cantidadEnemigos);
	void dibujarEscena(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques,
		Bitmap^ bmpTrofeo, Bitmap^ bmpTanques);
	void actualizar();
	void moverJugador(EDireccion direccion);
	CJugador* getJugador();
	CMapa* getMapa();
};