#include "casilla.h"

void Casilla::inicializa(int f, int c, TipoCasilla t, unsigned char cr, unsigned char cg, unsigned char cb) {
	fila = f;
	col = c;
	ocupada = false;
	tipo = t;
	r = cr;
	g = cg;
	b = cb;
	pieza = nullptr;
}