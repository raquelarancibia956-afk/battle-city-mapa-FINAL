#pragma once
#include "Comun.h"

class CBloque {
	int posX;
	int posY;
	ETipoBloque tipo;
	short durabilidad;

public:
	CBloque(ETipoBloque tipo, int dureza);
	~CBloque();

	void setTipo(ETipoBloque tipo);
	ETipoBloque getTipo();
	void setDurabilidad(short durabilidad);
	short getDurabilidad();
};
