#pragma once
#include "IEstadoTanque.h"

class EstadoNormal : public IEstadoTanque {
public:
	void aplicar(CTanque* tanque) override;
	const char* getNombre() const override;
};

class EstadoRapido : public IEstadoTanque {
public:
	void aplicar(CTanque* tanque) override;
	const char* getNombre() const override;
};
