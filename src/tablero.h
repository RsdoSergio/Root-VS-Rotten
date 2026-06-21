#pragma once
#include "casilla.h"
#include"pos.h"
#include<vector>
#include "listapieza.h"
#include "hechizo.h"


class Cursor;

constexpr int FILAS = 9;
constexpr int COLS = 9;
constexpr float TAM_CELDA = 2.8f;

class Tablero {
public:

	void inicializaTablero();
	void colocarPiezasIniciales();

	//recibe un cursor para poder dibujar el cursor. las casillas se siguen dibujando de igual manera

	Pieza* getPieza(Pos p) const;
	bool   estaOcupada(Pos p) const;
	bool piezaBloqueada(Pos p);

	// Convierte una coordenada en espacio de mundo (las mismas unidades que usa
	// dibujaTablero) a la casilla (fila, col) correspondiente. Es la operacion
	// inversa de las cuentas de x,y que se hacen al dibujar. Devuelve Pos invalida
	// si el punto cae fuera del tablero.
	Pos screenToCell(float xMundo, float yMundo) const;

	bool gestionarEntrada(Pos cursor, int& turno);
	void cancelarSeleccion();
	void dibuja(const Cursor& cursor);

	// Getters para que Mundo pueda acceder a los combatientes
	Pieza* getPersonaje1() const { return personaje1; }
	Pieza* getPersonaje2() const { return personaje2; }

	bool estaAnimando() const { return animando; }
	bool actualizarAnimacion(double dt);  // llamada en mueve()
	bool combatePendiente = false;
	void resolverCombate(bool atacanteGana); 
	void avanzarCiclo(); // llamar cada 5 turnos
	BandoVentaja getBandoVentaja() const;
	std::vector<Pieza*>& getEliminadasPlanta() { return eliminadasPlanta; }
	std::vector<Pieza*>& getEliminadasZombi() { return eliminadasZombi; }

	bool modoHechizoActivo() const { return hechizoActivo != nullptr; } 
	void activarHechizo(Pieza* mago, HechizoBase* hechizo);
	bool aplicarHechizo(Pos destino);
	void cancelarHechizo() { hechizoActivo = nullptr; magoLanzando = nullptr; }
	void colocarPiezaEnCasilla(Pos p, Pieza* pieza) { casillas[p.fila][p.col].pieza = pieza; }


private:

	void dibujaTablero(const Cursor& cursor);
	void dibujaPiezas();
	void marcaCasillasValidas();

	Casilla casillas[FILAS][COLS];
	Pos piezaSeleccionada;
	std::vector<Pos> casillasValidas;
	bool movimientoPendiente = false;

	// Piezas involucradas en el ultimo combate detectado
	Pieza* personaje1 = nullptr;
	Pieza* personaje2 = nullptr;

	Pos posOrigen;
	Pos posDestino;

	std::vector<Pos> movimientosValidos(Pos origen);
	bool moverPieza(Pos origen, Pos destino);

	bool animando = false; // si hay alguna pieza moviéndose
	Pieza* piezaAnimando = nullptr; // pieza q se está moviendo
	float animX = 0.0f;
	float animY = 0.0f;
	float destX = 0.0f;
	float destY = 0.0f;

	int ciclo = 0;        // contador de turnos
	int indiceCiclo = 0;
	int patronOriginal[FILAS][COLS]; // guardamos el patrón inicial
	std::vector<Pieza*> eliminadasPlanta;
	std::vector<Pieza*> eliminadasZombi;

	HechizoBase* hechizoActivo = nullptr;
	Pieza* magoLanzando = nullptr;
};