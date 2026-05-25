#pragma once
#include "vector2d.h"
#include "pos.h"
#include<iostream>


constexpr float TAM_PIEZA = 0.9f;//Porvisional para las piezas
enum  Bando { planta, zombi };

class Pieza {
protected:
    double   vida;
    double   vidaMax;
    double   fuerza;
    double   velocidad;
    double   intervaloAtaque;
    Bando    bando;
    Pos      casilla;
    Vector2D posArena;

public:
    Pieza(double vida, double fuerza, double vel, double intervalo, Bando b, Pos pos);

    double getVida()      const { return vida; }
    double getVidaMax()   const { return vidaMax; }
    double getFuerza()    const { return fuerza; }
    double getVelocidad() const { return velocidad; }
    Bando  getBando()     const { return bando; }
    Pos    getCasilla()   const { return casilla; }
    bool   estaViva()     const { return vida > 0; }

    void setCasilla(Pos p) { casilla = p; }
    void recibirDanio(double d);
    void curar(double cantidad);
    
    virtual void dibujaTablero(float x, float y) const {};
    virtual std::string getNombre() const { return "Pieza"; }
    virtual void usarAtaqueSecundario() {};

    virtual ~Pieza() {} // Imprescindible en jerarquías
};