#include "cursor.h"
#include "freeglut.h"

Cursor::Cursor(int fila, int col, unsigned char r, unsigned char g, unsigned char b)
	: posicion(fila, col), cr(r), cg(g), cb(b)

{}

void Cursor::mover(unsigned char key)
{
	if (key == 'w' || key == 'W')  if (posicion.fila < FILAS - 1) posicion.fila++;
	if (key == 's' || key == 'S')  if (posicion.fila > 0)  posicion.fila--;
	if (key == 'a' || key == 'A')  if (posicion.col > 0)  posicion.col--;
	if (key == 'd' || key == 'D')  if (posicion.col < COLS - 1)  posicion.col++;
}

void Cursor::dibuja() const
{
	if (!posicion.esValida()) return;

	float x = posicion.col * TAM_CELDA - (COLS * TAM_CELDA) / 2.0f;
	float y = posicion.fila * TAM_CELDA - (FILAS * TAM_CELDA) / 2.0f;

	if (bloqueado)
		glColor3ub(255, 0, 0);
	else
		glColor3ub(cr, cg, cb);

	glLineWidth(3.5f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(x, y, 0);
	glVertex3f(x + TAM_CELDA, y, 0);
	glVertex3f(x + TAM_CELDA, y + TAM_CELDA, 0);
	glVertex3f(x, y + TAM_CELDA, 0);
	glEnd();
	glLineWidth(1.0f);
}

void Cursor::setPosicion(Pos p)
{
	if (p.fila < 0 || p.fila >= FILAS || p.col < 0 || p.col >= COLS) return;
	posicion = p;
}

void Cursor::moverFlechas(int key)
{
	if (key == GLUT_KEY_UP)    if (posicion.fila < FILAS - 1) posicion.fila++;
	if (key == GLUT_KEY_DOWN)  if (posicion.fila > 0) posicion.fila--;
	if (key == GLUT_KEY_LEFT)  if (posicion.col > 0)  posicion.col--;
	if (key == GLUT_KEY_RIGHT) if (posicion.col < COLS - 1)  posicion.col++;
}