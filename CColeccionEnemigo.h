#pragma once
#include <vector>
#include "Enemigo.h"
#include "CFabricaEnemigo.h"
#include "Mapa.h"   // NUEVO

class CColeccionEnemigo {
	std::vector<CEnemigo*> enemigos;
	short siguienteId;
public:
	CColeccionEnemigo();
	~CColeccionEnemigo();

	void crear(CFabricaEnemigo* fabrica, int x, int y);
	void crearVarios(CFabricaEnemigo* fabrica, int cantidad, CMapa* mapa);   // CAMBIA: recibe el mapa
	void eliminar(int indice);
	void limpiar();
	CEnemigo* obtener(int indice);
	int cantidad();
	void mover(int jugadorX, int jugadorY, CMapa* mapa);
	void dibujar(Graphics^ g, Bitmap^ bmpTanques);
};