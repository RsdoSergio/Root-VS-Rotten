#pragma once

struct Vector2D
{
    double x{};
    double y{};

public:
	
	Vector2D() : x(0.0), y(0.0) {}//constructor por defecto
	Vector2D(double x, double y) : x(x), y(y) {}

	void setValores(double x, double y);
	double getX() const { return x; } 
	double getY() const { return y; } 

	//sobrecarga de operadores para las ecuaciones de movimiento
	//inspirados en lo hecho en el laboratorio de informatica
	Vector2D operator+(const Vector2D& v) const { return { x + v.x, y + v.y }; }
	Vector2D operator-(const Vector2D& v) const { return { x - v.x, y - v.y }; }
	Vector2D operator*(double f) const { return { x * f,   y * f }; }

};

    void setValores(double x, double y);
    double getX() const { return x; }
    double getY() const { return y; }
};