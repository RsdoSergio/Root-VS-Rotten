#pragma once

struct Vector2D
{
    double x{};
    double y{};

    Vector2D() {};
    Vector2D(double x, double y) : x(x), y(y) {}

    void setValores(double x, double y);
    double getX() const { return x; }
    double getY() const { return y; }
};