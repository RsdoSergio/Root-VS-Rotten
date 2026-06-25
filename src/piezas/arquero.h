#pragma once
#include "piezaTierra.h"
#include"proyectilacelerado.h"

// Pieza con ataque a distancia, vida media
class Arquero : public PiezaTierra {
	double velocidadProyectil;

	static constexpr double VEL_MIN = 1.0;
	static constexpr double VEL_MAX = 15.0;
	static constexpr double DURACION_PROYECTIL = 3.0;
public:
	Arquero(Bando b, Pos pos)
		: PiezaTierra(
			8.0,   // PV bajo
			5.0,   // Daño medio
			4.5,   // Vel. movimiento media
			0.6,   // Enfriamiento bajo
			2, //rad de mov
			b, pos),
		velocidadProyectil(8.0) // El proyectil viaja más rápido que la propia pieza
	{
		rutaSpriteAtaque = bando == Bando::planta
			? "imagenes/sprites_plantas/guisantralladora_ataque.png"
			: "imagenes/sprites_zombies/zombie_pertiga_ataque.png";

		rutaSprite = bando == Bando::planta
			? "imagenes/sprites_plantas/guisantralladora.png"
			: "imagenes/sprites_zombies/zombie_pertiga.png";
		numFramesAtaque = 4;
	}

	std::string getNombre() const override {
		return bando == Bando::planta ? "Guisantralladora" : "Pertigador";
	}
	void usarAtaqueSecundario() override {};
	bool puedeDiagonal() const override { return true; };
	Proyectil* crearProyectil(int dirX, int dirY) override;

	std::string getRutaProyectil() const override {
		return bando == Bando::planta ? "imagenes/proyectiles/proyectil_gisantralladora.png" : "imagenes/proyectiles/proyectil_pertiga.png";
	}
};