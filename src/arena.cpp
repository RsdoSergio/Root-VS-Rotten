#include "arena.h"
#include "freeglut.h"
#include "piezas/piezatierra.h"
#include"piezas/piezavuelo.h"
#include"piezas/piezateletransporte.h"
#include "interaccion.h"
#include"piezas/pieza.h"
#include "audio.h"

void arena::dibujaFondo() const
{
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(-30.0, -17.0);
	glVertex2f(30.0, -17.0);
	glVertex2f(30.0, 17.0);
	glVertex2f(-30.0, 17.0);
	glEnd();
}

void arena::dibujaInterior() const
{
	const char* fondos[9] = {			//array con las 9 rutas de los fondos
	   "imagenes/fondos/fondo_arena1.png",
	   "imagenes/fondos/fondo_arena2.png",
	   "imagenes/fondos/fondo_arena3.png",
	   "imagenes/fondos/fondo_arena4.png",
	   "imagenes/fondos/fondo_arena5.png",
	   "imagenes/fondos/fondo_arena6.png",
	   "imagenes/fondos/fondo_arena7.png",
	   "imagenes/fondos/fondo_arena8.png",
	   "imagenes/fondos/fondo_arena9.png"
	};

	const char* ruta = fondos[indiceFondo - 1]; //ojo q es un array (índice 0 = arena1)

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta).id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); glVertex2f(-SEMIANCHO, -SEMIALTO);
	glTexCoord2d(1, 1); glVertex2f(SEMIANCHO, -SEMIALTO);
	glTexCoord2d(1, 0); glVertex2f(SEMIANCHO, SEMIALTO);
	glTexCoord2d(0, 0); glVertex2f(-SEMIANCHO, SEMIALTO);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void arena::dibujaMarco() const
{
	glLineWidth(5);
	glColor3ub(255, 255, 255);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-SEMIANCHO, -SEMIALTO);
	glVertex2f(SEMIANCHO, -SEMIALTO);
	glVertex2f(SEMIANCHO, SEMIALTO);
	glVertex2f(-SEMIANCHO, SEMIALTO);
	glEnd();
}

void arena::dibujaHUD() const
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	// Dibuja el fondo del HUD
	glColor3ub(160, 100, 45);
	glBegin(GL_QUADS);
	glVertex2d(-SEMIANCHO, HUD_BASE);
	glVertex2d(SEMIANCHO, HUD_BASE);
	glVertex2d(SEMIANCHO, HUD_TECHO);
	glVertex2d(-SEMIANCHO, HUD_TECHO);
	glEnd();

	// Dibuja el marco del HUD
	glLineWidth(3);
	glColor3ub(255, 255, 255);
	glBegin(GL_LINE_LOOP);
	glVertex2d(-SEMIANCHO, HUD_BASE);
	glVertex2d(SEMIANCHO, HUD_BASE);
	glVertex2d(SEMIANCHO, HUD_TECHO);
	glVertex2d(-SEMIANCHO, HUD_TECHO);
	glEnd();
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2d(0.0, HUD_BASE);
	glVertex2d(0.0, HUD_TECHO);
	glEnd();

	double prop1 = (pieza1 && pieza1->getVidaMax() > 0.0) ? (pieza1->getVida() / pieza1->getVidaMax()) : 0.0;
	double prop2 = (pieza2 && pieza2->getVidaMax() > 0.0) ? (pieza2->getVida() / pieza2->getVidaMax()) : 0.0;

	const double margen = 0.3;
	const double barAncho = SEMIANCHO - margen * 2.0;
	const double barAlto = HUD_TECHO - HUD_BASE - margen * 2.0;
	const double barY = HUD_BASE + margen;

	// Dibuja las barras de vida
	glColor3ub(80, 80, 80);
	glBegin(GL_QUADS);
	glVertex2d(-SEMIANCHO + margen, barY);
	glVertex2d(-margen, barY);
	glVertex2d(-margen, barY + barAlto);
	glVertex2d(-SEMIANCHO + margen, barY + barAlto);
	glEnd();
	glColor3ub(80, 200, 80);

	glBegin(GL_QUADS);
	glVertex2d(-SEMIANCHO + margen, barY);
	glVertex2d(-SEMIANCHO + margen + barAncho * prop1, barY);
	glVertex2d(-SEMIANCHO + margen + barAncho * prop1, barY + barAlto);
	glVertex2d(-SEMIANCHO + margen, barY + barAlto);
	glEnd();

	glColor3ub(80, 80, 80);
	glBegin(GL_QUADS);
	glVertex2d(margen, barY);
	glVertex2d(SEMIANCHO - margen, barY);
	glVertex2d(SEMIANCHO - margen, barY + barAlto);
	glVertex2d(margen, barY + barAlto);
	glEnd();

	glColor3ub(180, 60, 200);
	glBegin(GL_QUADS);
	glVertex2d(margen, barY);
	glVertex2d(margen + barAncho * prop2, barY);
	glVertex2d(margen + barAncho * prop2, barY + barAlto);
	glVertex2d(margen, barY + barAlto);
	glEnd();
}

void arena::activa()
{
	activo = true;
	terminado = false;
	indiceFondo = 1 + rand() % 9;
	numObstaculos = 3 + rand() % 4;

	for (int i = 0; i < MAX_OBSTACULOS; i++)
		obstaculos[i].desactivar();

	for (int i = 0; i < numObstaculos; i++)
		colocarObstaculoAleatorio(i);
}

void arena::desactiva()
{	//reseteo de la pieza a x defecto
	if (pieza1)
	{
		pieza1->setAccion(AccionPieza::IDLE);
		pieza1->setDireccion(DirMovimiento::IDLE);
	}
	if (pieza2)
	{
		pieza2->setAccion(AccionPieza::IDLE);
		pieza2->setDireccion(DirMovimiento::IDLE);
	}

	//limpia los proyectiles que hayan quedado activos al terminar el combate
	for (Proyectil* pr : proyectil1)
		delete pr;
	for (Proyectil* pr : proyectil2)
		delete pr;
	proyectil1.clear();
	proyectil2.clear();

	activo = false;
	terminado = false;
	pieza1 = nullptr;
	pieza2 = nullptr;
}

void arena::dibujaObstaculos() const
{
	for (int i = 0; i < MAX_OBSTACULOS; i++)
		obstaculos[i].dibuja();
}

void arena::dibuja() const
{
	if (!activo) return;
	dibujaFondo();
	dibujaInterior();
	dibujaMarco();
	dibujaHUD();
	dibujaObstaculos();
	dibujaPiezasArena();
	dibujaProyectiles();
}

void arena::fDatos(Pieza& p1, Pieza& p2)
{
	if (p1.getBando() == Bando::planta) //esto hará que la pieza a la izquierda siempre sea planta
	{
		pieza1 = &p1;
		pieza2 = &p2;
	}
	else {
		pieza1 = &p2;
		pieza2 = &p1;
	}

	nombrePieza1 = p1.getNombre();
	nombrePieza2 = p2.getNombre();
	vidaPieza1 = p1.getVida();
	vidaPieza2 = p2.getVida();
	vidaMaxPieza1 = p1.getVidaMax();
	vidaMaxPieza2 = p2.getVidaMax();

	pieza1->setPosArena(-SEMIANCHO * 0.6, 0.0);
	pieza2->setPosArena(SEMIANCHO * 0.6, 0.0);
	pieza1->resetEjes();
	pieza2->resetEjes();
	activo = true;

	Audio::playMusicaCombate();
}

// Dibuja las dos piezas en sus lados respectivos de la arena
void arena::dibujaPiezasArena() const
{
	if (pieza1 == nullptr || pieza2 == nullptr) return;
	pieza1->dibujaArena(pieza1->getPosArena().getX(), pieza1->getPosArena().getY());
	pieza2->dibujaArena(pieza2->getPosArena().getX(), pieza2->getPosArena().getY());
}

//SE AÑADEN LOS PROYECTILES EN ARENA PARA PROBAR SU FUNCIONAMIENTO POSTERIORMENTE SE TIENE QUE CAMBIAR
// CADA PIEZA DEBERÁ GESTIONAR SU PROPIO PROYECTIL
//
//
// Mueve los proyectiles activos
// Sigue el mismo patron que Mundo::mueve en el juego de referencia

void arena::mueve(double dt)
{
	if (!activo) return;

	auto mover = [&](Pieza* p, const std::vector<Proyectil*>& proyectiles)
		{
			if (!p) return;
			if (terminado) return;
			p->actualizarAtaque(dt);
			if (p->estaAtacando())
			{
				p->setAccion(AccionPieza::ATACAR);
				return;
			}
			PiezaTierra* pt = dynamic_cast<PiezaTierra*>(p);
			if (pt) pt->actualizarArena(dt);
			PiezaVuelo* pv = dynamic_cast<PiezaVuelo*>(p);
			if (pv) pv->actualizarArena(dt);
			PiezaTeletransporte* pte = dynamic_cast<PiezaTeletransporte*>(p);
			if (pte) pte->actualizarArena(dt);
		};

	mover(pieza1, proyectil1);
	if (pieza1)
		Interaccion::choque(*pieza1, caja);
	if (pieza1)
		for (int i = 0; i < MAX_OBSTACULOS; i++)
			Interaccion::choque(*pieza1, obstaculos[i]);

	mover(pieza2, proyectil2);
	if (pieza2)
		Interaccion::choque(*pieza2, caja);
	if (pieza2)
		for (int i = 0; i < MAX_OBSTACULOS; i++)
			Interaccion::choque(*pieza2, obstaculos[i]);

	if (pieza1 && pieza2) Interaccion::choque(*pieza1, *pieza2);

	// Actualizar timers de cooldown
	tiempoDisparo1 += dt;
	tiempoDisparo2 += dt;

	// Mueve los proyectiles y comprueba colisión con la pieza contraria
	for (Proyectil* pr : proyectil1) {
		pr->mueve(dt);
		if (pieza2 && pieza2->estaViva())
			Interaccion::choque(*pr, *pieza2);
		for (int i = 0; i < MAX_OBSTACULOS; i++)
			Interaccion::choque(*pr, obstaculos[i]);

		//se desactiva el proyectil si sale de la arena
		double px = pr->getPosProyectil().getX();
		double py = pr->getPosProyectil().getY();
		if (px < caja.getXmin() || px > caja.getXMAX() ||
			py < caja.getYmin() || py > caja.getYMAX())
			pr->desactivar();
	}
	for (Proyectil* pr : proyectil2) {
		pr->mueve(dt);
		if (pieza1 && pieza1->estaViva())
			Interaccion::choque(*pr, *pieza1);
		for (int i = 0; i < MAX_OBSTACULOS; i++)
			Interaccion::choque(*pr, obstaculos[i]);

		//se desactiva el proyectil si sale de la arena
		double px = pr->getPosProyectil().getX();
		double py = pr->getPosProyectil().getY();
		if (px < caja.getXmin() || px > caja.getXMAX() ||
			py < caja.getYmin() || py > caja.getYMAX())
			pr->desactivar();
	}

	// Fin de combate
	if (pieza1 && !pieza1->estaViva()) { plantaGano = false;  terminado = true; } // murió pieza1, ganó pieza2
	if (pieza2 && !pieza2->estaViva()) { plantaGano = true; terminado = true; } // murió pieza2, ganó pieza1
}

void arena::tecla(unsigned char key)
{
	if (!activo) return;

	if (key == 'q' || key == 'Q') procesarAtaque(pieza1, proyectil1, tiempoDisparo1, +1);
	if (key == 'k' || key == 'K') procesarAtaque(pieza2, proyectil2, tiempoDisparo2, -1);
}

// Dibuja los proyectiles activos
void arena::dibujaProyectiles() const
{
	for (Proyectil* p : proyectil1) p->dibuja();
	for (Proyectil* p : proyectil2) p->dibuja();
}

void arena::colocarObstaculoAleatorio(int idx)
{
	constexpr double OBS_MIN = 2.0;
	constexpr double OBS_MAX = 6.0;
	constexpr double HOLGURA = 2.0;
	constexpr double MARGEN_PIEZA = TAM_PIEZA + 1.5;

	double x = 0.0, y = 0.0, lado = OBS_MIN;
	int intentos = 0;

	while (intentos < 200)
	{
		intentos++;

		lado = OBS_MIN + (double)rand() / RAND_MAX * (OBS_MAX - OBS_MIN);

		double xMin = caja.getXmin() + lado / 2.0 + HOLGURA;
		double xMax = caja.getXMAX() - lado / 2.0 - HOLGURA;
		double yMin = caja.getYmin() + lado / 2.0 + HOLGURA;
		double yMax = caja.getYMAX() - lado / 2.0 - HOLGURA;

		x = xMin + (double)rand() / RAND_MAX * (xMax - xMin);
		y = yMin + (double)rand() / RAND_MAX * (yMax - yMin);

		bool solapaPieza1 = pieza1 && (std::abs(x - pieza1->getPosArena().getX()) < (lado / 2.0 + MARGEN_PIEZA) && std::abs(y - pieza1->getPosArena().getY()) < (lado / 2.0 + MARGEN_PIEZA));

		bool solapaPieza2 = pieza2 && (std::abs(x - pieza2->getPosArena().getX()) < (lado / 2.0 + MARGEN_PIEZA) && std::abs(y - pieza2->getPosArena().getY()) < (lado / 2.0 + MARGEN_PIEZA));

		bool solapaObs = false;
		for (int j = 0; j < idx; j++)
		{
			double minDistX = (lado + obstaculos[j].getAncho()) / 2.0 + HOLGURA;
			double minDistY = (lado + obstaculos[j].getAlto()) / 2.0 + HOLGURA;
			if (std::abs(x - obstaculos[j].getPosX()) < minDistX && std::abs(y - obstaculos[j].getPosY()) < minDistY)
			{
				solapaObs = true;
				break;
			}
		}

		if (!solapaPieza1 && !solapaPieza2 && !solapaObs)
			break;
	}

	static const std::string spritesObstaculo[] = {
		"imagenes/obstaculos/obs1.png",
		"imagenes/obstaculos/obs2.png",
		"imagenes/obstaculos/obs3.png",
		"imagenes/obstaculos/obs4.png",
		"imagenes/obstaculos/obs5.png",
		"imagenes/obstaculos/obs6.png"
	};
	constexpr int NUM_SPRITES_OBS = 6;
	const std::string& sprite = spritesObstaculo[rand() % NUM_SPRITES_OBS];

	obstaculos[idx].colocar(x, y, lado, lado, sprite);
}

void arena::recibirMovimiento(int jugador, int dir, bool estado)
{
	if (!activo) return;
	Pieza* p = (jugador == 0) ? pieza1 : pieza2;
	if (!p) return;

	//solo PiezaTierra tiene setMovimiento por ahora
	PiezaTierra* pt = dynamic_cast<PiezaTierra*>(p);//transformar pieza de clase pieza a clase Piezatierra
	if (pt) pt->setMovimiento(dir, estado);

	PiezaVuelo* pv = dynamic_cast<PiezaVuelo*>(p);
	if (pv) pv->setMovimiento(dir, estado);

	PiezaTeletransporte* pte = dynamic_cast<PiezaTeletransporte*>(p);
	if (pte) pte->setMovimiento(dir, estado);
}

void arena::procesarAtaque(Pieza* p, std::vector<Proyectil*>& proyectiles, double& tiempoDisparo, int dirDefecto)
{
	if (!p || tiempoDisparo < p->getIntervaloAtaque()) return;

	if (p->esMelee())
	{
		int dirX = p->getUltimoEjeX();
		int dirY = p->getUltimoEjeY();
		if (dirX == 0 && dirY == 0) dirX = dirDefecto;

		Vector2D pos(
			p->getPosArena().getX() + dirX * 0.9,
			p->getPosArena().getY() + dirY * 0.9
		);
		Vector2D vel(0.0, 0.0);
		proyectiles.push_back(new Proyectil(pos, vel, p->getFuerza(), p->getTiempoAnimAtaque()));
	}
	else
	{
		int dirX = 0, dirY = 0;
		if (p->getUltimoEjeX() != 0 && p->getUltimoEjeY() != 0)
		{
			if (p->getUltimoEjeReciente() == 0) dirX = p->getUltimoEjeX();
			else dirY = p->getUltimoEjeY();
		}
		else
		{
			dirX = p->getUltimoEjeX();
			dirY = p->getUltimoEjeY();
		}
		if (dirX == 0 && dirY == 0) dirX = dirDefecto;
		Vector2D vel(dirX * p->getVelocidadProyectil(), dirY * p->getVelocidadProyectil());
		proyectiles.push_back(new Proyectil(p->getPosArena(), vel, p->getFuerza()));
	}
	p->iniciarAtaque();
	tiempoDisparo = 0.0;
}