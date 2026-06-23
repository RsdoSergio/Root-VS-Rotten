#pragma once

class Transicion
{
public:
	void cubrir();
	void descubrir();

	void actualiza(double dt);
	void dibuja() const;

	bool estaCubierta() const { return cubierta; }
	bool estaActiva()   const { return activa; }

private:
	bool  activa = false;
	bool  cubierta = false;
	bool  cubriendo = false;

	float progreso = 0.0f;
};