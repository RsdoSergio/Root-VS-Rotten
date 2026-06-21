#include "pieza.h"
#include"gestorTexturas.h"

Pieza::Pieza(double v, double f, double vel, double intervalo, int radio, Bando b, Pos pos)
	: vida(v), vidaMax(v),
	fuerza(f),
	velocidad(vel),
	intervaloAtaque(intervalo),
	radioMovimiento(radio), // ? nuevo
	bando(b),
	casilla(pos)
{
	posArena.setValores(0.0, 0.0);
}

void Pieza::recibirDanio(double d) {
	vida -= d;
	if (vida < 0.0) vida = 0.0;
}

void Pieza::curar(double cantidad) {
	vida += cantidad;
	if (vida > vidaMax) vida = vidaMax;
}

void Pieza::setDireccion(DirMovimiento d) {
	dirActual = d;
	if (d != DirMovimiento::IDLE)
		ultimaDir = d;
}

void Pieza::resetEjes() {
	ultimo_eje_x = 0;
	ultimo_eje_y = 0;
	ultimo_eje_reciente = 0;
}

int Pieza::getFrame(DirMovimiento dir, AccionPieza accion) const
{
	if (accion == AccionPieza::ATACAR) return 5;
	switch (dir) {
	case DirMovimiento::ESTE:  return 1;
	case DirMovimiento::OESTE: return 2;
	case DirMovimiento::NORTE: return 3;
	case DirMovimiento::SUR:   return 4;
	default:                   return 0;
	}
}

void Pieza::dibujaTablero(float x, float y) const
{
	int frame = getFrame(getDireccion(), getAccion());
	dibujarSprite(getRutaSprite(), x, y, 1.1f, frame, 6);
}

void Pieza::dibujaArena(float x, float y) const
{
	int frame = getFrame(getDireccion(), getAccion());
	dibujarSprite(getRutaSprite(), x, y, 2.0f, frame, 6);
}

void Pieza::actualizarAtaque(double dt)
{
	if (!atacandoActivo) return;
	tiempoAtaqueRestante -= dt;
	if (tiempoAtaqueRestante <= 0.0)
	{
		tiempoAtaqueRestante = 0.0;
		atacandoActivo = false;
	}
}

void Pieza::dibujaTableroGrande(float x, float y, float tam) const
{
	int frame = getFrame(getDireccion(), getAccion());
	dibujarSprite(getRutaSprite(), x, y, tam, frame, 6);
}