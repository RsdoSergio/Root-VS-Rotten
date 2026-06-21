#include "gestorTexturas.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include"pieza.h"

void precargarTexturas() {
	const char* texturas[] = {
	"imagenes/fondo_menu_inicio.png",
	"imagenes/fondo_pausa.png",
	"imagenes/fondo_arena1.png",
	"imagenes/fondo_arena2.png",
	"imagenes/fondo_arena3.png",
	"imagenes/fondo_arena4.png",
	"imagenes/fondo_arena5.png",
	"imagenes/fondo_arena6.png",
	"imagenes/fondo_arena7.png",
	"imagenes/fondo_arena8.png",
	"imagenes/fondo_arena9.png",
	"imagenes/sprites_plantas/seta_solar.png",
	"imagenes/sprites_plantas/rabano_casillero.png",
	"imagenes/sprites_plantas/rotinabo.png",
	"imagenes/sprites_plantas/guisantralladora.png",
	"imagenes/sprites_plantas/boca_de_dragon.png",
	"imagenes/sprites_plantas/mazorcanon.png",
	"imagenes/sprites_plantas/bonk_choi.png",
	"imagenes/sprites_plantas/girasol_primitivo.png",
	"imagenes/sprites_zombies/zombie_normal.png",
	"imagenes/sprites_zombies/zombie_momia.png",
	"imagenes/sprites_zombies/zombie_globo.png",
	"imagenes/sprites_zombies/zombie_pertiga.png",
	"imagenes/sprites_zombies/zombie_dragon.png",
	"imagenes/sprites_zombies/zombie_gondola.png",
	"imagenes/sprites_zombies/zombie_yeti.png",
	"imagenes/sprites_zombies/zombie_doctor.png",
	"imagenes/obstaculos/obs1.png",
	"imagenes/obstaculos/obs2.png",
	"imagenes/obstaculos/obs3.png",
	"imagenes/obstaculos/obs4.png",
	"imagenes/obstaculos/obs5.png",
	"imagenes/obstaculos/obs6.png",
	};

	int total = sizeof(texturas) / sizeof(texturas[0]); //nº elementos

	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::setFont("fuentes/texto.ttf", 50);
	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::printxy("Cargando...  0%", -10.0f, 0.0f);
	glutSwapBuffers();

	for (int i = 0; i < total; i++) {
		ETSIDI::getTexture(texturas[i]);

		int pct = (i + 1) * 100 / total; //ptc --> porcentaje
		std::string msg = "Cargando... " + std::to_string(pct) + "%";

		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		glClear(GL_COLOR_BUFFER_BIT);

		ETSIDI::setFont("fuentes/texto.ttf", 50);
		ETSIDI::setTextColor(1.f, 1.f, 1.f);
		ETSIDI::printxy(msg.c_str(), -10.0f, 0.0f);
		glutSwapBuffers();
	}
}

void dibujarSprite(const std::string& ruta, float x, float y, float tam, int frame, int totalFrames)
{
	if (ruta.empty()) return;

	float u0 = frame / (float)totalFrames;
	float u1 = (frame + 1) / (float)totalFrames;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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