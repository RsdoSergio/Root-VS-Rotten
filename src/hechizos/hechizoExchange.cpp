#include "hechizoExchange.h"
#include "tablero.h"
#include "piezas/pieza.h"
#include "piezas/mago.h"

bool hechizoExchange::elegirOrigen(Tablero& tablero, Pieza* caster, Pos posOrigen)
{
	Pieza* pieza = tablero.getPieza(posOrigen);

	if (pieza == nullptr) return false;                    // casilla vacia
	if (pieza->getBando() != caster->getBando()) return false; // no es aliado

	origen = posOrigen;
	return true;
}

bool hechizoExchange::ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo)
{
	if (!origen.esValida()) return false; // no se eligio origen todavia

	if (objetivo.fila == origen.fila && objetivo.col == origen.col)
		return false; // no se puede intercambiar una pieza con si misma

	Pieza* piezaA = tablero.getPieza(origen);
	Pieza* piezaB = tablero.getPieza(objetivo);

	if (piezaA == nullptr) return false; // la pieza origen ya no esta
	if (piezaB == nullptr) return false; // la casilla destino debe tener una pieza
	if (piezaB->getBando() != caster->getBando()) return false; // destino debe ser aliado

	tablero.colocarPiezaEnCasilla(origen, piezaB);
	tablero.colocarPiezaEnCasilla(objetivo, piezaA);
	piezaA->setCasilla(objetivo);
	piezaB->setCasilla(origen);


	Mago* mago = dynamic_cast<Mago*>(caster);
	if (mago != nullptr)
		mago->usarHechizo(Hechizo::EXCHANGE);

	origen = Pos();
	return true;
}