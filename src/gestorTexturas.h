#pragma once
#include<string>
#include"piezas/pieza.h"
void precargarTexturas();

void dibujarSprite(const std::string& ruta, float x, float y, float tam, int frame, int totalFrames);
