#pragma once
#include "vector2d.h"
#include "pos.h"
#include "proyectil.h"
#include<iostream>
#include<vector>

enum class BandoVentaja { PLANTA, ZOMBI };

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
	

	bool   atacandoActivo = false;
	double tiempoAtaqueRestante = 0.0;
	

	bool aprisionada = false;
	int turnoAprisionamiento = -1;

	double bonusVida = 0.0;
	double bonusFuerza = 0.0;
	double bonusVelocidad = 0.0;

	//para sprites
	std::string rutaSpriteAtaque = "";
	std::string rutaSprite = "";
	int numFramesNormal = 6;
	int numFramesAtaque = 4;

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
	double getTiempoAnimAtaque() const { return tiempoAnimAtaque; }

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
	virtual void dibujaTableroGrande(float x, float y, float tam) const; //para cuando se seleccione
	virtual void dibujaArena(float x, float y) const;
	virtual std::string getNombre() const { return "Pieza"; }
	virtual void usarAtaqueSecundario() {};

	virtual std::string getRutaSprite() const { return ""; }

	virtual TipoMovimiento getTipoMovimiento() const = 0; // Cada clase intermedia lo implementa

	virtual bool puedeDiagonal() const { return false; } //implementado para que las piezas de tierra se puedan mover en diagonales
	virtual bool esMelee() const { return false; }
	virtual double getVelocidadProyectil() const { return 12.0; } // valor por defecto, igual que VEL_PROYECTIL de arena
	virtual void moverArena(DirArena dir, double xMin, double xMax, double yMin, double yMax) {}

	virtual void actualizarArena(double dt) {}
	virtual void setMovimiento(int dir, bool estado) {}

	virtual void activarExplosion() {}
	virtual double consumirDanoExplosion() { return 0.0; }

	virtual double getRadioExplosionMax() const { return 0.0; }

	virtual int getFrame(DirMovimiento dir, AccionPieza accion) const;

	bool estaAtacando() const { return atacandoActivo; }
	void iniciarAtaque() { atacandoActivo = true; tiempoAtaqueRestante = tiempoAnimAtaque; }

	virtual void actualizarEfectos(double dt) {}
	virtual bool bloqueaMovimientoAlAtacar() const { return true; }
	virtual Proyectil* crearProyectil(int dirX, int dirY);


	void actualizarAtaque(double dt);

	virtual std::vector<Proyectil*> recogerProyectiles() { return {}; }
	virtual bool tieneProyectilesPendientes() const { return false; }
	virtual void iniciarRafaga(int dirX, int dirY) {}
	virtual bool tieneRafaga() const { return false; }

	bool estaAprisionada() const { return aprisionada; }
	void aprisionar(int turnoActual) { aprisionada = true; turnoAprisionamiento = turnoActual; }
	void liberar() { aprisionada = false; turnoAprisionamiento = -1; }
	int getTurnoAprisionamiento() const { return turnoAprisionamiento; }
	void setFuerza(double f) { fuerza = f; }
	void setVelocidad(double v) { velocidad = v; }
	void setVidaMax(double v) { vidaMax = v; }
	
	virtual ~Pieza() {}
};