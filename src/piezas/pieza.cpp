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
	if (accion == AccionPieza::ATACAR)
	{
		if (!rutaSpriteAtaque.empty()) //direccion
		{
			switch (dir) {
			case DirMovimiento::ESTE:  return 0;
			case DirMovimiento::OESTE: return 1;
			case DirMovimiento::NORTE: return 2;
			case DirMovimiento::SUR:   return 3;
			default:                   return 0;
			}
		}
		return 5; // frame genérico de ataque
	}
	switch (dir) {
	case DirMovimiento::ESTE:  return 1;
	case DirMovimiento::OESTE: return 2;
	case DirMovimiento::NORTE: return 3;
	case DirMovimiento::SUR:   return 4;
	default:                   return 0;
	}
}

void Pieza::dibujaArena(float x, float y) const
{
	bool atacando = (getAccion() == AccionPieza::ATACAR);
	bool tieneAtaque = !rutaSpriteAtaque.empty();
	std::string ruta = (atacando && tieneAtaque) ? rutaSpriteAtaque : rutaSprite;
	int numFrames = (atacando && tieneAtaque) ? numFramesAtaque : numFramesNormal;
	int frame = getFrame(getDireccion(), getAccion());
	dibujarSprite(ruta, x, y, tamArena, frame, numFrames);
}

void Pieza::dibujaTablero(float x, float y) const
{
	int frame = getFrame(getDireccion(), getAccion());
	dibujarSprite(rutaSprite, x, y, 1.1f, frame, numFramesNormal);
}
void Pieza::actualizarAtaque(double dt)
{
	if (!atacandoActivo) return;
	tiempoAtaqueRestante -= dt;
	if (tiempoAtaqueRestante <= 0.0)
	{
		tiempoAtaqueRestante = 0.0;
		atacandoActivo = false;
		accionActual = AccionPieza::IDLE; 
	}
}

void Pieza::dibujaTableroGrande(float x, float y, float tam) const
{
	int frame = getFrame(getDireccion(), getAccion());
	dibujarSprite(getRutaSprite(), x, y, tam, frame, 6);
}