#include "hechizoRevive.h"
#include "tablero.h"
#include "pieza.h"
#include <cmath>

std::vector<Pieza*>& hechizoRevive::getCandidatas(Tablero& tablero, Pieza* caster)
{
    return (caster->getBando() == Bando::planta)
        ? tablero.getEliminadasPlanta()
        : tablero.getEliminadasZombi();
}

bool hechizoRevive::elegirPieza(Tablero& tablero, Pieza* caster, int indice)
{
    std::vector<Pieza*>& lista = getCandidatas(tablero, caster);
    if (indice < 0 || indice >= (int)lista.size()) return false;

    piezaElegida = lista[indice];
    return true;
}

bool hechizoRevive::ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo)
{
    if (piezaElegida == nullptr) return false; // no se eligio pieza todavia

    // La casilla destino debe estar vacia
    if (tablero.getPieza(objetivo) != nullptr) return false;

    // Debe ser adyacente al mago
    Pos posMago = caster->getCasilla();
    int df = std::abs(objetivo.fila - posMago.fila);
    int dc = std::abs(objetivo.col - posMago.col);
    if (df > 1 || dc > 1 || (df == 0 && dc == 0)) return false;

    std::vector<Pieza*>& lista = getCandidatas(tablero, caster);
    for (size_t i = 0; i < lista.size(); i++) {
        if (lista[i] == piezaElegida) {
            lista.erase(lista.begin() + i);
            break;
        }
    }

    piezaElegida->curar(piezaElegida->getVidaMax());
    piezaElegida->setCasilla(objetivo);
    tablero.colocarPiezaEnCasilla(objetivo, piezaElegida);

    piezaElegida = nullptr; 
    return true;
}