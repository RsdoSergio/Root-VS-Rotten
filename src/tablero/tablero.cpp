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
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLS; j++) {
			// Color según tipo de casilla
			if ((i + j) % 2 == 0) { // casillas pares
				glColor3ub(100, 200, 100);  // verde claro
			}
			else { // casillas impares
				glColor3ub(50, 130, 50);    // verde oscuro
			}

			// Calcular posición en el mundo (centrado en origen)
			float x = j * TAM_CELDA - (COLS * TAM_CELDA) / 2.0f;
			float y = i * TAM_CELDA - (FILAS * TAM_CELDA) / 2.0f;

			// Dibujar la celda
			glBegin(GL_POLYGON);
			glVertex3f(x, y, 0);
			glVertex3f(x + TAM_CELDA, y, 0);
			glVertex3f(x + TAM_CELDA, y + TAM_CELDA, 0);
			glVertex3f(x, y + TAM_CELDA, 0);
			glEnd();
		}
	}
}