#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero.h"
#include <vector>
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
	const float TAM = 2.8f; //tamaño de cada celda
	const float pos = (9 * TAM) / 2.0f;
	Audio::playMusica("audio/INTRO.mp3", true);
};

void Mundo::dibujaTimer() const
{
	extern float G_XMAX;
	extern float G_YMAX;

	int totalSeg = (int)tiempoPartida;
	int minutos = totalSeg / 60;
	int segundos = totalSeg % 60;

	std::string textoMin = std::to_string(minutos);
	std::string textoSeg = std::to_string(segundos);

	if (minutos < 10)  textoMin = "0" + textoMin;
	if (segundos < 10) textoSeg = "0" + textoSeg;

	std::string buf = textoMin + "." + textoSeg;

	float bx = G_XMAX - 5.8f;
	float by = -G_YMAX + 1.0f;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0f, 0.0f, 0.0f, 0.55f);
	glBegin(GL_QUADS);
	glVertex2f(bx - 0.f, by - 0.4f);
	glVertex2f(bx + 5.4f, by - 0.4f);
	glVertex2f(bx + 5.4f, by + 1.6f);
	glVertex2f(bx - 0.f, by + 1.6f);
	glEnd();
	glDisable(GL_BLEND);

	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::setFont("fuentes/auxiliar.ttf", 40);
	ETSIDI::printxy(buf.c_str(), bx + 2, by);
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);
}

//Metodo se gestiona la pulsacion de teclas
void Mundo::tecla(unsigned char key)
{
	if (registrandoNombre)
	{
		if (key == 13 && !nombreIntroducido.empty())
		{
			Puntuaciones::guardar(nombreIntroducido, (int)tiempoPartida);
			accionPendiente = AccionTransicion::IR_AL_MENU;
			transicion.cubrir();
		}
		else if (key == 27)
		{
			registrandoNombre = false;
			accionPendiente = AccionTransicion::IR_AL_MENU;
			transicion.cubrir();
		}
		else if (key == 8 && !nombreIntroducido.empty())
			nombreIntroducido.pop_back();
		else if (key >= 32 && key < 127 && nombreIntroducido.size() < 20)
			nombreIntroducido += (char)key;
		return;
	}

	if (transicion.estaActiva()) return;

	if (!enPartida) {
		menu.tecla(key);
		if (menu.seEligeJugar() && accionPendiente == AccionTransicion::NINGUNA) {
			accionPendiente = AccionTransicion::EMPEZAR_PARTIDA;
			transicion.cubrir();
			menu.reinicia();
		}
		return;
	}

	if (key == ' ' && magoSeleccionado != nullptr) {
		mostrarPanelHechizos = !mostrarPanelHechizos;
		return;
	}

	if (key == 'm' || key == 'M') {
		enPausa = !enPausa;
		opcionPausa = 0;
		verControlesPausa = false;
		return;
	}

	if (enPausa)
	{
		if (verControlesPausa) {
			if (key == 27) verControlesPausa = false;
			return;
		}

		if (key == 'w' || key == 'W') {
			opcionPausa = (opcionPausa - 1 + 3) % 3;
			Audio::playSonido("audio/MENU.mp3");
		}

		if (key == 's' || key == 'S') {
			opcionPausa = (opcionPausa + 1) % 3;
			Audio::playSonido("audio/MENU.mp3");
		}

		if (key == 13) {
			Audio::playSonido("audio/SELECCION_EN_MENU.mp3");
			if (opcionPausa == 0) enPausa = false;
			if (opcionPausa == 1) verControlesPausa = true;
			if (opcionPausa == 2) exit(0);
		}
		return;
	}

	//partida terminada ESC = menu y ENTER = registrar nombre
	if (partidaTerminada) {
		if (key == 13)
		{
			accionPendiente = AccionTransicion::IR_A_REGISTRAR_NOMBRE;
			transicion.cubrir();
		}
		else if (key == 27)
		{
			accionPendiente = AccionTransicion::IR_AL_MENU;
			transicion.cubrir();
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

	if (turno == 0) cursor.mover(key);  // WASD

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
				Audio::playSonido("audio/SELECCION_HECHIZO.mp3");
				tablero.activarHechizo(m, &hechizoHeal);
				m->usarHechizo(Hechizo::HEAL);
				magoSeleccionado = nullptr;
			}

			if (key == '3' && m->puedeUsarHechizo(Hechizo::REVIVE)) {
				Audio::playSonido("audio/SELECCION_HECHIZO.mp3");
				eligiendoRevive = true;
				mostrarPanelHechizos = true;
			}

			if (key == '6' && m->puedeUsarHechizo(Hechizo::EXCHANGE)) {
				Audio::playSonido("audio/SELECCION_HECHIZO.mp3");
				eligiendoExchangeOrigen = true; // paso 1: elegir la primera pieza en el tablero
			}

			if (key == '1' && m->puedeUsarHechizo(Hechizo::TELEPORT)) {
				Audio::playSonido("audio/SELECCION_HECHIZO.mp3");
				eligiendoTeleportOrigen = true; // paso 1: elegir la pieza a teletransportar
			}

			if (key == '4' && m->puedeUsarHechizo(Hechizo::IMPRISON)) {
				Audio::playSonido("audio/SELECCION_HECHIZO.mp3");
				tablero.activarHechizo(m, &hechizoImprison);
				m->usarHechizo(Hechizo::IMPRISON);
				magoSeleccionado = nullptr;
			}
			if (key == '5' && m->puedeUsarHechizo(Hechizo::SHIFT_TIME)) {
				Audio::playSonido("audio/SELECCION_HECHIZO.mp3");
				hechizoShiftTime.ejecutar(tablero, m, Pos()); // Pos() vacia: no se usa el objetivo
				m->usarHechizo(Hechizo::SHIFT_TIME);
				mensajeFeedback = hechizoShiftTime.getMensajeExito();
				tiempoFeedback = 3.0;
				magoSeleccionado = nullptr;
			}

			if (key == '7' && m->puedeUsarHechizo(Hechizo::TRANSFORM)) {
				Audio::playSonido("audio/SELECCION_HECHIZO.mp3");
				hechizoTransform.ejecutar(tablero, m, Pos()); // Pos() vacia: no se usa el objetivo
				m->usarHechizo(Hechizo::TRANSFORM);
				mensajeFeedback = hechizoTransform.getMensajeExito();
				tiempoFeedback = 3.0;
				magoSeleccionado = nullptr;
			}
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

void Mundo::jugarCasilla(Pos casilla)
{
	if (tablero.modoHechizoActivo())
	{
		HechizoBase* usado = tablero.getHechizoActivo();
		bool exito = tablero.aplicarHechizo(casilla);
		if (exito && usado != nullptr) {
			mensajeFeedback = usado->getMensajeExito();
			tiempoFeedback = 3.0;
			comprobarFinPartida();
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
			
			eligiendoTeleportOrigen = false;
			magoSeleccionado = nullptr;
		}
		return; // mientras se elige origen, este clic no se interpreta como movimiento normal
	}

	if (magoSeleccionado == nullptr)
	{
		Pieza* p = tablero.getPieza(casilla);
		Mago* m = dynamic_cast<Mago*>(p);
		if (m != nullptr && (int)m->getBando() == turno && !m->estaAprisionada())
		{
			magoSeleccionado = m;
			return;
		}
	}

	bool combate = tablero.gestionarEntrada(casilla, turno);
	tablero.setTurnoActual(numeroJugada);
	magoSeleccionado = nullptr;
	if (turno == 0)
		cursor.setBloqueado(tablero.piezaBloqueada(cursor.getPosicion()));
	else
		cursor2.setBloqueado(tablero.piezaBloqueada(cursor2.getPosicion()));

	if (combate) {
		BandoVentaja ventaja = tablero.getBandoVentaja();
		Pieza* p1 = tablero.getPersonaje1();
		Pieza* p2 = tablero.getPersonaje2();

		bool b1 = tablero.esCasillaDePoder(p1->getCasilla());
		bool b2 = tablero.esCasillaDePoder(p2->getCasilla());
		arena.fDatos(*p1, *p2, ventaja, b1, b2, tablero.contarCasillasDePoder(Bando::planta), tablero.contarCasillasDePoder(Bando::zombi));
		arena.activa();
	}
}
void Mundo::comprobarFinPartida()
{
	if (partidaTerminada) return;

	// Condicion 1: algun bando controla los 5 puntos de poder
	int ganador = tablero.comprobarPuntosDePoder();
	if (ganador == 0) {
		partidaTerminada = true;
		plantasGanaronPartida = true;
		mensajeFinPartida = "ROOT GANAN";
		return;
	}
	else if (ganador == 1) {
		partidaTerminada = true;
		plantasGanaronPartida = false;
		mensajeFinPartida = "ROTTEN GANAN";
		return;
	}

	int piezasRoot = 0, piezasRotten = 0;
	bool hayRootLibre = false, hayRottenLibre = false;

	for (int i = 0; i < FILAS; i++)
		for (int j = 0; j < COLS; j++) {
			Pieza* p = tablero.getPieza(Pos(i, j));
			if (p == nullptr) continue;
			if (p->getBando() == Bando::planta) {
				piezasRoot++;
				if (!p->estaAprisionada()) hayRootLibre = true;
			}
			else {
				piezasRotten++;
				if (!p->estaAprisionada()) hayRottenLibre = true;
			}
		}

	//eliminar todas las piezas del rival
	if (piezasRoot == 0) {
		partidaTerminada = true;
		plantasGanaronPartida = false;
		mensajeFinPartida = "ROTTEN GANAN";
		return;
	}
	if (piezasRotten == 0) {
		partidaTerminada = true;
		plantasGanaronPartida = true;
		mensajeFinPartida = "ROOT GANAN";
		return;
	}

	// las piezas restantes del rival estan aprisionadas
	if (!hayRootLibre) {
		partidaTerminada = true;
		plantasGanaronPartida = false;
		mensajeFinPartida = "ROTTEN GANAN";
		return;
	}
	if (!hayRottenLibre) {
		partidaTerminada = true;
		plantasGanaronPartida = true;
		mensajeFinPartida = "ROOT GANAN";
		return;
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

			tablero.inicializaTablero();
			tablero.colocarPiezasIniciales();
			turno = 0;
			numeroJugada = 0;
			magoSeleccionado = nullptr;
			eligiendoRevive = false;
			eligiendoExchangeOrigen = false;
			eligiendoTeleportOrigen = false;

			enPartida = true;
			tiempoPartida = 0.0;
			musicaFinalSonando = false;
			pendienteMusicaTablero = true;
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		case AccionTransicion::ABRIR_CARTEL_VERSUS:
			rutaCartel = "imagenes/carteles/cartel_vs.png";
			Audio::playSonido("audio/FIGHT.mp3");

			mostrandoCartel = true;
			tiempoCartel = 3.0;
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		case AccionTransicion::ABRIR_CARTEL_RESULTADO:
			Audio::stopMusica();
			if (arena.getPlantaGano()) {
				rutaCartel = "imagenes/carteles/cartel_plantas_ganan.png";
				Audio::playSonido("audio/VICTORIA_PLANTAS.mp3");
			}
			else {
				rutaCartel = "imagenes/carteles/cartel_plantas_pierden.png";
				Audio::playSonido("audio/VICTORIA_ZOMBIS.mp3");
			}
			mostrandoCartel = true;
			tiempoCartel = 5.0;
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		case AccionTransicion::CERRAR_CARTEL_VERSUS:
		{
			Pieza* p1 = tablero.getPersonaje1();
			Pieza* p2 = tablero.getPersonaje2();

			bool boost1 = tablero.esCasillaDePoder(p1->getCasilla());
			bool boost2 = tablero.esCasillaDePoder(p2->getCasilla());
			arena.fDatos(*p1, *p2, tablero.getBandoVentaja(), boost1, boost2, tablero.contarCasillasDePoder(Bando::planta),
				tablero.contarCasillasDePoder(Bando::zombi));
			arena.activa();
			mostrandoCartel = false;
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;
		}

		case AccionTransicion::CERRAR_CARTEL_RESULTADO:
		{
			tablero.resolverCombate(arena.getPlantaGano());
			tablero.avanzarCiclo();

			Mago* m1 = dynamic_cast<Mago*>(tablero.getPersonaje1());
			if (m1 && m1->estaTransformado()) m1->revertirTransformacion();
			Mago* m2 = dynamic_cast<Mago*>(tablero.getPersonaje2());
			if (m2 && m2->estaTransformado()) m2->revertirTransformacion();

			arena.desactiva();
			pendienteMusicaTablero = true;
			mostrandoCartel = false;
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			comprobarFinPartida();
			break;
		}

		case AccionTransicion::IR_A_REGISTRAR_NOMBRE:
			registrandoNombre = true;
			nombreIntroducido = "";
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		case AccionTransicion::IR_AL_MENU:
			partidaTerminada = false;
			enPartida = false;
			registrandoNombre = false;
			mensajeFinPartida.clear();
			Audio::stopMusica();
			Audio::playMusica("audio/INTRO.mp3", true);
			accionPendiente = AccionTransicion::NINGUNA;
			transicion.descubrir();
			break;

		default:
			break;
		}
	}

	if (pendienteMusicaTablero && !transicion.estaActiva())
	{
		pendienteMusicaTablero = false;
		Audio::playMusicaTablero();
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

	if (!partidaTerminada)
		tiempoPartida += 0.025;
	else
	{
		if (!musicaFinalSonando)
		{
			musicaFinalSonando = true;
			Audio::playMusicaFinal();
		}
		return;
	}

	bool estabaActiva = arena.estaActiva();
	if (arena.estaActiva()) arena.mueve(0.025);

	// Si la arena acaba de desactivarse este frame → resolver resultado
	if (arena.combateTerminado() && accionPendiente == AccionTransicion::NINGUNA && !mostrandoCartel)
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
		tablero.curarEnCasillasdePoder();
		comprobarFinPartida();
	}

	BandoVentaja ventajaActual = tablero.getBandoVentaja();
	for (int i = 0; i < FILAS; i++)
		for (int j = 0; j < COLS; j++) {
			Pieza* p = tablero.getPieza(Pos(i, j));
			if (p && p->estaAprisionada() && (numeroJugada - p->getTurnoAprisionamiento() >= 3))
				p->liberar();
		}
}

void Mundo::dibuja()
{
	if (!enPartida)
	{
		menu.dibuja();
		transicion.dibuja();
		return;
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glColor3ub(255, 255, 255);

	tablero.dibuja(cursor, turno);
	cursor.dibuja();   // borde amarillo
	cursor2.dibuja();  // borde morado
	arena.dibuja();
	dibujaPanelHechizos();

	if (!enPausa && !mostrandoCartel && !transicion.estaActiva())
		dibujaTimer();

	if (enPausa && !verControlesPausa) menu.dibujaPausa(opcionPausa);
	if (enPausa && verControlesPausa) menu.dibujaControlesPausa();

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

	if (partidaTerminada && !registrandoNombre)
	{
		extern float G_XMAX;
		extern float G_YMAX;

		const char* rutaFin = plantasGanaronPartida ? "imagenes/carteles/fin_juego_plantas.png" : "imagenes/carteles/fin_juego_zombies.png";

		auto texFin = ETSIDI::getTexture(rutaFin);
		if (texFin.id != 0)
		{
			glDisable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, texFin.id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
		else
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.0f, 0.0f, 0.0f, 0.85f);
			glBegin(GL_QUADS);
			glVertex3f(-G_XMAX, -G_YMAX, 0);
			glVertex3f(G_XMAX, -G_YMAX, 0);
			glVertex3f(G_XMAX, G_YMAX, 0);
			glVertex3f(-G_XMAX, G_YMAX, 0);
			glEnd();
			glDisable(GL_BLEND);
		}

		{
			int totalSeg = (int)tiempoPartida;
			int minutos = totalSeg / 60;
			int segundos = totalSeg % 60;
			std::string textoMin = (minutos < 10 ? "0" : "") + std::to_string(minutos);
			std::string textoSeg = (segundos < 10 ? "0" : "") + std::to_string(segundos);
			std::string buf = textoMin + "." + textoSeg;

			float bx = G_XMAX - 9.0f;
			float by = -G_YMAX + 1.0f;

			ETSIDI::setTextColor(1.0f, 0.82f, 0.0f);
			ETSIDI::setFont("fuentes/texto.ttf", 24);
			ETSIDI::printxy("TIEMPO", bx + 2.5f, by + 3.3f);

			ETSIDI::setTextColor(1.0f, 1.0f, 1.0f);
			ETSIDI::setFont("fuentes/auxiliar.ttf", 75);
			ETSIDI::printxy(buf.c_str(), bx + 0.2f, by + 0.3f);

			glColor3f(1.0f, 1.0f, 1.0f);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}

		ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
		ETSIDI::setFont("fuentes/texto.ttf", 28);
		ETSIDI::printxy("ESC   INICIO", -G_XMAX + 1.0f, -11.0f);
		ETSIDI::printxy("ENTER REGISTRAR PUNTUACION", -G_XMAX + 1.0f, -13.0f);
	}

	if (registrandoNombre)
	{
		extern float G_XMAX;
		extern float G_YMAX;

		const char* rutaRelleno = plantasGanaronPartida ? "imagenes/carteles/rellenar_nombre_plantas.png" : "imagenes/carteles/rellenar_nombre_zombies.png";

		auto texRelleno = ETSIDI::getTexture(rutaRelleno);
		if (texRelleno.id != 0)
		{
			glDisable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, texRelleno.id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

		ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
		ETSIDI::setFont("fuentes/texto.ttf", 50);
		ETSIDI::printxy("REGISTRAR PUNTUACION", -16.0f, 7.0f);

		{
			int totalSeg = (int)tiempoPartida;
			int minutos = totalSeg / 60;
			int segundos = totalSeg % 60;
			std::string textoMin = (minutos < 10 ? "0" : "") + std::to_string(minutos);
			std::string textoSeg = (segundos < 10 ? "0" : "") + std::to_string(segundos);
			std::string buf = textoMin + "." + textoSeg;
			float bx = G_XMAX - 9.0f;
			float by = -G_YMAX + 1.0f;
			ETSIDI::setTextColor(1.0f, 0.82f, 0.0f);
			ETSIDI::setFont("fuentes/texto.ttf", 24);
			ETSIDI::printxy("TIEMPO", bx + 2.5f, by + 3.3f);
			ETSIDI::setTextColor(1.0f, 1.0f, 1.0f);
			ETSIDI::setFont("fuentes/auxiliar.ttf", 75);
			ETSIDI::printxy(buf.c_str(), bx + 0.2f, by + 0.3f);
		}

		ETSIDI::setTextColor(0.6f, 0.9f, 1.0f);
		ETSIDI::setFont("fuentes/texto.ttf", 28);
		ETSIDI::printxy("Introduce tu nombre:", -8.0f, 3.5f);

		std::string mostrar = nombreIntroducido + "_";
		ETSIDI::setTextColor(1.0f, 1.0f, 1.0f);
		ETSIDI::setFont("fuentes/texto.ttf", 55);
		ETSIDI::printxy(mostrar.c_str(), -8.0f, -1.5f);

		ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
		ETSIDI::setFont("fuentes/texto.ttf", 22);
		ETSIDI::printxy("ENTER - Guardar    ESC - Cancelar", -11.0f, -6.0f);
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

extern float G_XMAX;
extern float G_YMAX;

void Mundo::clicRaton(int boton, int estado, int xPixel, int yPixel)
{
	if (transicion.estaActiva()) return;
	if (boton != GLUT_LEFT_BUTTON || estado != GLUT_DOWN) return;
	if (!enPartida || enPausa || partidaTerminada) return;
	if (arena.estaActiva()) return;        // en la arena el raton no se usa
	if (tablero.estaAnimando()) return;     // igual que con teclado: ignorar durante animacion

	int anchoVentana = glutGet(GLUT_WINDOW_WIDTH);
	int altoVentana = glutGet(GLUT_WINDOW_HEIGHT);
	if (anchoVentana <= 0 || altoVentana <= 0) return;

	// FreeGLUT da (xPixel,yPixel) con origen arriba-izquierda.
	// Lo pasamos a coordenadas de mundo [-G_XMAX,G_XMAX] x [-G_YMAX,G_YMAX]
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
	const char* nombres[7] = { "Teleport", "Heal", "Revive", "Imprison", "ShiftTime", "Exchange", "Transform" };
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