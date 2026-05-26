#pragma once

constexpr double ARENA_ANCHO = 44.0;
constexpr double ARENA_ALTO = 26.0;
constexpr double SEMIANCHO = ARENA_ANCHO / 2.0;
constexpr double SEMIALTO = ARENA_ALTO / 2.0;

class arena
{
	bool activo = false;

	void dibujaFondo() const;
	void dibujaInterior() const;
	void dibujaMarco() const;

public:
	arena() {};

	void dibuja() const;
	void activa() { activo = true; }
	void desactiva() { activo = false; }
	bool estaActiva() const { return activo; }

};
