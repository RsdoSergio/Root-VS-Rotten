#pragma once
#include "vector2d.h"
#include "pos.h"
#include<iostream>

enum class DirArena { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

constexpr int DIR_ARRIBA = 0;
constexpr int DIR_ABAJO = 1;
constexpr int DIR_IZQ = 2;
constexpr int DIR_DCHA = 3;

enum class TipoMovimiento { TIERRA, VUELO, TELETRANSPORTE };
constexpr float TAM_PIEZA = 0.9f;//Porvisional para las piezas
enum  Bando { planta, zombi };

class Pieza
{
    friend class Interaccion; // <-- aquí, fuera de cualquier sección

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
    double getIntervaloAtaque() const { return intervaloAtaque; }//nuevo para el cooldown de ataque

    Vector2D getPosArena() const { return posArena; }

    void setCasilla(Pos p) { casilla = p; }
    void recibirDanio(double d);
    void curar(double cantidad);

    void setPosArena(double x, double y) { posArena.setValores(x, y); }

    int getRadioMovimiento() const { return radioMovimiento; }

    virtual void dibujaTablero(float x, float y) const {};
    virtual std::string getNombre() const { return "Pieza"; }
    virtual void usarAtaqueSecundario() {};

    virtual TipoMovimiento getTipoMovimiento() const = 0; // Cada clase intermedia lo implementa

    virtual bool puedeDiagonal() const { return false; } //implementado para que las piezas de tierra se puedan mover en diagonales

    virtual void moverArena(DirArena dir, double xMin, double xMax, double yMin, double yMax) {}

    virtual ~Pieza() {} // Imprescindible en jerarquías
};