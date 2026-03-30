#include "mundo.h"
#include "freeglut.h"
#include <cmath>
void Mundo::rotar_ojo()
{
	auto dist = sqrt(x_ojo * x_ojo + z_ojo * z_ojo);
	auto ang = atan2(z_ojo, x_ojo);
	ang += 0.05;
	x_ojo = dist * cos(ang);
	z_ojo = dist * sin(ang);
}
void Mundo::inicializa() {
	x_ojo = 0;
	y_ojo = 10;
	z_ojo = 20;
};
//Metodo se gestiona la pulsacion de teclas, y como afecta a la simulacion
void Mundo::tecla(unsigned char key)
{
	
}

//Metodo que gestiona el comportamiento de la simulacion, 
// y como evoluciona con el tiempo
void Mundo::mueve()
{
	
	rotar_ojo(); //para que el ojo rote lentamente. LO BORRAREMOS 

}

//Metodo que gestiona el dibujo de la simulacion
void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		0.0, 0, 0.0,				// hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);				// definimos hacia arriba (eje Y)    

	//aqui es donde hay que poner el codigo de dibujo
	
	//dibujo del suelo inicial que BORRAREMOS
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3ub(255, 0, 0);
	glVertex3d(-5.0, 0, -5.0);
	glVertex3d(-5.0, 0, 5.0);
	glColor3ub(255, 255, 0);
	glVertex3d(5.0, 0, 5.0);
	glVertex3d(5.0, 0, -5.0);
	glEnd();
	glEnable(GL_LIGHTING);
}
