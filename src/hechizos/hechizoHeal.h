#pragma once
#include "hechizo.h"

class hechizoHeal : public HechizoBase
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "HEAL"; }
	std::string getMensajeSeleccion() const override { return "Selecciona la pieza aliada a curar"; }
	std::string getMensajeExito() const override { return "El mago ha curado a un aliado"; }
};