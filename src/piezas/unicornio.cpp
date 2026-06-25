#include "unicornio.h"
#include "gestorTexturas.h"

std::string Unicornio::getRutaSprite() const
{
	return bando == Bando::planta
		? "imagenes/sprites_plantas/rabano_casillero.png"
		: "imagenes/sprites_zombies/zombie_momia.png";
}

void Unicornio::iniciarRafaga(int dx, int dy)
{
	proyectilesRestantes = proyectilesRafaga;
	timerEntreDisparos = 0.0;
	dirX = dx;
	dirY = dy;
	iniciarAtaque();
}

void Unicornio::actualizarEfectos(double dt)
{
	if (proyectilesRestantes <= 0) return;

	timerEntreDisparos += dt;
	if (timerEntreDisparos >= tiempoEntreDisparos)
	{
		timerEntreDisparos = 0.0;
		proyectilesRestantes--;

		Vector2D vel(dirX * velocidadProyectil, dirY * velocidadProyectil);
		proyectilesPendientes.push_back(new Proyectil(posArena, vel, fuerza, -1.0, getRutaProyectil()));

		if (proyectilesRestantes > 0)
			iniciarAtaque(); // mantener sprite de ataque entre disparos
	}
}

std::vector<Proyectil*> Unicornio::recogerProyectiles()
{
	std::vector<Proyectil*> tmp = proyectilesPendientes;
	proyectilesPendientes.clear();
	return tmp;
}