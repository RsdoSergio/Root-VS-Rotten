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
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_archon.png").id);
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