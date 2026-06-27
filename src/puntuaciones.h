#pragma once
#include <string>
#include <vector>

struct EntradaPuntuacion {
	std::string nombre;
	int segundos;
};

class Puntuaciones {
	static const char* RUTA_FICHERO;

public:
	static std::vector<EntradaPuntuacion> cargar();
	static void guardar(const std::string& nombre, int segundos);
	static std::string formatearTiempo(int segundos);
};