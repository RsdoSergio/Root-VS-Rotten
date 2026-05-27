#include "menu.h"
#include "freeglut.h"

void Menu::dibuja() const
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-25.0f, -15.0f);
	glVertex2f(25.0f, -15.0f);
	glVertex2f(25.0f, 15.0f);
	glVertex2f(-25.0f, 15.0f);
	glEnd();

	ETSIDI::setTextColor(255, 255, 255);
	ETSIDI::setFont("fuentes/Minecraft.ttf", 72);
	ETSIDI::printxy("ROOT VS ROTTEN", -17, 7);

	ETSIDI::setTextColor(255, 255, 255);
	ETSIDI::setFont("fuentes/Minecraft.ttf", 32);
	ETSIDI::printxy("Un juego de estrategia", -9, 4.5);

	if (opcionSeleccionada == EstadoMenu::OPCION_0)  //opcion jugar
	{
		ETSIDI::setTextColor(0.10f, 1.0f, 0.10f);
		ETSIDI::setFont("fuentes/Minecraft.ttf", 52);
		ETSIDI::printxy("> JUGAR <", -6.5, -4);
	}
	else
	{
		ETSIDI::setTextColor(0.65f, 0.65f, 0.65f);
		ETSIDI::setFont("fuentes/Minecraft.ttf", 48);
		ETSIDI::printxy("JUGAR", -4.5, -4);
	}

	if (opcionSeleccionada == EstadoMenu::OPCION_1) //opcion salir
	{
		ETSIDI::setTextColor(1.0f, 0.10f, 0.10f);
		ETSIDI::setFont("fuentes/Minecraft.ttf", 52);
		ETSIDI::printxy("> SALIR <", -6, -8);
	}
	else
	{
		ETSIDI::setTextColor(0.65f, 0.65f, 0.65f);
		ETSIDI::setFont("fuentes/Minecraft.ttf", 48);
		ETSIDI::printxy("SALIR", -4, -8);
	}

	ETSIDI::setTextColor(0.5f, 0.5f, 0.5f);
	ETSIDI::setFont("fuentes/Minecraft.ttf", 24);
	ETSIDI::printxy("W / S para moverte   |   ENTER para confirmar", -14, -13);

	glColor3ub(255, 255, 255);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Menu::tecla(unsigned char key)
{
	if (key == 'w' || key == 'W')
		opcionSeleccionada = EstadoMenu::OPCION_0;

	if (key == 's' || key == 'S')
		opcionSeleccionada = EstadoMenu::OPCION_1;

	if (key == 13) //enter en ASCII
	{
		if (opcionSeleccionada == EstadoMenu::OPCION_0)
			confirmadoJugar = true;
		else
			exit(0);
	}
}