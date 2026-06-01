#include "arena.h"
#include "freeglut.h"

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

void arena::fDatos(const Pieza& p1, const Pieza& p2)
{
	nombrePieza1 = p1.getNombre();
	nombrePieza2 = p2.getNombre();
	vidaPieza1 = p1.getVida();
	vidaPieza2 = p2.getVida();
	vidaMaxPieza1 = p1.getVidaMax();
	vidaMaxPieza2 = p2.getVidaMax();
	pieza1 = &p1;
	pieza2 = &p2;
}

// Dibuja las dos piezas en sus lados respectivos de la arena
void arena::dibujaPiezasArena() const
{
	if (pieza1 == nullptr || pieza2 == nullptr) return;
	pieza1->dibujaTablero(-SEMIANCHO / 2.0f, 0.0f);  // Para colocar las piezas en su sitio de la arena
	pieza2->dibujaTablero(+SEMIANCHO / 2.0f, 0.0f);  //
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
	if (proyectil1) proyectil1->mueve(dt);
	if (proyectil2) proyectil2->mueve(dt);
}

void arena::tecla(unsigned char key)
{
	if (!activo) return;

	if (key == 'q' || key == 'Q')
	{
		delete proyectil1;  // eliminar el anterior si existia
		// Sale desde la posicion de pieza1, hacia la derecha
		//se fuerza a salir desde el centro de la pieza, estoy hay q cambiarlo
		Vector2D pos(-SEMIANCHO / 2.0, 0.0);
		Vector2D vel(VEL_PROYECTIL, 0.0);
		proyectil1 = new Proyectil(pos, vel, 5.0);
	}

	if (key == 'k' || key == 'K')
	{
		delete proyectil2;
		// Sale desde la posicion de pieza2, hacia la izquierda
		Vector2D pos(+SEMIANCHO / 2.0, 0.0);
		Vector2D vel(-VEL_PROYECTIL, 0.0);
		proyectil2 = new Proyectil(pos, vel, 5.0);
	}
}

// Dibuja los proyectiles activos
void arena::dibujaProyectiles() const
{
	if (proyectil1) proyectil1->dibuja();
	if (proyectil2) proyectil2->dibuja();
}