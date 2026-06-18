#pragma once
#include<string>
#include"pieza.h"
void precargarTexturas();

void dibujarSprite(const std::string& ruta, float x, float y, float tam,DirMovimiento dir, int totalFrames);
    