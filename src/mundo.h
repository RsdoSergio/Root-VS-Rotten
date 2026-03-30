#pragma once

class Mundo
{
	double x_ojo;
	double y_ojo;
	double z_ojo;
public:
	void rotar_ojo();
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};