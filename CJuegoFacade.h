#pragma once
#include <vector>
#include "Mapa.h"
#include "Jugador.h"
#include "CColeccionEnemigo.h"
#include "FEnemigoM.h"
#include "CSujetoJuego.h"
#include "CMarcadorObserver.h"
#include "Proyectil.h"

class CJuegoFacade : public CSujetoJuego {
	CMapa* mapa;
	CJugador* jugador;
	CColeccionEnemigo* enemigos;
	std::vector<Proyectil*> proyectiles;
	CMarcadorObserver* marcador;
	int nivelActual;
	bool juegoGanado;
	void limpiarProyectiles();
	bool jugadorEnTrofeo();
	void verificarAvanceNivel();
public:
	CJuegoFacade();
	~CJuegoFacade();

	// Interfaz simple para el cliente
	void iniciarNivel(int nivel, int cantidadEnemigos);
	void dibujarEscena(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques,
		Bitmap^ bmpTrofeo, Bitmap^ bmpTanques);
	void actualizar();
	void moverJugador(EDireccion direccion);
	void dispararJugador();
	void rotarEstadoJugador();
	CJugador* getJugador();
	CMapa* getMapa();
	CMarcadorObserver* getMarcador();
	bool estaGanado() const;
};
