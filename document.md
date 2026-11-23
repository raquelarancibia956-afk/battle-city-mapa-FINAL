# Documentación de Cambios - Battle City

Resumen sencillo de las funcionalidades, correcciones y patrones de diseño implementados en el proyecto.

---

## 1. Movimiento del Jugador y Colisiones
- **Archivos:** `Jugador.h`, `Jugador.cpp`, `Tanque.h`, `Tanque.cpp`, `Mapa.h`, `Mapa.cpp`, `Juego.h`
- Se implementó `CJugador::mover(...)` con:
  - Validación de límites del mapa (`13 x 13` bloques de `64 x 64` px) y bloques sólidos (`destruible`, `noDestruible`, `agua`, `trofeo`).
  - Solo `piso` y `arbol` son transitables.
  - Alineación suave a la cuadrícula (*corner snapping*) al doblar en pasillos estrechos.
  - Avance píxel a píxel para detenerse pegado a los obstáculos sin atravesarlos.
- Se conectó el control por teclado en `Juego.h` con las **flechas direccionales** y **W, A, S, D** (`KeyPreview = true`).

---

## 2. Corrección de la Orientación del Sprite
- **Archivo:** `Tanque.cpp`
- En `imagenes\tanques.png`, las filas de dirección corresponden a:
  - `0`: Arriba
  - `1`: Derecha
  - `2`: Abajo
  - `3`: Izquierda
- Se corrigió `CTanque::dibujarSprite` intercambiando `derecha` (`1`) e `izquierda` (`3`), evitando que los tanques caminaran hacia atrás al moverse horizontalmente.

---

## 3. Movimiento Autónomo de Enemigos
- **Archivos:** `Enemigo.h`, `Enemigo.cpp`, `CColeccionEnemigo.h`, `CColeccionEnemigo.cpp`, `CJuegoFacade.cpp`
- Los enemigos se mueven automáticamente en cada ciclo del temporizador (`timer1_Tick` -> `CJuegoFacade::actualizar()`).
- Calculan su ruta hacia el jugador rodeando obstáculos y evitando superponerse entre sí (`puedeMoverEnemigo`).

---

## 4. Patrones de Diseño Implementados
Además de **Facade** (`CJuegoFacade`) y **Factory Method** (`CFabricaEnemigo`, `FEnemigoM`), se agregaron 4 patrones:

1. **Strategy** (`IEstrategiaMovimiento.h`, `EstrategiaPerseguir.h/.cpp`, `EstrategiaAleatoria.h/.cpp`):
   - Permite alternar el comportamiento de movimiento de cada enemigo entre perseguir al jugador o patrullar aleatoriamente.
2. **Singleton** (`Mapa.h`, `Mapa.cpp`):
   - `CMapa::getInstancia()` asegura una única instancia global del mapa en todo el juego.
3. **Observer** (`IObservadorJuego.h`, `CSujetoJuego.h`, `CMarcadorObserver.h/.cpp`):
   - `CJuegoFacade` notifica cambios de nivel, vidas, puntuación y estado a `CMarcadorObserver`, actualizando la barra de título de la ventana.
4. **State** (`IEstadoTanque.h`, `EstadosTanque.h/.cpp`, `Tanque.h/.cpp`):
   - Modela estados del tanque (`EstadoNormal`, `EstadoRapido`, `EstadoBlindado`) que modifican sus atributos dinámicamente.

---

## 5. Sistema de Disparos
- **Archivos:** `Proyectil.h`, `Proyectil.cpp`, `Bloque.h`, `Bloque.cpp`, `CJuegoFacade.h`, `CJuegoFacade.cpp`, `Juego.h`
- El jugador dispara con la tecla **Espacio** (máximo 2 balas activas simultáneamente) y los enemigos disparan de forma autónoma.
- Las balas destruyen bloques `destruible` (reduciendo su durabilidad hasta convertirlos en `piso`), se detienen en bloques `noDestruible`/`trofeo` y eliminan enemigos sumando `+100` puntos al jugador.

---

## 6. Controles del Juego
- **Moverse:** Flechas direccionales o `W`, `A`, `S`, `D`
- **Disparar:** `Espacio`
- **Cambiar estado del tanque (Patrón State):** `E`
- **Cambiar de nivel:** Teclas `1` al `5`

---

## 7. Control de Versiones
- Se inicializó el repositorio Git en la rama `main` con `.gitignore` configurado para excluir archivos temporales y salidas de compilación de Visual Studio.
