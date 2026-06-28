#include "hechzoTeleport.h"
#include "tablero.h"
#include "piezas/pieza.h"
#include "piezas/mago.h"

bool hechizoTeleport::elegirOrigen(Tablero& tablero, Pieza* caster, Pos posOrigen)
{
	Pieza* pieza = tablero.getPieza(posOrigen);

	if (pieza == nullptr) return false;                    // casilla vacia
	if (pieza->getBando() != caster->getBando()) return false; // no es aliado

	origen = posOrigen;
	return true;
}

bool hechizoTeleport::ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo)
{
	if (!origen.esValida()) return false; // no se eligio origen todavia

	if (objetivo.fila == origen.fila && objetivo.col == origen.col)
		return false; // no se puede teletransportar a la misma casilla

	Pieza* pieza = tablero.getPieza(origen);
	if (pieza == nullptr) return false; // la pieza origen ya no esta

	if (tablero.getPieza(objetivo) != nullptr) return false; // el destino debe estar vacio

	tablero.colocarPiezaEnCasilla(origen, nullptr);
	tablero.colocarPiezaEnCasilla(objetivo, pieza);
	pieza->setCasilla(objetivo);

	Mago* mago = dynamic_cast<Mago*>(caster);
	if (mago != nullptr)
		mago->usarHechizo(Hechizo::TELEPORT);

	origen = Pos();
	return true;
}