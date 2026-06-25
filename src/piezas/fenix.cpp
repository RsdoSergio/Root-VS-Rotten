#include "fenix.h"
#include "gestorTexturas.h"
#include "freeglut.h"






void Fenix::dibujaArena(float x, float y) const
{
    PiezaVuelo::dibujaArena(x, y);

    if (!explosionActiva) return;

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int numCirculos = 6;
    for (int i = 0; i < numCirculos; i++)
    {
        double t = (double)i / (numCirculos - 1); // 0.0 a 1.0
        double r = radioExplosionActual * (i + 1.0) / numCirculos;

        // azul -> amarillo -> naranja
        float red = (float)t;
        float green = (float)(t < 0.5 ? t * 2.0 : 1.0 - (t - 0.5));
        float blue = (float)(1.0 - t);
        float alpha = 1.0f - (float)(tiempoExplosion / duracionExplosion) * 0.5f;

        glColor4f(red, green, blue, alpha);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < 48; j++)
        {
            double ang = 2.0 * 3.14159265 * j / 48;
            // temblor: pequeño offset aleatorio por segmento
            double temblor = (rand() % 10 - 5) * 0.04;
            glVertex2d(x + (r + temblor) * cos(ang), y + (r + temblor) * sin(ang));
        }
        glEnd();
    }

    glPopAttrib();
}


void Fenix::actualizarEfectos(double dt)
{
    if (!explosionActiva) return;
    tiempoExplosion += dt;
    radioExplosionActual = radioExplosionMax * (tiempoExplosion / duracionExplosion);
    
    if (tiempoExplosion >= duracionExplosion)
    {
        explosionActiva = false;
        radioExplosionActual = 0.0;
        danoExplosionPendiente = true;
    }
}

void Fenix::actualizarArena(double dt)
{
    PiezaVuelo::actualizarArena(dt);
}

double Fenix::consumirDanoExplosion()
{

    if (!danoExplosionPendiente) return 0.0;
    danoExplosionPendiente = false;
    return fuerza;
    
}

void Fenix::activarExplosion()
{
    explosionActiva = true;
    radioExplosionActual = 0.0;
    tiempoExplosion = 0.0;
    
}