#include "tablero.h"
#include "freeglut.h"

void Tablero::inicializaTablero() {
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLS; j++) {
			casillas[i][j].ocupada = false;

			casillas[i][j].tipo = Casilla::NORMAL;
		}
	}
}

void Tablero::dibujaTablero() {
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
	unsigned char colores[3][3] = {
		{220, 255, 220},  // 0: verde muy claro
		{34,  100,  34},  // 1: verde oscuro
		{ 85, 140,  40},  // 2: verde medio
	};

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLS; j++) {
			int tipo = patron[i][j];
			glColor3ub(colores[tipo][0], colores[tipo][1], colores[tipo][2]);

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