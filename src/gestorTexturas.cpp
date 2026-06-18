#include "gestorTexturas.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include"pieza.h"

void precargarTexturas() {
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::setFont("fuentes/texto.ttf", 50);
	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::printxy("Cargando...  0%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_menu_inicio.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando...  9%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_pausa.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 18%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena1.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 27%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena2.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 36%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena3.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 45%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena4.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 54%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena5.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 63%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena6.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 72%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena7.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 81%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena8.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 90%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena9.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 100%", -10.0f, 0.0f);
	glutSwapBuffers();
}


void dibujarSprite(const std::string& ruta, float x, float y, float tam,DirMovimiento dir, int totalFrames)
{
	
	if (ruta.empty()) return;

	int frame = 0;
	switch (dir) {
	case DirMovimiento::ESTE:  frame = 1; break;
	case DirMovimiento::OESTE: frame = 2; break;
	case DirMovimiento::NORTE: frame = 3; break;
	case DirMovimiento::SUR:   frame = 4; break;
	default:                   frame = 0; break;
	}

	float u0 = frame / (float)totalFrames;
	float u1 = (frame + 1) / (float)totalFrames;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(u0, 1.0f); glVertex3f(x - tam, y - tam, 0);
	glTexCoord2f(u1, 1.0f); glVertex3f(x + tam, y - tam, 0);
	glTexCoord2f(u1, 0.0f); glVertex3f(x + tam, y + tam, 0);
	glTexCoord2f(u0, 0.0f); glVertex3f(x - tam, y + tam, 0);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}