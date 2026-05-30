#pragma once
#include "vector2d.h"

class Pared
{
    Vector2D limite1_, limite2_;

public:
    void dibuja() const;
    Pared(Vector2D l1, Vector2D l2);
};