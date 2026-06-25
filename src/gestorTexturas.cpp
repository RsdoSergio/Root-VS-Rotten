#include "gestorTexturas.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include "piezas/pieza.h"

void precargarTexturas() {
	const char* texturas[] = {
	"imagenes/fondos/fondo_menu_inicio.png",
	"imagenes/fondos/fondo_pausa.png",
	"imagenes/fondos/fondo_arena1.png",
	"imagenes/fondos/fondo_arena2.png",
	"imagenes/fondos/fondo_arena3.png",
	"imagenes/fondos/fondo_arena4.png",
	"imagenes/fondos/fondo_arena5.png",
	"imagenes/fondos/fondo_arena6.png",
	"imagenes/fondos/fondo_arena7.png",
	"imagenes/fondos/fondo_arena8.png",
	"imagenes/fondos/fondo_arena9.png",
	"imagenes/sprites_plantas/seta_solar.png",
"imagenes/sprites_plantas/seta_solar_ataque.png",
"imagenes/sprites_plantas/rabano_casillero.png",
"imagenes/sprites_plantas/rabano_casillero_ataque.png",
"imagenes/sprites_plantas/rotinabo.png",
"imagenes/sprites_plantas/rotinabo_ataque.png",
"imagenes/sprites_plantas/guisantralladora.png",
"imagenes/sprites_plantas/guisantralladora_ataque.png",
"imagenes/sprites_plantas/boca_de_dragon.png",
"imagenes/sprites_plantas/boca_de_dragon_ataque.png",
"imagenes/sprites_plantas/mazorcanon.png",
"imagenes/sprites_plantas/mazorcanon_ataque.png",
"imagenes/sprites_plantas/bonk_choi.png",
"imagenes/sprites_plantas/bonk_choi_ataque.png",
"imagenes/sprites_plantas/girasol_primitivo.png",
"imagenes/sprites_plantas/girasol_primitivo_ataque.png",
"imagenes/sprites_zombies/zombie_normal.png",
"imagenes/sprites_zombies/zombie_normal_ataque.png",
"imagenes/sprites_zombies/zombie_momia.png",
"imagenes/sprites_zombies/zombie_momia_ataque.png",
"imagenes/sprites_zombies/zombie_globo.png",
"imagenes/sprites_zombies/zombie_globo_ataque.png",
"imagenes/sprites_zombies/zombie_pertiga.png",
"imagenes/sprites_zombies/zombie_pertiga_ataque.png",
"imagenes/sprites_zombies/zombie_dragon.png",
"imagenes/sprites_zombies/zombie_dragon_ataques.png",
"imagenes/sprites_zombies/zombie_gondola.png",
"imagenes/sprites_zombies/zombie_gondola_ataque.png",
"imagenes/sprites_zombies/zombie_yeti.png",
"imagenes/sprites_zombies/zombie_yeti_ataque.png",
"imagenes/sprites_zombies/zombie_doctor.png",
"imagenes/sprites_zombies/zombie_doctor_ataque.png",
	"imagenes/obstaculos/obs1.png",
	"imagenes/obstaculos/obs2.png",
	"imagenes/obstaculos/obs3.png",
	"imagenes/obstaculos/obs4.png",
	"imagenes/obstaculos/obs5.png",
	"imagenes/obstaculos/obs6.png",
	"imagenes/fondos/fondo_tablero.png",
	"imagenes/turnos/turno_plantas.png",
	"imagenes/turnos/turno_zombies.png",
	"imagenes/carteles/cartel_vs.png",
	"imagenes/carteles/cartel_plantas_ganan.png",
	"imagenes/carteles/cartel_plantas_pierden.png",
	"imagenes/fondos/combate_20.png",
	"imagenes/fondos/combate_40.png",
	"imagenes/fondos/combate_60.png",
	"imagenes/fondos/combate_80.png",
	"imagenes/fondos/combate_100.png"
	};

	int total = sizeof(texturas) / sizeof(texturas[0]); //nº elementos

	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::setFont("fuentes/auxiliar.ttf", 70);
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

		ETSIDI::setFont("fuentes/auxiliar.ttf", 70);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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