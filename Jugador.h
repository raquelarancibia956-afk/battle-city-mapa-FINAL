#pragma once
#include <string>
#include "Tanque.h"

class CMapa;
class CColeccionEnemigo;

class CJugador : public CTanque {
	std::string nombre;
	int puntuacion;
public:
	CJugador(short id, int posX, int posY, int vidas);
	void setNombre(std::string nombre);
	void setPuntuacion(int puntuacion);
	std::string getNombre();
	int getPuntuacion();

	void dibujar(Graphics^ g, Bitmap^ bmpTanques) override;
	void mover();
	void mover(CMapa* mapa);
	void mover(EDireccion direccion, CMapa* mapa = nullptr, CColeccionEnemigo* enemigos = nullptr);
	bool puedeMover(int nuevoX, int nuevoY, CMapa* mapa, CColeccionEnemigo* enemigos = nullptr);
};