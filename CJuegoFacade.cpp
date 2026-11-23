#include "CJuegoFacade.h"
#include "Comun.h"
#include "EstadosTanque.h"
#include <cstring>
#include <cstdlib>

static bool colisionaRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

CJuegoFacade::CJuegoFacade() {
	mapa = CMapa::getInstancia();
	jugador = new CJugador(1, 4 * ANCHO_IMAGEN, 12 * ALTO_IMAGEN, 3);
	enemigos = new CColeccionEnemigo();
	marcador = new CMarcadorObserver();
	nivelActual = 1;
	juegoGanado = false;
	agregarObservador(marcador);
}

CJuegoFacade::~CJuegoFacade() {
	limpiarProyectiles();
	quitarObservador(marcador);
	delete marcador;
	delete jugador;
	delete enemigos;
}

void CJuegoFacade::limpiarProyectiles() {
	for (Proyectil* p : proyectiles) {
		delete p;
	}
	proyectiles.clear();
}

void CJuegoFacade::iniciarNivel(int nivel, int cantidadEnemigos) {
	limpiarProyectiles();
	enemigos->limpiar();   
	nivelActual = nivel;
	juegoGanado = false;

	switch (nivel) {
	case 1: mapa->nivel1(); break;
	case 2: mapa->nivel2(); break;
	case 3: mapa->nivel3(); break;
	case 4: mapa->nivel4(); break;
	case 5: mapa->nivel5(); break;
	}
	if (jugador != nullptr) {
		jugador->setX(4 * ANCHO_IMAGEN);
		jugador->setY(12 * ALTO_IMAGEN);
		jugador->setDireccion(EDireccion::arriba);
		std::string nomEstado = jugador->getEstado() ? jugador->getEstado()->getNombre() : "Normal";
		notificar(jugador->getVidas(), jugador->getPuntuacion(), nivelActual, nomEstado);
	}
	FEnemigoM fabrica;
	enemigos->crearVarios(&fabrica, cantidadEnemigos, mapa);   
}

bool CJuegoFacade::jugadorEnTrofeo() {
	if (jugador == nullptr || mapa == nullptr) return false;

	int colInicio = jugador->getX() / ANCHO_IMAGEN;
	int colFin = (jugador->getX() + ANCHO_TANQUE - 1) / ANCHO_IMAGEN;
	int filInicio = jugador->getY() / ALTO_IMAGEN;
	int filFin = (jugador->getY() + ALTO_TANQUE - 1) / ALTO_IMAGEN;

	for (int f = filInicio; f <= filFin; f++) {
		for (int c = colInicio; c <= colFin; c++) {
			CBloque* b = mapa->getBloque(f, c);
			if (b != nullptr && b->getTipo() == ETipoBloque::trofeo) {
				return true;
			}
		}
	}
	return false;
}

void CJuegoFacade::verificarAvanceNivel() {
	if (juegoGanado || jugador == nullptr || enemigos == nullptr) return;

	if (enemigos->cantidad() == 0 && jugadorEnTrofeo()) {
		jugador->setPuntuacion(jugador->getPuntuacion() + 500);
		if (nivelActual < 5) {
			iniciarNivel(nivelActual + 1, 4);
		} else {
			juegoGanado = true;
			limpiarProyectiles();
			notificar(jugador->getVidas(), jugador->getPuntuacion(), nivelActual, "GANASTE");
		}
	}
}

void CJuegoFacade::moverJugador(EDireccion direccion) {
	if (jugador != nullptr && !juegoGanado) {
		jugador->mover(direccion, mapa, enemigos);
		verificarAvanceNivel();
	}
}

void CJuegoFacade::dispararJugador() {
	if (jugador == nullptr || juegoGanado) return;

	// Limitar a maximo 2 balas activas del jugador al mismo tiempo
	int activas = 0;
	for (Proyectil* p : proyectiles) {
		if (p != nullptr && p->estaActivo() && p->getEsDelJugador()) {
			activas++;
		}
	}
	if (activas >= 2) return;

	int centroX = jugador->getX() + ANCHO_TANQUE / 2;
	int centroY = jugador->getY() + ALTO_TANQUE / 2;
	proyectiles.push_back(new Proyectil(centroX, centroY, jugador->getDireccion(), true));
}

void CJuegoFacade::rotarEstadoJugador() {
	if (jugador == nullptr || jugador->getEstado() == nullptr) return;

	const char* actual = jugador->getEstado()->getNombre();
	if (std::strcmp(actual, "Normal") == 0) {
		jugador->setEstado(new EstadoRapido());
	} else {
		jugador->setEstado(new EstadoNormal());
	}
	notificar(jugador->getVidas(), jugador->getPuntuacion(), nivelActual, jugador->getEstado()->getNombre());
}

CJugador* CJuegoFacade::getJugador() {
	return jugador;
}

CMapa* CJuegoFacade::getMapa() {
	return mapa;
}

CMarcadorObserver* CJuegoFacade::getMarcador() {
	return marcador;
}

bool CJuegoFacade::estaGanado() const {
	return juegoGanado;
}

void CJuegoFacade::actualizar() {
	if (juegoGanado || jugador == nullptr || enemigos == nullptr || mapa == nullptr) return;

	// 1. Mover enemigos
	enemigos->mover(jugador->getX(), jugador->getY(), mapa);

	// 2. Disparo autonomo sencillo de los enemigos
	for (int i = 0; i < enemigos->cantidad(); i++) {
		CEnemigo* e = enemigos->obtener(i);
		if (e != nullptr && (std::rand() % 35 == 0)) {
			int cx = e->getX() + ANCHO_TANQUE / 2;
			int cy = e->getY() + ALTO_TANQUE / 2;
			proyectiles.push_back(new Proyectil(cx, cy, e->getDireccion(), false));
		}
	}

	// 3. Mover proyectiles y verificar impactos
	bool cambioEstado = false;
	for (Proyectil* p : proyectiles) {
		if (p == nullptr || !p->estaActivo()) continue;
		p->mover(mapa);
		if (!p->estaActivo()) continue;

		if (p->getEsDelJugador()) {
			// Bala del jugador vs enemigos
			for (int i = 0; i < enemigos->cantidad(); i++) {
				CEnemigo* e = enemigos->obtener(i);
				if (e != nullptr && colisionaRect(p->getX(), p->getY(), p->getAncho(), p->getAlto(),
					e->getX(), e->getY(), ANCHO_TANQUE, ALTO_TANQUE)) {
					p->desactivar();
					short vidasEnemigo = e->getVidas() - 1;
					e->setVidas(vidasEnemigo);
					if (vidasEnemigo <= 0) {
						enemigos->eliminar(i);
						jugador->setPuntuacion(jugador->getPuntuacion() + 100);
						cambioEstado = true;
						int nivelAntes = nivelActual;
						verificarAvanceNivel();
						if (juegoGanado || nivelActual != nivelAntes) {
							return;
						}
					}
					break;
				}
			}
		} else {
			// Bala enemiga vs jugador
			if (colisionaRect(p->getX(), p->getY(), p->getAncho(), p->getAlto(),
				jugador->getX(), jugador->getY(), ANCHO_TANQUE, ALTO_TANQUE)) {
				p->desactivar();
				short vidasRestantes = jugador->getVidas() - 1;
				jugador->setVidas(vidasRestantes);
				cambioEstado = true;
				if (vidasRestantes <= 0) {
					// Reiniciar al nivel 1 cuando el jugador pierde todas las vidas
					jugador->setVidas(3);
					jugador->setPuntuacion(0);
					jugador->setEstado(new EstadoNormal());
					iniciarNivel(1, 4);
					return;
				}
			}
		}
	}

	// 4. Eliminar proyectiles inactivos
	for (size_t i = 0; i < proyectiles.size(); ) {
		if (proyectiles[i] == nullptr || !proyectiles[i]->estaActivo()) {
			delete proyectiles[i];
			proyectiles.erase(proyectiles.begin() + i);
		} else {
			i++;
		}
	}

	if (cambioEstado) {
		std::string nomEstado = jugador->getEstado() ? jugador->getEstado()->getNombre() : "Normal";
		notificar(jugador->getVidas(), jugador->getPuntuacion(), nivelActual, nomEstado);
	}
}

void CJuegoFacade::dibujarEscena(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques,
	Bitmap^ bmpTrofeo, Bitmap^ bmpTanques) {
	actualizar();
	mapa->DibujarMapa(g, bmpPiso, bmpBloques, bmpTrofeo);
	jugador->dibujar(g, bmpTanques);
	enemigos->dibujar(g, bmpTanques);
	for (Proyectil* p : proyectiles) {
		if (p != nullptr && p->estaActivo()) {
			p->dibujar(g);
		}
	}

	if (juegoGanado) {
		int anchoMapa = MAX_COLUMNAS * ANCHO_IMAGEN;
		int altoMapa = MAX_FILAS * ALTO_IMAGEN;
		SolidBrush^ fondo = gcnew SolidBrush(Color::FromArgb(190, 0, 0, 0));
		g->FillRectangle(fondo, 0, altoMapa / 2 - 90, anchoMapa, 180);

		Font^ fuenteTitulo = gcnew Font("Arial", 42, FontStyle::Bold);
		Font^ fuenteSub = gcnew Font("Arial", 16, FontStyle::Bold);
		StringFormat^ formato = gcnew StringFormat();
		formato->Alignment = StringAlignment::Center;
		formato->LineAlignment = StringAlignment::Center;

		g->DrawString("GANASTE!", fuenteTitulo, Brushes::Gold,
			RectangleF(0, (float)(altoMapa / 2 - 75), (float)anchoMapa, 70), formato);

		System::String^ sub = System::String::Format("Puntuacion final: {0}  |  Presiona 1-5 para jugar de nuevo",
			jugador != nullptr ? jugador->getPuntuacion() : 0);
		g->DrawString(sub, fuenteSub, Brushes::White,
			RectangleF(0, (float)(altoMapa / 2 + 15), (float)anchoMapa, 45), formato);

		delete fondo;
		delete fuenteTitulo;
		delete fuenteSub;
		delete formato;
	}
}
