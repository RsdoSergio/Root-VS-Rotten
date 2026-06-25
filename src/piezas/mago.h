#pragma once
#include "piezaTeletransporte.h"
#include <array>

enum class Hechizo {
	TELEPORT,
	HEAL,
	REVIVE,
	IMPRISON,
	SHIFT_TIME,
	EXCHANGE,
	TRANSFORM
};

class Mago : public PiezaTeletransporte {
	double velocidadProyectil;
	std::array<bool, 7> hechizosUsados = { false };

	bool transformado = false;
	double vidaOriginal = 0.0;
	double vidaMaxOriginal = 0.0;
	double fuerzaOriginal = 0.0;
	double velocidadOriginal = 0.0;

public:
	Mago(Bando b, Pos pos)
		: PiezaTeletransporte(
			16.0,  // PV medio
			7.0,   // Daño medio
			4.0,   // Vel. movimiento media
			0.8,   // Enfriamiento medio
			-1,//rad de mov
			b, pos),
		velocidadProyectil(6.0)

	{
		rutaSprite = bando == Bando::planta
			? "imagenes/sprites_plantas/girasol_primitivo.png"
			: "imagenes/sprites_zombies/zombie_doctor.png";

		rutaSpriteAtaque = bando == Bando::planta
			? "imagenes/sprites_plantas/girasol_primitivo_ataque.png"
			: "imagenes/sprites_zombies/zombie_doctor_ataque.png";

		numFramesAtaque = 4;
	}

	double getVelocidadProyectil() const override { return velocidadProyectil; }

	bool puedeUsarHechizo(Hechizo h) const {
		return !hechizosUsados[static_cast<int>(h)];
	}
	void usarHechizo(Hechizo h) {
		hechizosUsados[static_cast<int>(h)] = true;
	}

	bool estaTransformado() const { return transformado; }

	void transformar() {
		if (transformado) return; // evita transformar dos veces sin revertir
		transformado = true;
		vidaOriginal = getVida();
		vidaMaxOriginal = getVidaMax();
		fuerzaOriginal = getFuerza();
		velocidadOriginal = getVelocidad();
		setVidaMax(vidaMaxOriginal * 1.5);
		curar(getVidaMax()); // sube tambien la vida actual al nuevo maximo
		setFuerza(fuerzaOriginal * 1.5);
		setVelocidad(velocidadOriginal * 1.5);
	}

	void revertirTransformacion() {
		if (!transformado) return;
		transformado = false;
		setVidaMax(vidaMaxOriginal);
		if (getVida() > vidaMaxOriginal) curar(vidaMaxOriginal - getVida()); // clamp si hiciera falta
		setFuerza(fuerzaOriginal);
		setVelocidad(velocidadOriginal);
	}

	std::string getNombre() const override {
		return bando == Bando::planta ? "Girasol Primitivo" : "Doctor Zombie";
	}
	void usarAtaqueSecundario() override {};

	std::string getRutaProyectil() const override {
		return bando == Bando::planta ? "imagenes/proyectiles/proyectil_girasol.png" : "imagenes/proyectiles/proyectil_doctor.png";
	}
};