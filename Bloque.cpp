#include "Bloque.h"

CBloque::CBloque(ETipoBloque tipo, int durabilidad) {
	this->tipo = tipo;
	this->durabilidad = durabilidad;
}

CBloque::~CBloque() {}

void CBloque::setTipo(ETipoBloque tipo) {
	this->tipo = tipo;
}

ETipoBloque CBloque::getTipo() {
	return this->tipo;
}

void CBloque::setDurabilidad(short durabilidad) {
	this->durabilidad = durabilidad;
}

short CBloque::getDurabilidad() {
	return this->durabilidad;
}
