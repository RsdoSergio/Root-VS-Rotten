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


	double prop1 = (vidaMaxPieza1 > 0.0) ? (vidaPieza1 / vidaMaxPieza1) : 0.0;
	double prop2 = (vidaMaxPieza2 > 0.0) ? (vidaPieza2 / vidaMaxPieza2) : 0.0;

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

	if (pieza1) pieza1->setVelocidad(pieza1->getVelocidad() / 1.3f);
	if (pieza2) pieza2->setVelocidad(pieza2->getVelocidad() / 1.3f);
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

void arena::fDatos(Pieza& p1, Pieza& p2, BandoVentaja ventaja)
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

	nombrePieza1 = pieza1->getNombre();
	nombrePieza2 = pieza2->getNombre();
	vidaPieza1 = pieza1->getVida();
	vidaPieza2 = pieza2->getVida();
	vidaMaxPieza1 = pieza1->getVidaMax();
	vidaMaxPieza2 = pieza2->getVidaMax();

	float velPlanta = 4.0f;
	float velZombi = 4.0f;
	float bonus = 1.3f;

	if (ventaja == BandoVentaja::PLANTA) {
		pieza1->setVidaMax(pieza1->getVidaMax() * bonus); // ← primero aumentar el máximo
		pieza1->curar(pieza1->getVidaMax()); // ← luego curar al nuevo máximo
		vidaMaxPieza1 = pieza1->getVidaMax();
		vidaPieza1 = pieza1->getVida();

		pieza1->setVelocidad(pieza1->getVelocidad() * bonus);
	}
	else if (ventaja == BandoVentaja::ZOMBI) {
		pieza2->setVidaMax(pieza2->getVidaMax() * bonus);
		pieza2->curar(pieza2->getVidaMax());
		vidaMaxPieza2 = pieza2->getVidaMax();
		vidaPieza2 = pieza2->getVida();

		pieza2->setVelocidad(pieza2->getVelocidad() * bonus);
	}

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
		p->actualizarEfectos(dt);
		if (p->estaAtacando() && p->bloqueaMovimientoAlAtacar())
		{
			p->setAccion(AccionPieza::ATACAR);
			return;
		}
		if (p->estaAtacando()) p->setAccion(AccionPieza::ATACAR);//poner esto para qse ponga el frame de atacar si no se bloquea al hacerlo
		p->actualizarArena(dt);
		};

	mover(pieza1, proyectil1);
	if (pieza1)
		Interaccion::choque(*pieza1, caja);
	if (pieza1 && !dynamic_cast<PiezaVuelo*>(pieza1))
		for (int i = 0; i < MAX_OBSTACULOS; i++)
			Interaccion::choque(*pieza1, obstaculos[i]);
	
	mover(pieza2, proyectil2);
	if (pieza2)
		Interaccion::choque(*pieza2, caja);
	if (pieza2 && !dynamic_cast<PiezaVuelo*>(pieza2))
		for (int i = 0; i < MAX_OBSTACULOS; i++)
			Interaccion::choque(*pieza2, obstaculos[i]);

	if (pieza1 && pieza2) Interaccion::choque(*pieza1, *pieza2);

	aplicarDanoExplosiones();//para el fenix solo

	// Actualizar timers de cooldown
	tiempoDisparo1 += dt;
	tiempoDisparo2 += dt;

	auto recoger = [&](Pieza* p, std::vector<Proyectil*>& proyectiles)
		{
			if (p && p->tieneProyectilesPendientes())
			{
				auto nuevos = p->recogerProyectiles();
				proyectiles.insert(proyectiles.end(), nuevos.begin(), nuevos.end());
			}
		};
	recoger(pieza1, proyectil1);
	recoger(pieza2, proyectil2);

	// Mueve los proyectiles y comprueba colisión con la pieza contraria
	for (Proyectil* pr : proyectil1) {
		pr->mueve(dt);
		if (pieza2 && pieza2->estaViva())
			Interaccion::choque(*pr, *pieza2);
		if (!dynamic_cast<PiezaVuelo*>(pieza1))
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
		if (!dynamic_cast<PiezaVuelo*>(pieza2))
			for (int i = 0; i < MAX_OBSTACULOS; i++)
				Interaccion::choque(*pr, obstaculos[i]);

		//se desactiva el proyectil si sale de la arena
		double px = pr->getPosProyectil().getX();
		double py = pr->getPosProyectil().getY();
		if (px < caja.getXmin() || px > caja.getXMAX() ||
			py < caja.getYmin() || py > caja.getYMAX())
			pr->desactivar();
	}

	if (pieza1) vidaPieza1 = pieza1->getVida();
	if (pieza2) vidaPieza2 = pieza2->getVida();


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

	int dirX = p->getUltimoEjeX();
	int dirY = p->getUltimoEjeY();

	// Calcular dirección con último eje para ranged
	if (dirX != 0 && dirY != 0)
	{
		if (p->getUltimoEjeReciente() == 0) dirY = 0;
		else dirX = 0;
	}
	if (dirX == 0 && dirY == 0) dirX = dirDefecto;

	if (p->esMelee())
	{
		Audio::playSonido("audio/ATAQUE_A_MELEE.mp3");
		p->activarExplosion();

		if (p->tieneRafaga())
		{
			p->iniciarRafaga(dirX, dirY);
			// NO iniciarAtaque() — la ráfaga lo gestiona internamente
		}
		else
		{
			Vector2D pos(
				p->getPosArena().getX() + dirX * 3.5,
				p->getPosArena().getY() + dirY * 3.5
			);
			proyectiles.push_back(new Proyectil(pos, Vector2D(0.0, 0.0), p->getFuerza(), p->getTiempoAnimAtaque()));
			p->iniciarAtaque();
		}
	}
	else
	{
		Audio::playSonido("audio/ATAQUE_A_DISTANCIA.mp3");
		if (p->tieneRafaga())
			p->iniciarRafaga(dirX, dirY);
		else
		{
			Vector2D vel(dirX * p->getVelocidadProyectil(), dirY * p->getVelocidadProyectil());
			proyectiles.push_back(new Proyectil(p->getPosArena(), vel, p->getFuerza()));
		}
		p->iniciarAtaque();
	}

	tiempoDisparo = 0.0;
}


void arena::aplicarDanoExplosiones()
{
	auto aplicar = [&](Pieza* atacante, Pieza* defensor)
		{
			double dano = atacante->consumirDanoExplosion();
			if (dano <= 0.0 || !defensor || !defensor->estaViva()) return;
			double dx = defensor->getPosArena().getX() - atacante->getPosArena().getX();
			double dy = defensor->getPosArena().getY() - atacante->getPosArena().getY();
			if (std::sqrt(dx * dx + dy * dy) <= atacante->getRadioExplosionMax())
				defensor->recibirDanio(dano);
		};

	if (pieza1 && pieza2) aplicar(pieza1, pieza2);
	if (pieza1 && pieza2) aplicar(pieza2, pieza1);
}