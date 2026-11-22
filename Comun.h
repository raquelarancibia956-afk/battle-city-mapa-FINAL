#pragma once
#define MAX_FILAS 13
#define MAX_COLUMNAS 13

////////////////
#define ANCHO_IMAGEN 64
#define ALTO_IMAGEN 64
#define ANCHO_TANQUE 64
#define ALTO_TANQUE 64
///////////////////
#define FILA_JUGADOR 0
#define FILA_ENEMIGO 8     
#define FILAS_POR_TIPO 4
#define MAX_TIPOS_ENEMIGO 4

enum ETipoBloque {
	piso = 1,
	destruible,
	noDestruible,
	agua,
	arbol,
	trofeo
};

enum EDireccion {
	ninguno,
	arriba,
	abajo,
	izquierda,
	derecha
};

class CComun {

};

