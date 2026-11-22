#pragma once
#include "Comun.h"

using namespace System::Drawing;

class CMapa;

class CTanque {
	short id;
	short vidas;
	EDireccion direccion;
	short velocidad;
	int posX;
	int posY;
	short powerups[99];
protected:
	/// /////////////////////////////
	void dibujarSprite(Graphics^ g, Bitmap^ bmpTanques, int filaBase, int columna);
public:
	CTanque(short id, int posX, int posY, int vidas);
	virtual ~CTanque();
	void setId(short id);
	void setVidas(short vidas);
	void setDireccion(EDireccion direccion);
	void setVelocidad(short velocidad);
	void setX(int posX);
	void setY(int posY);

	short getId();
	short getVidas();
	EDireccion getDireccion();
	short getVelocidad();
	int getX();
	int getY();

	bool puedeMover(int nuevoX, int nuevoY, CMapa* mapa);
	/// ///////////////////////////
	virtual void dibujar(Graphics^ g, Bitmap^ bmpTanques) = 0;
};