#include "tablero.h"
#include "freeglut.h"

#include "pieza.h"
#include"peon.h"
#include "golem.h"
#include "arquero.h"
#include "valquiria.h"
#include "genio.h"
#include "unicornio.h"
#include "fenix.h"
#include "mago.h"

void Tablero::inicializaTablero() {
	// Patron del tablero Archon 9x9
	// 0 = verde muy claro
	// 1 = verde oscuro
	// 2 = verde medio (fondo)

	int patron[FILAS][COLS] = { // Inicialización completa de la matriz del tablero
		{1, 0, 1, 2, 2, 2, 0, 1, 0},
		{0, 1, 2, 0, 2, 1, 2, 0, 1},
		{1, 2, 0, 1, 2, 0, 1, 2, 0},
		{2, 0, 1, 0, 2, 1, 0, 1, 2},
		{0, 2, 2, 2, 2, 2, 2, 2, 1},
		{2, 0, 1, 0, 2, 1, 0, 1, 2},
		{1, 2, 0, 1, 2, 0, 1, 2, 0},
		{0, 1, 2, 0, 2, 1, 2, 0, 1},
		{1, 0, 1, 2, 2, 2, 0, 1, 0}
	};

	// Definicion de colores RGB para cada tipo
	using byte = unsigned char;
	byte colores[3][3] = {
		{220, 255, 220},  // 0: verde muy claro
		{34,  100,  34},  // 1: verde oscuro
		{85, 140,  40},  // 2: verde medio  
	};

	for (int i = 0; i < FILAS; i++) { // Inicialización del tipo de casilla y su color
		for (int j = 0; j < COLS; j++) {
			Casilla::TipoCasilla tipo;

			if (((i + 1 == 1 || i + 1 == 9) && j + 1 == 5) || ((i + 1 == 1 || i + 1 == 5 || i + 1 == 9) && i + 1 == 5))
				tipo = Casilla::PODER;
			else
				tipo = Casilla::NORMAL;

			// Guardar color según patrón (dentro de casilla)
			int p = patron[i][j];
			casillas[i][j].inicializa(i, j, tipo, colores[p][0], colores[p][1], colores[p][2]);
		}
	}
}




void Tablero::dibujaTablero() {
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLS; j++) {
			glColor3ub(casillas[i][j].r, casillas[i][j].g, casillas[i][j].b);

			float x = j * TAM_CELDA - (COLS * TAM_CELDA) / 2.0f;
			float y = i * TAM_CELDA - (FILAS * TAM_CELDA) / 2.0f;

			glBegin(GL_POLYGON);
			glVertex3f(x, y, 0);
			glVertex3f(x + TAM_CELDA, y, 0);
			glVertex3f(x + TAM_CELDA, y + TAM_CELDA, 0);
			glVertex3f(x, y + TAM_CELDA, 0);
			glEnd();
		}
	}
}

void Tablero::colocarPiezasIniciales() {

	// --- BANDO LUZ (columna 0 - fila trasera, de esquina a centro) ---
	casillas[0][0].pieza = new Valquiria(Bando::planta, Pos(0, 0)); // A1 esquina
	casillas[1][0].pieza = new Golem(Bando::planta, Pos(1, 0)); // A2
	casillas[2][0].pieza = new Unicornio(Bando::planta, Pos(2, 0)); // A3
	casillas[3][0].pieza = new Djinn(Bando::planta, Pos(3, 0)); // A4
	casillas[4][0].pieza = new Mago(Bando::planta, Pos(4, 0)); // A5 centro - lider
	casillas[5][0].pieza = new Fenix(Bando::planta, Pos(5, 0)); // A6
	casillas[6][0].pieza = new Unicornio(Bando::planta, Pos(6, 0)); // A7
	casillas[7][0].pieza = new Golem(Bando::planta, Pos(7, 0)); // A8
	casillas[8][0].pieza = new Valquiria(Bando::planta, Pos(8, 0)); // A9 esquina

	// --- BANDO LUZ (columna 1 - fila delantera) ---
	casillas[0][1].pieza = new Arquero(Bando::planta, Pos(0, 1)); // B1 esquina
	for (int i = 1; i <= 7; i++)
		casillas[i][1].pieza = new Peon(Bando::planta, Pos(i, 1)); // B2-B8 peones
	casillas[8][1].pieza = new Arquero(Bando::planta, Pos(8, 1)); // B9 esquina

	// --- BANDO OSCURIDAD (columna 8 - fila trasera, simétrico) ---
	casillas[0][8].pieza = new Valquiria(Bando::zombi, Pos(0, 8));
	casillas[1][8].pieza = new Golem(Bando::zombi, Pos(1, 8));
	casillas[2][8].pieza = new Unicornio(Bando::zombi, Pos(2, 8));
	casillas[3][8].pieza = new Djinn(Bando::zombi, Pos(3, 8));
	casillas[4][8].pieza = new Mago(Bando::zombi, Pos(4, 8));
	casillas[5][8].pieza = new Fenix(Bando::zombi, Pos(5, 8));
	casillas[6][8].pieza = new Unicornio(Bando::zombi, Pos(6, 8));
	casillas[7][8].pieza = new Golem(Bando::zombi, Pos(7, 8));
	casillas[8][8].pieza = new Valquiria(Bando::zombi, Pos(8, 8));

	// --- BANDO OSCURIDAD (columna 7 - fila delantera, simétrico) ---
	casillas[0][7].pieza = new Arquero(Bando::zombi, Pos(0, 7));
	for (int i = 1; i <= 7; i++)
		casillas[i][7].pieza = new Peon(Bando::zombi, Pos(i, 7));
	casillas[8][7].pieza = new Arquero(Bando::zombi, Pos(8, 7));
}

void Tablero::dibujaPiezas()
{
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLS; j++) {
			Pieza* p = casillas[i][j].pieza;
			if (p != nullptr) {
				// Centro de la casilla en coordenadas OpenGL
				float x = j * TAM_CELDA - (COLS * TAM_CELDA) / 2.0f + TAM_CELDA / 2.0f;
				float y = i * TAM_CELDA - (FILAS * TAM_CELDA) / 2.0f + TAM_CELDA / 2.0f;
				p->dibujaTablero(x, y); // Polimorfismo: cada pieza sabe cómo dibujarse
			}
		}
	}
	
}
