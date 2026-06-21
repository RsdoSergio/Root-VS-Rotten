#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero.h"
#include <vector>
#include "audio.h"
#include "audio.h"
#include "gestorTexturas.h"
#include <ctime>

void Mundo::inicializa() {
	srand((unsigned int)time(nullptr));
	tablero.inicializaTablero();
	tablero.colocarPiezasIniciales();  //inicializacion de piezas para el juego

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLS; j++) {
			Pieza* p = tablero.getPieza(Pos(i, j));
			if (p != nullptr)
				ListaPieza.agregar(p);
		}
	}

	precargarTexturas();

	//inicializacion de peones para ambos bandos
	const float TAM = 2.8f; //tener presente el tamaño de cada celda
	const float pos = (9 * TAM) / 2.0f;
	Audio::playMusica("audio/INTRO.mp3", true);
};

//Metodo se gestiona la pulsacion de teclas, y como afecta a la simulacion
void Mundo::tecla(unsigned char key)
{
	if (transicion.estaActiva()) return;

	if (!enPartida) {
		menu.tecla(key);
		if (menu.seEligeJugar() && accionPendiente == AccionTransicion::NINGUNA) {
			accionPendiente = AccionTransicion::EMPEZAR_PARTIDA;
			transicion.cubrir();
		}
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

	if (tablero.estaAnimando()) return; // ignorar teclas durante movimiento de piezas en tablero
	// Cada cursor se mueve solo durante su turno
	// Movimiento por teclado sustituido por el raton (ver Mundo::clicRaton)
	// if (turno == 0) cursor.mover(key);  // WASD

	if (key == 13) {
		// El cursor activo depende del turno
		Pos posActiva = (turno == 0) ? cursor.getPosicion() : cursor2.getPosicion();
		jugarCasilla(posActiva);
	}

	if (magoSeleccionado != nullptr && !tablero.modoHechizoActivo())
	{
		Mago* m = dynamic_cast<Mago*>(magoSeleccionado);
		if (m != nullptr)
		{
			if (key == '2' && m->puedeUsarHechizo(Hechizo::HEAL)) {
				tablero.activarHechizo(m, &hechizoHeal);
				m->usarHechizo(Hechizo::HEAL);
				magoSeleccionado = nullptr;
			}
			// futuro: '1' TELEPORT, '3' REVIVE, '4' IMPRISON, '5' SHIFT_TIME, '6' EXCHANGE, '7' SUMMON
		}
	}

	if (key == 27) {
		tablero.cancelarSeleccion(); //Escape para cancelar seleccion
		tablero.cancelarHechizo();
		magoSeleccionado = nullptr;
		cursor.setBloqueado(false);
		cursor2.setBloqueado(false);
		if (key == 'v') arena.desactiva();
	}
}

// Logica comun de "intentar jugar" una casilla: seleccionar pieza propia o, si ya
// habia una seleccionada, intentar mover/combatir contra la casilla indicada.
// La usan tanto el teclado (tecla(), con key==13) como el raton (clicRaton()).
void Mundo::jugarCasilla(Pos casilla)
{
	if (tablero.modoHechizoActivo())
	{
		tablero.aplicarHechizo(casilla);
		magoSeleccionado = nullptr; // cerramos el menu de hechizos
		return;
	}

	if (magoSeleccionado == nullptr)
	{
		Pieza* p = tablero.getPieza(casilla);
		Mago* m = dynamic_cast<Mago*>(p);
		if (m != nullptr && (int)m->getBando() == turno)
		{
			magoSeleccionado = m;
			return;
		}
	}

	bool combate = tablero.gestionarEntrada(casilla, turno);
	if (turno == 0)
		cursor.setBloqueado(tablero.piezaBloqueada(cursor.getPosicion()));
	else
		cursor2.setBloqueado(tablero.piezaBloqueada(cursor2.getPosicion()));

	if (combate) {
		arena.fDatos(*tablero.getPersonaje1(), *tablero.getPersonaje2());
		arena.activa();
	}
}

void Mundo::mueve()
{
	transicion.actualiza(0.025);

	if (transicion.estaCubierta() && accionPendiente != AccionTransicion::NINGUNA)
	{
		switch (accionPendiente)
		{
		case AccionTransicion::EMPEZAR_PARTIDA:
			enPartida = true;
			Audio::playMusicaTablero();
			break;
		case AccionTransicion::ENTRAR_ARENA:
			arena.fDatos(*tablero.getPersonaje1(), *tablero.getPersonaje2());
			arena.activa();
			break;
		case AccionTransicion::VOLVER_TABLERO:
			tablero.resolverCombate(arena.getPlantaGano());
			arena.desactiva();
			Audio::playMusicaTablero();
			break;
		default:
			break;
		}
		accionPendiente = AccionTransicion::NINGUNA;
		transicion.descubrir();
	}

	if (!enPartida || enPausa) return;

	bool estabaActiva = arena.estaActiva();
	if (arena.estaActiva()) arena.mueve(0.025);

	// Si la arena acaba de desactivarse este frame → resolver resultado
	if (arena.estaActiva() && arena.combateTerminado() && accionPendiente == AccionTransicion::NINGUNA)
	{
		accionPendiente = AccionTransicion::VOLVER_TABLERO;
		transicion.cubrir();
	}

	int resultado = tablero.actualizarAnimacion(0.025);
	if (resultado == 1 && accionPendiente == AccionTransicion::NINGUNA)
	{
		accionPendiente = AccionTransicion::ENTRAR_ARENA;
		transicion.cubrir();
	}
	if (resultado == 2)
		turno = 1 - turno;
}

//Metodo que gestiona el dibujo de la simulacion
void Mundo::dibuja()
{
	if (!enPartida)
	{
		menu.dibuja();
		transicion.dibuja();
		return;
	}

	//Resets necesarios sino no funciona bien
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glColor3ub(255, 255, 255);

	tablero.dibuja(cursor, turno);
	cursor.dibuja();   // borde amarillo
	cursor2.dibuja();  // borde morado
	//caja.dibuja();
	arena.dibuja();
	if (enPausa) menu.dibujaPausa(opcionPausa);
	transicion.dibuja();
}
// Flechas
void Mundo::teclaEspecial(int key)
{
	if (transicion.estaActiva()) return;
	if (!enPartida) return;

	if (arena.estaActiva()) {
		if (key == GLUT_KEY_UP)    arena.recibirMovimiento(1, DIR_ARRIBA, true);
		if (key == GLUT_KEY_DOWN)  arena.recibirMovimiento(1, DIR_ABAJO, true);
		if (key == GLUT_KEY_LEFT)  arena.recibirMovimiento(1, DIR_IZQ, true);
		if (key == GLUT_KEY_RIGHT) arena.recibirMovimiento(1, DIR_DCHA, true);
		return;
	}
	if (tablero.estaAnimando()) return;
	// Movimiento por teclado sustituido por el raton (ver Mundo::clicRaton)
	// if (turno == 1) cursor2.moverFlechas(key);
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

// G_XMAX/G_YMAX se definen en main.cpp y se actualizan en OnReshape: delimitan,
// en coordenadas de mundo, la zona visible que dibuja glOrtho.
extern float G_XMAX;
extern float G_YMAX;

// Gestiona un clic de raton sobre la ventana del juego.
// boton/estado siguen la misma idea que los key de teclado: aqui solo nos
// interesa el flanco de bajada del boton izquierdo (equivalente a pulsar Enter
// tras mover el cursor con WASD/flechas).
void Mundo::clicRaton(int boton, int estado, int xPixel, int yPixel)
{
	if (transicion.estaActiva()) return;
	if (boton != GLUT_LEFT_BUTTON || estado != GLUT_DOWN) return;
	if (!enPartida || enPausa) return;
	if (arena.estaActiva()) return;        // en la arena el raton no se usa
	if (tablero.estaAnimando()) return;     // igual que con teclado: ignorar durante animacion

	int anchoVentana = glutGet(GLUT_WINDOW_WIDTH);
	int altoVentana = glutGet(GLUT_WINDOW_HEIGHT);
	if (anchoVentana <= 0 || altoVentana <= 0) return;

	// FreeGLUT da (xPixel,yPixel) con origen arriba-izquierda.
	// Lo pasamos a coordenadas de mundo, sabiendo que glOrtho cubre
	// [-G_XMAX,G_XMAX] x [-G_YMAX,G_YMAX] sobre toda la ventana.
	float xMundo = (xPixel / (float)anchoVentana) * (2.0f * G_XMAX) - G_XMAX;
	float yMundo = G_YMAX - (yPixel / (float)altoVentana) * (2.0f * G_YMAX); // se invierte el eje Y

	Pos casilla = tablero.screenToCell(xMundo, yMundo);
	if (!casilla.esValida()) return; // clic fuera del tablero, se ignora

	// Mueve el cursor visual del jugador en turno a la casilla clicada
	if (turno == 0) cursor.setPosicion(casilla);
	else            cursor2.setPosicion(casilla);

	jugarCasilla(casilla);
}