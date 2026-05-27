#include "cursor.h"
#include "freeglut.h"

// Se inicializa el cursor en el centro del tablero (4,4)
Cursor::Cursor() : posicion(4, 4)
{}

// Mueve el cursor una casilla en la direccion indicada por la tecla WASD
// Se comprueban los limites para no salir del tablero
void Cursor::mover(unsigned char key)
{
	if (key == 'w' || key == 'W')  if (posicion.fila < FILAS - 1) posicion.fila++;
	if (key == 's' || key == 'S')  if (posicion.fila > 0)  posicion.fila--;
	if (key == 'a' || key == 'A')  if (posicion.col > 0)  posicion.col--;
	if (key == 'd' || key == 'D')  if (posicion.col < COLS - 1)  posicion.col++;
}

// Dibuja un borde amarillo 
void Cursor::dibuja() const
{
	if (!posicion.esValida()) return;

	float x = posicion.col * TAM_CELDA - (COLS * TAM_CELDA) / 2.0f;
	float y = posicion.fila * TAM_CELDA - (FILAS * TAM_CELDA) / 2.0f;

	glColor3ub(255, 220, 0);
	glLineWidth(3.5f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(x, y, 0);
	glVertex3f(x + TAM_CELDA, y, 0);
	glVertex3f(x + TAM_CELDA, y + TAM_CELDA, 0);
	glVertex3f(x, y + TAM_CELDA, 0);
	glEnd();
	glLineWidth(1.0f);
}
