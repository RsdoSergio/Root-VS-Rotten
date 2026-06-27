#include "puntuaciones.h"
#include <fstream>
#include <algorithm>

const char* Puntuaciones::RUTA_FICHERO = "puntuaciones.txt";

std::vector<EntradaPuntuacion> Puntuaciones::cargar()
{
	std::vector<EntradaPuntuacion> lista;
	std::ifstream f(RUTA_FICHERO);
	if (!f.is_open())
		return lista;

	std::string nombre;
	int seg;
	while (f >> seg && std::getline(f >> std::ws, nombre))
		lista.push_back({ nombre, seg });

	return lista;
}

void Puntuaciones::guardar(const std::string& nombre, int segundos)
{
	auto lista = cargar();
	lista.push_back({ nombre, segundos });

	std::sort(lista.begin(), lista.end(), [](const EntradaPuntuacion& a, const EntradaPuntuacion& b) { return a.segundos < b.segundos; });

	if (lista.size() > 10) lista.resize(10);

	std::ofstream f(RUTA_FICHERO);
	for (auto& e : lista)
		f << e.segundos << " " << e.nombre << "\n";
}

std::string Puntuaciones::formatearTiempo(int segundos)
{
	int min = segundos / 60;
	int seg = segundos % 60;
	std::string m = (min < 10 ? "0" : "") + std::to_string(min);
	std::string s = (seg < 10 ? "0" : "") + std::to_string(seg);
	return m + " . " + s;
}