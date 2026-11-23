#pragma once
#include "Comun.h"

using namespace System::Drawing;

class CMapa;

class Proyectil {
	int posX;
	int posY;
	int ancho;
	int alto;
	int velocidad;
	EDireccion direccion;
	bool activo;
	bool esDelJugador;

public:
	Proyectil(int x, int y, EDireccion direccion, bool esDelJugador = true);
	void mover(CMapa* mapa);
	void dibujar(Graphics^ g);

	int getX() const;
	int getY() const;
	int getAncho() const;
	int getAlto() const;
	bool estaActivo() const;
	bool getEsDelJugador() const;
	void desactivar();
};
