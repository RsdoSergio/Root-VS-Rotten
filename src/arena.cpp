#include "arena.h"
#include "freeglut.h"
#include "piezatierra.h"
#include"piezavuelo.h"


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
	   "imagenes/fondo_arena1.png",
	   "imagenes/fondo_arena2.png",
	   "imagenes/fondo_arena3.png",
	   "imagenes/fondo_arena4.png",
	   "imagenes/fondo_arena5.png",
	   "imagenes/fondo_arena6.png",
	   "imagenes/fondo_arena7.png",
	   "imagenes/fondo_arena8.png",
	   "imagenes/fondo_arena9.png"
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

void arena::dibuja() const
{
	if (!activo) return;
	dibujaFondo();
	dibujaInterior();
	dibujaMarco();
	dibujaHUD();
	dibujaPiezasArena();
	dibujaProyectiles();
}

void arena::fDatos( Pieza& p1,  Pieza& p2)
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
	activo = true;
}

// Dibuja las dos piezas en sus lados respectivos de la arena
void arena::dibujaPiezasArena() const
{
	if (pieza1 == nullptr || pieza2 == nullptr) return;
	pieza1->dibujaTablero(pieza1->getPosArena().getX(), pieza1->getPosArena().getY());
	pieza2->dibujaTablero(pieza2->getPosArena().getX(), pieza2->getPosArena().getY());
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

	auto mover = [&](Pieza* p) 
		{
		if (!p) return;
		PiezaTierra* pt = dynamic_cast<PiezaTierra*>(p);
		if (pt) pt->actualizarArena(dt, caja.getXmin(), caja.getXMAX(), caja.getYmin(), caja.getYMAX());
		PiezaVuelo* pv = dynamic_cast<PiezaVuelo*>(p);
		if (pv) pv->actualizarArena(dt, caja.getXmin(), caja.getXMAX(), caja.getYmin(), caja.getYMAX());
		};

	mover(pieza1);
	mover(pieza2);

	// Actualizar timers de cooldown
	tiempoDisparo1 += dt;
	tiempoDisparo2 += dt;

	// Mover todos los proyectiles activos
	for (Proyectil* p : proyectil1) p->mueve(dt);
	for (Proyectil* p : proyectil2) p->mueve(dt);



}

void arena::tecla(unsigned char key)
{
	if (!activo) return;

	if ((key == 'q' || key == 'Q') && tiempoDisparo1 >= pieza1->getIntervaloAtaque())
	{
		Vector2D pos = pieza1->getPosArena();
		Vector2D vel(VEL_PROYECTIL, 0.0);
		proyectil1.push_back(new Proyectil(pos, vel, 5.0));
		tiempoDisparo1 = 0.0;
	}
	if ((key == 'k' || key == 'K') && tiempoDisparo2 >= pieza2->getIntervaloAtaque())
	{
		Vector2D pos = pieza2->getPosArena();
		Vector2D vel(-VEL_PROYECTIL, 0.0);
		proyectil2.push_back(new Proyectil(pos, vel, 5.0));
		tiempoDisparo2 = 0.0;
	}
}

// Dibuja los proyectiles activos
void arena::dibujaProyectiles() const
{
	for (Proyectil* p : proyectil1) p->dibuja();
	for (Proyectil* p : proyectil2) p->dibuja();
}

void arena::MoverPiezaPlanta(unsigned char key)
{
	
}

void arena::MoverPiezaZombi(int key)
{
	
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
}
