#include "interaccion.h"

void Interaccion::choque(Pieza& p, const Caja& c)
{
	constexpr double radio = TAM_PIEZA / 1.2;

	double x = p.posArena.getX();
	double y = p.posArena.getY();

	if (x - radio < c.izq.limite1_.getX())   x = c.izq.limite1_.getX() + radio;
	if (x + radio > c.dcha.limite1_.getX())   x = c.dcha.limite1_.getX() - radio;
	if (y - radio < c.suelo.limite1_.getY())  y = c.suelo.limite1_.getY() + radio;
	if (y + radio > c.techo.limite1_.getY())  y = c.techo.limite1_.getY() - radio;

	p.posArena.setValores(x, y);
}

void Interaccion::choque(Proyectil& pr, Pieza& p)
{
	if (!pr.getEstado()) return; // ya desactivado, ignorar

	constexpr double radioPieza = TAM_PIEZA / 1.1;
	constexpr double radioProyectil = 0.1;
	double dx = pr.getPosProyectil().getX() - p.posArena.getX();
	double dy = pr.getPosProyectil().getY() - p.posArena.getY();
	double distancia = std::sqrt(dx * dx + dy * dy);
	if (distancia < (radioPieza + radioProyectil))
	{
		p.recibirDanio(pr.getDamageProyectil());
		pr.desactivar();
	}
}

void Interaccion::choque(Pieza& p, const Obstaculo& o)
{
	if (!o.estaActivo()) return;

	constexpr double radio = TAM_PIEZA / 1.2;

	double x = p.posArena.getX();
	double y = p.posArena.getY();

	if (x + radio > o.getXmin() && x - radio < o.getXmax() &&
		y + radio > o.getYmin() && y - radio < o.getYmax())
	{
		double solapIzq = (x + radio) - o.getXmin();
		double solapDcha = o.getXmax() - (x - radio);
		double solapAbaj = (y + radio) - o.getYmin();
		double solapArri = o.getYmax() - (y - radio);

		double minSolap = std::min({ solapIzq, solapDcha, solapAbaj, solapArri });

		if (minSolap == solapIzq)
			x -= solapIzq;
		else if (minSolap == solapDcha)
			x += solapDcha;
		else if (minSolap == solapAbaj)
			y -= solapAbaj;
		else
			y += solapArri;

		p.posArena.setValores(x, y);
	}
}

void Interaccion::choque(Pieza& p1, Pieza& p2)
{
	constexpr double radio = TAM_PIEZA / 1.0;

	double dx = p2.posArena.getX() - p1.posArena.getX();
	double dy = p2.posArena.getY() - p1.posArena.getY();
	double dist = std::sqrt(dx * dx + dy * dy);

	double minDist = radio + radio;

	if (dist < minDist && dist > 0.0)
	{
		double solape = minDist - dist;
		double nx = dx / dist;
		double ny = dy / dist;

		p1.posArena.setValores(p1.posArena.getX() - nx * solape / 2.0, p1.posArena.getY() - ny * solape / 2.0);
		p2.posArena.setValores(p2.posArena.getX() + nx * solape / 2.0, p2.posArena.getY() + ny * solape / 2.0);
	}
}