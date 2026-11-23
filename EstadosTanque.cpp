#include "EstadosTanque.h"
#include "Tanque.h"

void EstadoNormal::aplicar(CTanque* tanque) {
	if (tanque != nullptr) {
		tanque->setVelocidad(20);
	}
}
const char* EstadoNormal::getNombre() const {
	return "Normal";
}

void EstadoRapido::aplicar(CTanque* tanque) {
	if (tanque != nullptr) {
		tanque->setVelocidad(36);
	}
}
const char* EstadoRapido::getNombre() const {
	return "Rapido";
}
