#include "freeglut.h"
#include "mundo.h"

Mundo mundo;

void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
void OnSpecialKey(int key, int x, int y);
void OnKeyboardUp(unsigned char key, int x, int y);
void OnSpecialKeyUp(int key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);

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
	glutInit(&argc, argv);
	glutInitWindowSize(1920, 1080);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("ROOT VS ROTTEN");
	// Ejecutar en pantalla completa
	glutFullScreen();

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

	glutDisplayFunc(OnDraw);
	glutReshapeFunc(OnReshape);
	glutTimerFunc(25, OnTimer, 0);
	glutKeyboardFunc(OnKeyboardDown);
	glutSpecialFunc(OnSpecialKey);
	glutKeyboardUpFunc(OnKeyboardUp);
	glutSpecialUpFunc(OnSpecialKeyUp);
	glutMouseFunc(OnMouseClick);

	mundo.inicializa();

	glutMainLoop();
	return 0;
}

void OnDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	mundo.dibuja();

	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	mundo.tecla(key);

	glutPostRedisplay();
}

void OnTimer(int value)
{
	mundo.mueve();
	glutPostRedisplay();
	glutTimerFunc(25, OnTimer, 0);
}

void OnSpecialKey(int key, int x, int y)
{
	mundo.teclaEspecial(key);
	glutPostRedisplay();
}

void OnKeyboardUp(unsigned char key, int x, int y)
{
	mundo.teclaLevantada(key);
	glutPostRedisplay();
}

void OnSpecialKeyUp(int key, int x, int y)
{
	mundo.teclaEspecialLevantada(key);
	glutPostRedisplay();
}

void OnMouseClick(int button, int state, int x, int y)
{
	//codigo de gestion de raton
	mundo.clicRaton(button, state, x, y);
	glutPostRedisplay();
}