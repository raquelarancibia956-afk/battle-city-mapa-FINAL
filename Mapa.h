#pragma once
#include <iostream>
#include "Bloque.h"

using namespace System::Drawing;

class CMapa {
  static CMapa* instancia;
  CBloque* mapa[MAX_FILAS][MAX_COLUMNAS];
  int nivel;

  CMapa();
  CMapa(const CMapa&) = delete;
  void operator=(const CMapa&) = delete;

  public:
	static CMapa* getInstancia();
	void setNivel(int nivel);
	int getNivel();
	CBloque* getBloque(int i, int j);
	CBloque* (*getMapa())[MAX_COLUMNAS];
	void nivel1();
	////////////////////
	void nivel2();
	void nivel3();
	void nivel4();
	void nivel5();

	void DibujarMapa(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo);
};

