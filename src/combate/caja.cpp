#include "caja.h"
#include "freeglut.h"
#include <string>

void caja::dibuja()
{
	suelo.dibuja();
	techo.dibuja();
	izquierda.dibuja();
	derecha.dibuja();

	dibujaHUD();
}

void caja::fDatos(const pieza& p1, const pieza& p2)
{

	vida1 = p1.getVida();
	vidamax1 = p1.getVidamax();
	vida2 = p2.getVida();
	vidamax2 = p2.getVidamax();

}

void caja::dibujaHUD()
{

}