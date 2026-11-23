#pragma once

class CTanque;

// Patron State: interfaz para el estado/power-up de un tanque
class IEstadoTanque {
public:
	virtual ~IEstadoTanque() {}
	virtual void aplicar(CTanque* tanque) = 0;
	virtual const char* getNombre() const = 0;
};
