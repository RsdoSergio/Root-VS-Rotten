#pragma once
#include "casilla.h"
#include"pos.h"
#include<vector>
#include "listapieza.h"

constexpr int FILAS = 9;
constexpr int COLS = 9;
constexpr float TAM_CELDA = 2.8f;

class Tablero {
public:
    void inicializaTablero();
	void dibujaTablero(); //← solo esta, sin duplicados ni vector/pair
    void colocarPiezasIniciales(listapieza& lista);

	void dibujaTablero(Pos cursor); 
    void dibujaPiezas();
    void marcaCasillasValidas();
    
    Pieza* getPieza(Pos p) const;
    bool   estaOcupada(Pos p) const ;

    void gestionarEntrada(Pos cursor, int& turno);
    void cancelarSeleccion();

private:
    Casilla casillas[FILAS][COLS];
    Pos piezaSeleccionada;
    std::vector<Pos> casillasValidas;
    bool movimientoPendiente = false;            

    std::vector<Pos> movimientosValidos(Pos origen);
    bool moverPieza(Pos origen, Pos destino);            
};