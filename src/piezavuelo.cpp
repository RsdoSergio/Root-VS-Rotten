#include "piezavuelo.h"

void PiezaVuelo::setMovimiento(int dir, bool estado)
{

    if (dir == DIR_ARRIBA) tecla_arriba = estado;
    if (dir == DIR_ABAJO)  tecla_abajo = estado;
    if (dir == DIR_IZQ)    tecla_izq = estado;
    if (dir == DIR_DCHA)   tecla_dcha = estado;

    //calcular último eje X 
    if (dir == DIR_IZQ || dir == DIR_DCHA)
    {
        if (estado)
        {
            // Nueva tecla pulsada en X pasa a ser la activa
            ultimo_eje_x = (dir == DIR_DCHA) ? +1 : -1;
        }
        else
        {
            // Tecla soltada en X , ver si la contraria sigue pulsada
            if (dir == DIR_DCHA && tecla_izq)  ultimo_eje_x = -1;
            else if (dir == DIR_IZQ && tecla_dcha) ultimo_eje_x = +1;
            else                                    ultimo_eje_x = 0;//si no hay nada pulsado
        }
    }

    //calcular último eje Y 
    if (dir == DIR_ARRIBA || dir == DIR_ABAJO)
    {
        if (estado)
        {
            ultimo_eje_y = (dir == DIR_ARRIBA) ? +1 : -1;// Nueva tecla pulsada en Y
        }

        else
        {
            // Tecla soltada en Y, ver si la contraria sigue pulsada
            if (dir == DIR_ARRIBA && tecla_abajo)  ultimo_eje_y = -1; // -1 hacia abajo
            else if (dir == DIR_ABAJO && tecla_arriba) ultimo_eje_y = +1;//+ hacia arriba
            else                                        ultimo_eje_y = 0;//nada pulsado
        }
    }
    if (dir == DIR_IZQ || dir == DIR_DCHA)    ultimo_eje_reciente = 0;
    if (dir == DIR_ARRIBA || dir == DIR_ABAJO) ultimo_eje_reciente = 1;
}

void PiezaVuelo::actualizarArena(double dt)
{
    double dirX = 0, dirY = 0;

    if (ultimo_eje_x != 0 && ultimo_eje_y != 0) {

        if (ultimo_eje_reciente == 0) dirX = ultimo_eje_x;
        else  dirY = ultimo_eje_y;
    }

    else
    {
        dirX = ultimo_eje_x;
        dirY = ultimo_eje_y;
    }

    double x = posArena.getX() + dirX * velocidad * dt;
    double y = posArena.getY() + dirY * velocidad * dt;

    posArena.setValores(x, y);
}



