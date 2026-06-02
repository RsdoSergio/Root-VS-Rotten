#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero.h"
#include <vector>
#include "audio.h"
#include "audio.h"
#include "gestorTexturas.h"

void Mundo::inicializa() {
	tablero.inicializaTablero();
	tablero.colocarPiezasIniciales();
	precargarTexturas();

	//inicializacion de peones para ambos bandos
	const float TAM = 2.8f; //tener presente el tamaño de cada celda
	const float pos = (9 * TAM) / 2.0f;
	Audio::playMusica("audio/INTRO.mp3", true);
};

//Metodo se gestiona la pulsacion de teclas, y como afecta a la simulacion
void Mundo::tecla(unsigned char key)
{
	if (!enPartida) {
		menu.tecla(key);
		if (menu.seEligeJugar())
			enPartida = true;
		return;
	}

	if (key == 'm' || key == 'M') {
		enPausa = !enPausa;
		opcionPausa = 0;   // resetea al abrir
		return;
	}

	if (enPausa) {
		if (key == 'w' || key == 'W') opcionPausa = 0;
		if (key == 's' || key == 'S') opcionPausa = 1;
		if (key == 13) {
			if (opcionPausa == 0) enPausa = false;
			if (opcionPausa == 1) exit(0);
		}
		return;
	}
	if (arena.estaActiva()) {
		
		if (key == 'w' || key == 'W') arena.recibirMovimiento(0, DIR_ARRIBA, true);
		if (key == 's' || key == 'S') arena.recibirMovimiento(0, DIR_ABAJO, true);
		if (key == 'a' || key == 'A') arena.recibirMovimiento(0, DIR_IZQ, true);
		if (key == 'd' || key == 'D') arena.recibirMovimiento(0, DIR_DCHA, true);
			
		arena.tecla(key); // disparos,    q/k disparan en la arena
		
		return;
	}

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
	if (arena.estaActiva()) arena.mueve(0.025); // para no mover los poryectiles si no estan en la arena
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
	if (enPausa) menu.dibujaPausa(opcionPausa);
}
// Flechas
void Mundo::teclaEspecial(int key)
{
	if (!enPartida) return;

	if (arena.estaActiva()) {
		if (key == GLUT_KEY_UP)    arena.recibirMovimiento(1, DIR_ARRIBA, true);
		if (key == GLUT_KEY_DOWN)  arena.recibirMovimiento(1, DIR_ABAJO, true);
		if (key == GLUT_KEY_LEFT)  arena.recibirMovimiento(1, DIR_IZQ, true);
		if (key == GLUT_KEY_RIGHT) arena.recibirMovimiento(1, DIR_DCHA, true);
		return;
	}
	if (turno == 1) cursor2.moverFlechas(key);
}

void Mundo::teclaLevantada(unsigned char key)
{
	if (!arena.estaActiva()) return;
	if (key == 'w' || key == 'W') arena.recibirMovimiento(0, DIR_ARRIBA, false);
	if (key == 's' || key == 'S') arena.recibirMovimiento(0, DIR_ABAJO, false);
	if (key == 'a' || key == 'A') arena.recibirMovimiento(0, DIR_IZQ, false);
	if (key == 'd' || key == 'D') arena.recibirMovimiento(0, DIR_DCHA, false);
}

void Mundo::teclaEspecialLevantada(int key)
{
	if (!arena.estaActiva()) return;
	if (key == GLUT_KEY_UP)    arena.recibirMovimiento(1, DIR_ARRIBA, false);
	if (key == GLUT_KEY_DOWN)  arena.recibirMovimiento(1, DIR_ABAJO, false);
	if (key == GLUT_KEY_LEFT)  arena.recibirMovimiento(1, DIR_IZQ, false);
	if (key == GLUT_KEY_RIGHT) arena.recibirMovimiento(1, DIR_DCHA, false);
}