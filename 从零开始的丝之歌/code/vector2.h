#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

class Vector2
{
public:
    double x = 0, y = 0;
public:
    Vector2() = default;
    Vector2(double x, double y) : x(x), y(y) {};

    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
    Vector2 operator+= (const Vector2& other) { x += other.x; y += other.y; return *this; }
    Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
    Vector2 operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
    Vector2 operator*(double scalar) const { return Vector2(x * scalar, y * scalar); }
    Vector2 operator*=(double scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2 operator/(double scalar) const { return Vector2(x / scalar, y / scalar); }
    Vector2 operator/=(double scalar) { x /= scalar; y /= scalar; return *this; }
    double operator*(const Vector2& other) const { return x * other.x + y * other.y; }
    double operator/(const Vector2& other) const { return x / other.x + y / other.y; }

    double length() const { return sqrt(x * x + y * y); }
    Vector2 normalize() const { if (length() == 0) return Vector2(0, 0); return *this / length(); }
    bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
    bool operator>(const Vector2& other) const { return x > other.x && y > other.y; }
    bool operator<(const Vector2& other) const { return x < other.x && y < other.y; }
    bool operator>=(const Vector2& other) const { return x >= other.x && y >= other.y; }
    bool operator<=(const Vector2& other) const { return x <= other.x && y <= other.y; }
    bool approach() const { return length() < 0.00001; }
    bool approach_x() const { return x < 0.00001 && x > -0.00001; }
    bool approach_y() const { return y < 0.00001 && y > -0.00001; }
private:

};

#endif // VECTOR2_H
