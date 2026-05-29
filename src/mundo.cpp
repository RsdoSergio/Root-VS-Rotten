#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero.h"
#include <vector>
#include "audio.h"
#include "audio.h"

void Mundo::inicializa() {
	tablero.inicializaTablero();
	tablero.colocarPiezasIniciales();

	//inicializacion de piezas para el juego

	//inicializacion de peones para ambos bandos
	const float TAM = 2.8f; //tener presente el tamaño de cada celda
	const float pos = (9 * TAM) / 2.0f;
	Audio::playMusica("audio/INTRO.mp3", true);
};

//Metodo se gestiona la pulsacion de teclas, y como afecta a la simulacion
void Mundo::tecla(unsigned char key)
{
	if (!enPartida)
	{
		menu.tecla(key);
		if (menu.seEligeJugar())
			enPartida = true;
		return;   // el tablero y el cursor no tocan nada
	}

	if (key == 'm') {
		enPausa = !enPausa;   //m alterna pausa/reanuda
		return;
	}

	if (enPausa) return; //si esta en pausa, se ignora el resto

	// Cada cursor se mueve solo durante su turno
	if (turno == 0) cursor.mover(key);  // WASD

	if (key == 13) {
		// El cursor activo depende del turno
		Pos posActiva = (turno == 0) ? cursor.getPosicion() : cursor2.getPosicion();
		bool combate = tablero.gestionarEntrada(posActiva, turno);
		if (combate) {
			arena.fDatos(*tablero.getPersonaje1(), *tablero.getPersonaje2());
			arena.activa();
		}
	}

	if (key == 27) tablero.cancelarSeleccion(); //Escape para cancelar seleccion
	if (key == 'v') arena.desactiva();
}

void Mundo::mueve()
{
	if (!enPartida || enPausa) return;
}

//Metodo que gestiona el dibujo de la simulacion
void Mundo::dibuja()
{
	if (!enPartida)
	{
		menu.dibuja();
		return;
	}

	//Resets necesarios sino no funciona bien
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glColor3ub(255, 255, 255);

	tablero.dibuja(cursor);
	cursor.dibuja();   // borde amarillo
	cursor2.dibuja();  // borde morado
	//caja.dibuja();
	arena.dibuja();
	menu.dibujaTeclaMenu();
	if (enPausa) menu.dibujaPausa();
}
// Flechas
void Mundo::teclaEspecial(int key)
{
	if (!enPartida) return;
	if (turno == 1) cursor2.moverFlechas(key);
}