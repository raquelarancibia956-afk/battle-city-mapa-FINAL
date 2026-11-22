#pragma once
#include "Mapa.h"
#include "Jugador.h"
#include "CColeccionEnemigo.h"  

class CControladora {
private:
	CMapa* mapa;
	/// /////////////
	CJugador* jugador;
	CColeccionEnemigo* enemigos;

public:
	CControladora();
	~CControladora() {};

	void Inicializar();
	void InicializarNivel2();
	void InicializarNivel3();
	void InicializarNivel4();
	void InicializarNivel5();
	void DibujarMapa(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo);
	void DibujarTanques(Graphics^ g, Bitmap^ bmpTanques);
	void Actualizar();
	void MoverJugador(EDireccion direccion);
	CJugador* GetJugador();
	CMapa* GetMapa();
};