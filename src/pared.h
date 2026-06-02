#pragma once
#include "vector2d.h"

class Pared
{
    Vector2D limite1_, limite2_;

public:
    void dibuja() const;
    Pared(Vector2D l1, Vector2D l2);

    Vector2D getLimite1() const { return limite1_; }
    Vector2D getLimite2() const { return limite2_; }
};