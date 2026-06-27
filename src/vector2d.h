#pragma once

struct Vector2D
{
	double x{};
	double y{};
public:

	Vector2D() : x(0.0), y(0.0) {}
	Vector2D(double x, double y) : x(x), y(y) {}

	void setValores(double x, double y);
	double getX() const { return x; }
	double getY() const { return y; }

	Vector2D operator+(const Vector2D& v) const { return { x + v.x, y + v.y }; }
	Vector2D operator-(const Vector2D& v) const { return { x - v.x, y - v.y }; }
	Vector2D operator*(double f) const { return { x * f,   y * f }; }
};