#pragma once
#include "vector2d.h"
#include "pos.h"
#include<iostream>


enum class DirArena { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

enum class TipoMovimiento { TIERRA, VUELO, TELETRANSPORTE };
constexpr float TAM_PIEZA = 0.9f;//Porvisional para las piezas
enum  Bando { planta, zombi };

class Pieza {
protected:
    double   vida;
    double   vidaMax;
    double   fuerza;
    double   velocidad;
    double   intervaloAtaque;
    int      radioMovimiento;
    Bando    bando;
    Pos      casilla;
    Vector2D posArena;

public:
    Pieza(double v, double f, double vel, double intervalo, int radio, Bando b, Pos pos);

    double getVida()      const { return vida; }
    double getVidaMax()   const { return vidaMax; }
    double getFuerza()    const { return fuerza; }
    double getVelocidad() const { return velocidad; }
    Bando  getBando()     const { return bando; }
    Pos    getCasilla()   const { return casilla; }
    bool   estaViva()     const { return vida > 0; }
    //para actualizar pos en arena
    Vector2D getPosArena() const { return posArena; }
    void     setPosArena(double x, double y) { posArena.setValores(x, y); }

    void setCasilla(Pos p) { casilla = p; }
    void recibirDanio(double d);
    void curar(double cantidad);

    int getRadioMovimiento() const { return radioMovimiento; }
    
    virtual void dibujaTablero(float x, float y) const {};
    virtual std::string getNombre() const { return "Pieza"; }
    virtual void usarAtaqueSecundario() {};

    virtual TipoMovimiento getTipoMovimiento() const = 0; // Cada clase intermedia lo implementa
    
    //Para mov en arena. recibe los limites de la caja dearena
    virtual void moverArena(DirArena dir, double xMin, double xMax, double yMin, double yMax) {}

    virtual ~Pieza() {} // Imprescindible en jerarquías
};