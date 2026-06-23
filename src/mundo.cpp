#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero.h"
#include <vector>
#include "audio.h"
#include "audio.h"
#include "gestorTexturas.h"
#include <ctime>
#include "hechizos/hechizoExchange.h"

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

	if (key == ' ' && magoSeleccionado != nullptr) {
		mostrarPanelHechizos = !mostrarPanelHechizos;
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

	if (magoSeleccionado != nullptr && !tablero.modoHechizoActivo() && !eligiendoRevive && !eligiendoExchangeOrigen && !eligiendoTeleportOrigen)
	{
		Mago* m = dynamic_cast<Mago*>(magoSeleccionado);
		if (m != nullptr)
		{
			if (key == '2' && m->puedeUsarHechizo(Hechizo::HEAL)) {
				tablero.activarHechizo(m, &hechizoHeal);
				m->usarHechizo(Hechizo::HEAL);
				magoSeleccionado = nullptr;
			}

			if (key == '3' && m->puedeUsarHechizo(Hechizo::REVIVE)) {
				eligiendoRevive = true;
				mostrarPanelHechizos = true;
			}

			if (key == '6' && m->puedeUsarHechizo(Hechizo::EXCHANGE)) {
				eligiendoExchangeOrigen = true; // paso 1: elegir la primera pieza en el tablero
			}

			if (key == '1' && m->puedeUsarHechizo(Hechizo::TELEPORT)) {
				eligiendoTeleportOrigen = true; // paso 1: elegir la pieza a teletransportar
			}

			if (key == '4' && m->puedeUsarHechizo(Hechizo::IMPRISON)) {
				tablero.activarHechizo(m, &hechizoImprison);
				m->usarHechizo(Hechizo::IMPRISON);
				magoSeleccionado = nullptr;
			}
			if (key == '5' && m->puedeUsarHechizo(Hechizo::SHIFT_TIME)) {
				hechizoShiftTime.ejecutar(tablero, m, Pos()); // Pos() vacia: no se usa el objetivo
				m->usarHechizo(Hechizo::SHIFT_TIME);
				mensajeFeedback = hechizoShiftTime.getMensajeExito();
				tiempoFeedback = 3.0;
				magoSeleccionado = nullptr;
			}

			// futuro: '5' SHIFT_TIME, '7' SUMMON
		}
	}

	// Sub-menu de Revive: el jugador elige QUE pieza revivir antes de elegir donde
	if (eligiendoRevive)
	{
		Mago* m = dynamic_cast<Mago*>(magoSeleccionado);
		if (m != nullptr && key >= '1' && key <= '9')
		{
			int indice = key - '1'; // '1' -> indice 0, '2' -> indice 1...
			if (hechizoRevive.elegirPieza(tablero, m, indice))
			{
				tablero.activarHechizo(m, &hechizoRevive); // ahora si, ya con pieza elegida
				m->usarHechizo(Hechizo::REVIVE);
				eligiendoRevive = false;
				magoSeleccionado = nullptr;
			}
		}
	}

	if (key == 27) {
		tablero.cancelarSeleccion();
		tablero.cancelarHechizo();
		magoSeleccionado = nullptr;
		eligiendoRevive = false;
		hechizoRevive.resetear();
		eligiendoExchangeOrigen = false;
		hechizoExchange.resetear();
		eligiendoTeleportOrigen = false;
		hechizoTeleport.resetear();
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
		HechizoBase* usado = tablero.getHechizoActivo();
		bool exito = tablero.aplicarHechizo(casilla);
		if (exito && usado != nullptr) {
			mensajeFeedback = usado->getMensajeExito();
			tiempoFeedback = 3.0;
		}
		magoSeleccionado = nullptr; // cerramos el menu de hechizos
		return;
	}

	if (eligiendoExchangeOrigen)
	{
		Mago* m = dynamic_cast<Mago*>(magoSeleccionado);
		if (m != nullptr && hechizoExchange.elegirOrigen(tablero, m, casilla))
		{
			tablero.activarHechizo(m, &hechizoExchange); // el siguiente clic es el destino
			m->usarHechizo(Hechizo::EXCHANGE);
			eligiendoExchangeOrigen = false;
			magoSeleccionado = nullptr;
		}
		return; // mientras se elige origen, este clic no se interpreta como movimiento normal
	}

	if (eligiendoTeleportOrigen)
	{
		Mago* m = dynamic_cast<Mago*>(magoSeleccionado);
		if (m != nullptr && hechizoTeleport.elegirOrigen(tablero, m, casilla))
		{
			tablero.activarHechizo(m, &hechizoTeleport); // el siguiente clic es la casilla destino
			m->usarHechizo(Hechizo::TELEPORT);
			eligiendoTeleportOrigen = false;
			magoSeleccionado = nullptr;
		}
		return; // mientras se elige origen, este clic no se interpreta como movimiento normal
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
	tablero.setTurnoActual(numeroJugada);
	magoSeleccionado = nullptr; // <-- añadir: cualquier movimiento normal limpia la seleccion de mago
	if (turno == 0)
		cursor.setBloqueado(tablero.piezaBloqueada(cursor.getPosicion()));
	else
		cursor2.setBloqueado(tablero.piezaBloqueada(cursor2.getPosicion()));

	if (combate) {
		BandoVentaja ventaja = tablero.getBandoVentaja();
		arena.fDatos(*tablero.getPersonaje1(), *tablero.getPersonaje2(), ventaja);
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
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		case AccionTransicion::ABRIR_CARTEL_VERSUS:
			rutaCartel = "imagenes/carteles/cartel_vs.png";
			mostrandoCartel = true;
			tiempoCartel = 2.0;
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		case AccionTransicion::ABRIR_CARTEL_RESULTADO:
			rutaCartel = arena.getPlantaGano() ? "imagenes/carteles/cartel_plantas_ganan.png" : "imagenes/carteles/cartel_plantas_pierden.png";
			mostrandoCartel = true;
			tiempoCartel = 2.0;
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		case AccionTransicion::CERRAR_CARTEL_VERSUS:
			arena.fDatos(*tablero.getPersonaje1(), *tablero.getPersonaje2(), tablero.getBandoVentaja());
			arena.activa();
			mostrandoCartel = false;
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		case AccionTransicion::CERRAR_CARTEL_RESULTADO:
			tablero.resolverCombate(arena.getPlantaGano());
			tablero.avanzarCiclo();
			arena.desactiva();
			Audio::playMusicaTablero();
			mostrandoCartel = false;
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		default:
			break;
		}
	}

	if (mostrandoCartel && !transicion.estaActiva())
	{
		tiempoCartel -= 0.025;
		if (tiempoCartel <= 0.0)
		{
			accionPendiente = (rutaCartel.find("cartel_vs") != std::string::npos) ? AccionTransicion::CERRAR_CARTEL_VERSUS : AccionTransicion::CERRAR_CARTEL_RESULTADO;
			transicion.cubrir();
		}
	}

	if (!enPartida || enPausa) return;

	bool estabaActiva = arena.estaActiva();
	if (arena.estaActiva()) arena.mueve(0.025);

	// Si la arena acaba de desactivarse este frame → resolver resultado
	if (arena.estaActiva() && arena.combateTerminado() && accionPendiente == AccionTransicion::NINGUNA && !mostrandoCartel)
	{
		accionPendiente = AccionTransicion::ABRIR_CARTEL_RESULTADO;
		transicion.cubrir();
	}

	int resultado = tablero.actualizarAnimacion(0.025);
	if (resultado == 1 && accionPendiente == AccionTransicion::NINGUNA)
	{
		accionPendiente = AccionTransicion::ABRIR_CARTEL_VERSUS;
		transicion.cubrir();
	}

	if (tiempoFeedback > 0.0) {
		tiempoFeedback -= 0.025;
		if (tiempoFeedback <= 0.0) mensajeFeedback.clear();
	}

	if (resultado == 2) {
		turno = 1 - turno;
		tablero.setTurnoActual(numeroJugada); 
		numeroJugada++;
	}

	// Provisional: libera piezas aprisionadas tras 3 turnos, hasta que exista el ciclo de color
	for (int i = 0; i < FILAS; i++)
		for (int j = 0; j < COLS; j++) {
			Pieza* p = tablero.getPieza(Pos(i, j));
			if (p && p->estaAprisionada() && (numeroJugada - p->getTurnoAprisionamiento() >= 3))
				p->liberar();
		}
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
	dibujaPanelHechizos();
	if (enPausa) menu.dibujaPausa(opcionPausa);

	if (mostrandoCartel && !rutaCartel.empty())
	{
		extern float G_XMAX;
		extern float G_YMAX;
		auto tex = ETSIDI::getTexture(rutaCartel.c_str());
		if (tex.id != 0)
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, tex.id);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-G_XMAX, -G_YMAX, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(G_XMAX, -G_YMAX, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(G_XMAX, G_YMAX, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-G_XMAX, G_YMAX, 0);
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
	}

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

static void dibujaTexto(float x, float y, const std::string& texto)
{
	glRasterPos2f(x, y);
	for (char c : texto)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

std::string Mundo::generarTextoPanel() const
{
	if (!mensajeFeedback.empty())
		return mensajeFeedback;

	Mago* m = dynamic_cast<Mago*>(magoSeleccionado);
	if (m == nullptr) return "";

	if (eligiendoRevive)
	{
		auto& candidatas = hechizoRevive.getCandidatas(const_cast<Tablero&>(tablero), m);
		if (candidatas.empty())
			return "No hay piezas que revivir";

		// Agrupar por nombre para no repetir entradas (ej: 2 Zombis -> "Zombi x2")
		std::vector<std::string> nombresUnicos;
		std::vector<int> contadores;

		for (Pieza* p : candidatas)
		{
			std::string nombre = p->getNombre();
			bool encontrado = false;
			for (size_t i = 0; i < nombresUnicos.size(); i++)
			{
				if (nombresUnicos[i] == nombre) {
					contadores[i]++;
					encontrado = true;
					break;
				}
			}
			if (!encontrado) {
				nombresUnicos.push_back(nombre);
				contadores.push_back(1);
			}
		}

		std::string texto;
		for (size_t i = 0; i < nombresUnicos.size(); i++)
		{
			texto += std::to_string(i + 1) + "." + nombresUnicos[i];
			if (contadores[i] > 1)
				texto += " x" + std::to_string(contadores[i]);
			texto += "  ";
		}
		return texto;
	}

	if (eligiendoExchangeOrigen)
		return "Elige la pieza aliada de origen";

	if (eligiendoTeleportOrigen)
		return "Elige la pieza aliada a teletransportar";

	if (tablero.modoHechizoActivo())
	{
		HechizoBase* h = tablero.getHechizoActivo();
		return h ? h->getMensajeSeleccion() : "";
	}

	std::string texto;
	const char* nombres[7] = { "Teleport", "Heal", "Revive", "Imprison", "ShiftTime", "Exchange", "Summon" };
	for (int i = 0; i < 7; i++)
		texto += std::to_string(i + 1) + "." + nombres[i] + "  ";
	return texto;
}
void Mundo::dibujaPanelHechizos() const
{
	bool debeMostrarse = mostrarPanelHechizos || eligiendoRevive || eligiendoExchangeOrigen || eligiendoTeleportOrigen || tablero.modoHechizoActivo();
	if (!debeMostrarse) return;
	if (magoSeleccionado == nullptr && mensajeFeedback.empty() && !tablero.modoHechizoActivo()) return;
	std::string texto = generarTextoPanel();
	if (texto.empty()) return;

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	float anchoCaja = COLS * TAM_CELDA;
	float altoCaja = 1.6f;
	float x0 = -anchoCaja / 2.0f;
	float y0 = -(FILAS * TAM_CELDA) / 2.0f - altoCaja - 0.4f;

	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(x0, y0);
	glVertex2f(x0 + anchoCaja, y0);
	glVertex2f(x0 + anchoCaja, y0 + altoCaja);
	glVertex2f(x0, y0 + altoCaja);
	glEnd();

	glColor3ub(255, 255, 255);
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x0, y0);
	glVertex2f(x0 + anchoCaja, y0);
	glVertex2f(x0 + anchoCaja, y0 + altoCaja);
	glVertex2f(x0, y0 + altoCaja);
	glEnd();
	glLineWidth(1.0f);

	glColor3ub(255, 255, 255);
	dibujaTexto(x0 + 0.3f, y0 + altoCaja / 2.0f - 0.3f, texto);
}