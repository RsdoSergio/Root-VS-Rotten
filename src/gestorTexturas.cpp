#include "gestorTexturas.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include "piezas/pieza.h"

void actualizarPantallaCarga(const std::string& msg) {
	glClear(GL_COLOR_BUFFER_BIT); glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::setFont("fuentes/auxiliar.ttf", 70);
	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::printxy(msg.c_str(), -10.0f, 0.0f);
	glutSwapBuffers();
}

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
	"imagenes/sprites_plantas/aura_transform.png",
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
	"imagenes/sprites_zombies/aura_transform.png",
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
	"imagenes/fondos/combate_100.png",
	"imagenes/proyectiles/proyectil_doctor.png",
	"imagenes/proyectiles/proyectil_girasol.png",
	"imagenes/proyectiles/proyectil_gisantralladora.png",
	"imagenes/proyectiles/proyectil_gondola.png",
	"imagenes/proyectiles/proyectil_mazorcanon.png",
	"imagenes/proyectiles/proyectil_momia.png",
	"imagenes/proyectiles/proyectil_pertiga.png",
	"imagenes/proyectiles/proyectil_rabano.png",
	"imagenes/carteles/fin_juego_plantas.png",
	"imagenes/carteles/fin_juego_zombies.png",
	"imagenes/carteles/rellenar_nombre_plantas.png",
	"imagenes/carteles/rellenar_nombre_zombies.png",
	};

	const char* musicas[] = {
		"audio/INTRO.mp3",
		"audio/TABLERO1.mp3",
		"audio/TABLERO2.mp3",
		"audio/TABLERO3.mp3",
		"audio/TABLERO4.mp3",
		"audio/TABLERO5.mp3",
		"audio/TABLERO6.mp3",
		"audio/TABLERO7.mp3",
		"audio/COMBATE1.mp3",
		"audio/COMBATE2.mp3",
		"audio/COMBATE3.mp3",
		"audio/COMBATE4.mp3",
		"audio/COMBATE5.mp3",
		"audio/COMBATE6.mp3",
		"audio/COMBATE7.mp3",
		"audio/COMBATE8.mp3",
		"audio/VIOLENTA1.mp3",
		"audio/VIOLENTA2.mp3",
		"audio/VIOLENTA3.mp3",
		"audio/VIOLENTA4.mp3",
		"audio/VIOLENTA5.mp3",
		"audio/VIOLENTA6.mp3",
		"audio/VIOLENTA7.mp3",
		"audio/PANTALLAFINAL1.mp3",
		"audio/PANTALLAFINAL2.mp3",
		"audio/PANTALLAFINAL3.mp3",
		"audio/PANTALLAFINAL4.mp3"
	};

	const char* efectos[] = {
		"audio/MENU.mp3",
		"audio/SELECCION_EN_MENU.mp3",
		"audio/SELECCION_HECHIZO.mp3",
		"audio/FIGHT.mp3",
		"audio/ATAQUE_A_MELEE.mp3",
		"audio/ATAQUE_A_DISTANCIA.mp3"
	};

	int totalTexturas = sizeof(texturas) / sizeof(texturas[0]);
	int totalMusicas = sizeof(musicas) / sizeof(musicas[0]);
	int totalEfectos = sizeof(efectos) / sizeof(efectos[0]);
	int total = totalTexturas + totalMusicas + totalEfectos;
	int cargados = 0;

	actualizarPantallaCarga("Cargando...  0%");

	for (int i = 0; i < totalTexturas; i++) {
		ETSIDI::getTexture(texturas[i]);
		cargados++;
		actualizarPantallaCarga("Cargando... " + std::to_string(cargados * 100 / total) + "%");
	}

	for (int i = 0; i < totalMusicas; i++) {
		ETSIDI::playMusica(musicas[i], false);
		ETSIDI::stopMusica();
		cargados++;
		actualizarPantallaCarga("Cargando... " + std::to_string(cargados * 100 / total) + "%");
	}

	for (int i = 0; i < totalEfectos; i++) {
		ETSIDI::play(efectos[i]);
		cargados++;
		actualizarPantallaCarga("Cargando... " + std::to_string(cargados * 100 / total) + "%");
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