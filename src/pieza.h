#pragma once
#include "vector2d.h"
#include "pos.h"
#include<iostream>

enum class DirArena { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

constexpr int DIR_ARRIBA = 0;
constexpr int DIR_ABAJO = 1;
constexpr int DIR_IZQ = 2;
constexpr int DIR_DCHA = 3;

enum class DirMovimiento { IDLE, NORTE, SUR, ESTE, OESTE };
enum class AccionPieza { IDLE, MOVERSE, ATACAR };

enum class TipoMovimiento { TIERRA, VUELO, TELETRANSPORTE };
constexpr float TAM_PIEZA = 0.9f;//Porvisional para las piezas
enum  Bando { planta, zombi };

class Pieza
{
    friend class Interaccion; 
    

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
    DirMovimiento dirActual = DirMovimiento::IDLE;
    DirMovimiento ultimaDir = DirMovimiento::ESTE;
    int ultimo_eje_x = 0;  // -1 izq, 0 nada, +1 dcha
    int ultimo_eje_y = 0;  // -1 abajo, 0 nada, +1 arriba
    int ultimo_eje_reciente = 0;
    double radioGolpe = 1.5;
    double tiempoAnimAtaque = 0.3;
    AccionPieza accionActual = AccionPieza::IDLE;
    //para poder ajustar los tamaños de piezas a gusto
    



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

    DirMovimiento getUltimaDir() const { return ultimaDir; } //

    int getUltimoEjeX() const { return ultimo_eje_x; }
    int getUltimoEjeY() const { return ultimo_eje_y; }
    int getUltimoEjeReciente() const { return ultimo_eje_reciente; }
    int getRadioMovimiento() const { return radioMovimiento; }

    void setCasilla(Pos p) { casilla = p; }
    void recibirDanio(double d);
    void curar(double cantidad);

    void setPosArena(double x, double y) { posArena.setValores(x, y); }

    
    AccionPieza getAccion() const { return accionActual; }
    DirMovimiento getDireccion() const { return dirActual; }//usado para obtener en que direccion se esta moviendo la pieza en ese momento
                                                            //luego usarlo para los sprites
    void setDireccion(DirMovimiento d);
    void setAccion(AccionPieza a) { accionActual = a; }

    void resetEjes();
    
    //puesto para resetear el movimiento al iniciar el combate
    

    virtual void dibujaTablero(float x, float y) const;
    virtual void dibujaArena(float x, float y) const;
    virtual std::string getNombre() const { return "Pieza"; }
    virtual void usarAtaqueSecundario() {};

    virtual std::string getRutaSprite() const { return ""; }

    virtual TipoMovimiento getTipoMovimiento() const = 0; // Cada clase intermedia lo implementa

    virtual bool puedeDiagonal() const { return false; } //implementado para que las piezas de tierra se puedan mover en diagonales
    virtual bool esMelee() const { return false; }
    virtual double getVelocidadProyectil() const { return 12.0; } // valor por defecto, igual que VEL_PROYECTIL de arena
    virtual void moverArena(DirArena dir, double xMin, double xMax, double yMin, double yMax) {}

    virtual int getFrame(DirMovimiento dir, AccionPieza accion) const;

    virtual ~Pieza() {} 
};