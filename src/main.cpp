#include "freeglut.h"
#include "mundo.h"

Mundo mundo; //centralizamos la información en este objeto

void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla
void OnSpecialKey(int key, int x, int y);//flechas del teclado

// Variables globales accesibles desde cualquier .cpp
float G_XMAX = 26.67f;  // valor por defecto 16:9
float G_YMAX = 15.0f;

void OnReshape(int w, int h)
{
	if (h == 0) h = 1;
	float aspect = (float)w / h;
	const float orthoScale = 15.0f;

	G_YMAX = orthoScale;
	G_XMAX = orthoScale * aspect;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-G_XMAX, G_XMAX, -G_YMAX, G_YMAX, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(1920, 1080);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("ROOT VS ROTTEN");
	// Ejecutar en pantalla completa
	glutFullScreen();

	// Configurar vista 2D sin perspectiva (ortonomal)
	// Desactivar iluminación para dibujo 2D plano
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);
	// Proyección ortográfica inicial
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	{
		// usar tamaño real de la ventana (que está en full screen)
		float w = (float)glutGet(GLUT_WINDOW_WIDTH);
		float h = (float)glutGet(GLUT_WINDOW_HEIGHT);
		if (h == 0.0f) h = 1.0f;
		const float aspect = w / h;
		const float orthoScale = 15.0f;
		if (aspect >= 1.0f)
			glOrtho(-orthoScale * aspect, orthoScale * aspect, -orthoScale, orthoScale, -1.0, 1.0);
		else
			glOrtho(-orthoScale, orthoScale, -orthoScale / aspect, orthoScale / aspect, -1.0, 1.0);
	}

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutReshapeFunc(OnReshape);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutSpecialFunc(OnSpecialKey);    //registrar callback de flechas

	//inicialización de objetos de la simulación
	mundo.inicializa();

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();
	return 0;
}

void OnDraw(void)
{
	//Borrado de la pantalla y reseteo de la matriz de transformacion
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	mundo.dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//codigo de gestion de teclado
	mundo.tecla(key);

	//indicamos que se vuelva a dibujar la pantalla, para que se vean los cambios
	glutPostRedisplay();
}

void OnTimer(int value)
{
	//código de animacion
	mundo.mueve();

	//no borrar estas lineas
	//indicamos que se vuelva a dibujar la pantalla, para que se vean los cambios
	glutPostRedisplay();
	//recurivamente, le decimos que dentro de 25ms vuelva a llamar a esta funcion, para que se siga animando
	glutTimerFunc(25, OnTimer, 0);
}

void OnSpecialKey(int key, int x, int y)
{
	mundo.teclaEspecial(key);
	glutPostRedisplay();
}