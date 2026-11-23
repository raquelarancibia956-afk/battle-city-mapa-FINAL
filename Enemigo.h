#pragma once
#include <vector>
#include "Tanque.h"
#include "IEstrategiaMovimiento.h"

enum ETipoTanque {
	tipo1,
	tipo2,
	tipo3,
	tipo4,
	tipo5
};

class CMapa;

class CEnemigo : public CTanque {
	ETipoTanque tipo;
	IEstrategiaMovimiento* estrategia;
	int objX;
	int objY;
public:
	CEnemigo(short id, short tipo, int posx, int posy, int vidas);
	~CEnemigo() override;
	void setTipo(ETipoTanque tipo);
	ETipoTanque getTipo();
	void setEstrategia(IEstrategiaMovimiento* nuevaEstrategia);

	void dibujar(Graphics^ g, Bitmap^ bmpTanques) override;
	void mover(int jugadorX, int jugadorY, CMapa* mapa, const std::vector<CEnemigo*>* otrosEnemigos = nullptr, int indiceActual = -1);
	bool puedeMoverEnemigo(int nx, int ny, CMapa* mapa, const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual);
	bool intentarAvanzar(EDireccion dir, CMapa* mapa, const std::vector<CEnemigo*>* otrosEnemigos, int indiceActual);
};