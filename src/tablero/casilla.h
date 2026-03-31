#pragma once

class Casilla {
public:
	enum TipoCasilla {
		NORMAL,
		POWER_LIGHT,   // casillas especiales de Root (plantas)
		POWER_DARK     // casillas especiales de Rotten (zombies)
	};

	TipoCasilla tipo;
	bool ocupada;
};