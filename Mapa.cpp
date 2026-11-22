#include "Mapa.h"

CMapa::CMapa() {
};

void CMapa::setNivel(int nivel) {
    this->nivel = nivel;
}

int CMapa::getNivel() {
    return this->nivel;
}

CBloque* CMapa::getBloque(int i, int j) {
    if (i < 0 || i >= MAX_FILAS || j < 0 || j >= MAX_COLUMNAS) return nullptr;
    return mapa[i][j];
}

CBloque* (*CMapa::getMapa())[MAX_COLUMNAS] {
    return this->mapa;
}

void CMapa::nivel1() {
    int tmpNivel1[MAX_FILAS][MAX_COLUMNAS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  
    {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},  
    {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},  
    {1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 1},  
    {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},  
    {1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},  
    {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},  
    {3, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 3},  
    {1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1},  
    {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},  
    {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},  
    {1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1},  
    {1, 1, 1, 1, 1, 2, 9, 2, 1, 1, 1, 1, 1}   
    };

    std::cout << "Inicializando nivel 1\n";
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            if (tmpNivel1[i][j] == 1) {
                mapa[i][j] = new CBloque(ETipoBloque::piso, 0);
            }
            if (tmpNivel1[i][j] == 2) {
                mapa[i][j] = new CBloque(ETipoBloque::destruible, 2);
            }
            if (tmpNivel1[i][j] == 3) {
                mapa[i][j] = new CBloque(ETipoBloque::noDestruible, -1);
            }
            if (tmpNivel1[i][j] == 9) {
                mapa[i][j] = new CBloque(ETipoBloque::trofeo, 1);
            }
        }
    }
}

void CMapa::nivel2() {
    int tmpNivel2[MAX_FILAS][MAX_COLUMNAS] = {
        {1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1},
        {3, 1, 2, 1, 1, 2, 1, 1, 1, 3, 3, 3, 1},
        {3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 1, 2, 2, 2, 1, 2, 2, 1, 4, 4, 1, 4},
        {1, 1, 2, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1},
        {1, 2, 2, 1, 4, 4, 1, 4, 4, 4, 1, 1, 1},
        {4, 4, 4, 1, 4, 4, 1, 2, 1, 1, 1, 3, 1},
        {1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 3, 1},
        {4, 4, 4, 1, 4, 1, 3, 1, 2, 1, 1, 2, 2},
        {1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1},
        {2, 2, 2, 1, 1, 2, 2, 2, 1, 2, 1, 1, 1},
        {2, 1, 1, 1, 1, 2, 9, 2, 1, 1, 1, 1, 1}
    };

    std::cout << "Inicializando nivel 2 exacto desde cuadricula\n";
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            if (tmpNivel2[i][j] == 1) mapa[i][j] = new CBloque(ETipoBloque::piso, 0);
            if (tmpNivel2[i][j] == 2) mapa[i][j] = new CBloque(ETipoBloque::destruible, 2);
            if (tmpNivel2[i][j] == 3) mapa[i][j] = new CBloque(ETipoBloque::noDestruible, -1);
            if (tmpNivel2[i][j] == 4) mapa[i][j] = new CBloque(ETipoBloque::agua, -1);
            if (tmpNivel2[i][j] == 9) mapa[i][j] = new CBloque(ETipoBloque::trofeo, 1);
        }
    }
}

void CMapa::nivel3() {
    int tmpNivel3[MAX_FILAS][MAX_COLUMNAS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  
        {5, 5, 1, 1, 1, 2, 2, 2, 1, 1, 1, 5, 5},  
        {5, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 5},  
        {1, 1, 1, 2, 2, 5, 2, 5, 2, 2, 1, 1, 1},  
        {1, 1, 1, 2, 5, 5, 5, 5, 5, 2, 1, 1, 1},  
        {5, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 5},  
        {5, 5, 1, 1, 2, 5, 2, 5, 2, 1, 1, 5, 5},  
        {4, 4, 4, 1, 2, 2, 2, 2, 2, 1, 4, 4, 4},  
        {1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1},  
        {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},  
        {3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3},  
        {2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2},  
        {3, 3, 3, 3, 1, 2, 9, 2, 1, 3, 3, 3, 3}   
    };

    std::cout << "Inicializando nivel 3\n";
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            switch (tmpNivel3[i][j]) {
            case 1: mapa[i][j] = new CBloque(ETipoBloque::piso, 0); break;
            case 2: mapa[i][j] = new CBloque(ETipoBloque::destruible, 2); break;
            case 3: mapa[i][j] = new CBloque(ETipoBloque::noDestruible, -1); break;
            case 4: mapa[i][j] = new CBloque(ETipoBloque::agua, -1); break;
            case 5: mapa[i][j] = new CBloque(ETipoBloque::arbol, -1); break;
            case 9: mapa[i][j] = new CBloque(ETipoBloque::trofeo, 1); break;
            }
        }
    }
}
void CMapa::nivel4() {
    int tmpNivel4[MAX_FILAS][MAX_COLUMNAS] = {
        {5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 5},  
        {5, 5, 1, 1, 2, 2, 2, 2, 2, 1, 5, 5, 5},  
        {5, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 3},  
        {3, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},  
        {1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 1, 2, 1},  
        {4, 1, 2, 1, 3, 1, 3, 1, 2, 2, 1, 1, 1},  
        {4, 1, 2, 1, 1, 1, 1, 1, 2, 2, 1, 4, 4},  
        {1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},  
        {1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},  
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},  
        {1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 5},  
        {5, 2, 2, 1, 1, 2, 2, 2, 2, 2, 1, 5, 5},  
        {3, 5, 1, 1, 1, 2, 9, 2, 1, 1, 5, 5, 3}    
    };

    std::cout << "Inicializando nivel 4\n";
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            switch (tmpNivel4[i][j]) {
            case 1: mapa[i][j] = new CBloque(ETipoBloque::piso, 0); break;
            case 2: mapa[i][j] = new CBloque(ETipoBloque::destruible, 2); break;
            case 3: mapa[i][j] = new CBloque(ETipoBloque::noDestruible, -1); break;
            case 4: mapa[i][j] = new CBloque(ETipoBloque::agua, -1); break;
            case 5: mapa[i][j] = new CBloque(ETipoBloque::arbol, -1); break;
            case 9: mapa[i][j] = new CBloque(ETipoBloque::trofeo, 1); break;
            }
        }
    }
}

void CMapa::nivel5() {
    int tmpNivel5[MAX_FILAS][MAX_COLUMNAS] = {
        {2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2},  
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1}, 
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1},  
        {4, 4, 4, 2, 2, 2, 4, 4, 4, 1, 3, 1, 4},  
        {4, 4, 4, 2, 2, 2, 4, 4, 4, 1, 3, 1, 4},  
        {1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 2, 1, 1},  
        {2, 2, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2},  
        {2, 2, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1},  
        {1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2},  
        {1, 2, 2, 2, 3, 1, 1, 1, 2, 1, 2, 2, 3},  
        {1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  
        {1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 1},  
        {1, 1, 2, 1, 1, 2, 9, 2, 1, 2, 1, 2, 1}   
    };

    std::cout << "Inicializando nivel 5\n";
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            switch (tmpNivel5[i][j]) {
            case 1: mapa[i][j] = new CBloque(ETipoBloque::piso, 0); break;
            case 2: mapa[i][j] = new CBloque(ETipoBloque::destruible, 2); break;
            case 3: mapa[i][j] = new CBloque(ETipoBloque::noDestruible, -1); break;
            case 4: mapa[i][j] = new CBloque(ETipoBloque::agua, -1); break;
            case 5: mapa[i][j] = new CBloque(ETipoBloque::arbol, -1); break;
            case 9: mapa[i][j] = new CBloque(ETipoBloque::trofeo, 1); break;
            }
        }
    }
}

void CMapa::DibujarMapa(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo) {
    int X = 0, Y = 0;
    for (int i = 0; i < MAX_FILAS; i++) {
        X = 0;
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            if (getBloque(i, j)->getTipo() == ETipoBloque::piso) {
                Rectangle rectPiso = Rectangle(0 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN, ALTO_IMAGEN);
                g->DrawImage(bmpPiso, zoom, rectPiso, GraphicsUnit::Pixel);
            }
            if (getBloque(i, j)->getTipo() == ETipoBloque::destruible) {
                Rectangle rectDestruible = Rectangle(1 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN, ALTO_IMAGEN);
                g->DrawImage(bmpBloques, zoom, rectDestruible, GraphicsUnit::Pixel);
            }
            if (getBloque(i, j)->getTipo() == ETipoBloque::noDestruible) {
                Rectangle rectNoDestruible = Rectangle(0 * ANCHO_IMAGEN, 1 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN, ALTO_IMAGEN);
                g->DrawImage(bmpBloques, zoom, rectNoDestruible, GraphicsUnit::Pixel);
            }
            if (getBloque(i, j)->getTipo() == ETipoBloque::trofeo) {
                Rectangle rectTrofeo = Rectangle(0, 0, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN, ALTO_IMAGEN);
                g->DrawImage(bmpTrofeo, zoom, rectTrofeo, GraphicsUnit::Pixel);
            }
            // /////////////
            if (getBloque(i, j)->getTipo() == ETipoBloque::agua) {
                Rectangle rectAgua = Rectangle(2 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN, ALTO_IMAGEN);
                g->DrawImage(bmpBloques, zoom, rectAgua, GraphicsUnit::Pixel);
            }
            if (getBloque(i, j)->getTipo() == ETipoBloque::arbol) {
                Rectangle rectArbol = Rectangle(1 * ANCHO_IMAGEN, 1 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN, ALTO_IMAGEN);
                g->DrawImage(bmpBloques, zoom, rectArbol, GraphicsUnit::Pixel);
            }

            X += ANCHO_IMAGEN;
        }
        Y += ALTO_IMAGEN;
    }
}