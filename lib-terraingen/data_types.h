#pragma once
#include <cmath>
#include <valarray>
#include <vector>

typedef std::vector<std::valarray<double>> Heightmap;

template<typename T>
struct Vector2{
    T x;
    T y;

    Vector2(T x, T y) : x(x), y(y)
    {
    }

    bool operator==(const Vector2 &other) const{
        return x == other.x && y == other.y;
    }

    double magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2<T> normalised() const {
        double mag = magnitude();
        if (mag == 0) return {0, 0};
        return {x / mag, y / mag};
    }

    Vector2<T> operator+(const Vector2<T> &other) const {
        return {x + other.x, y + other.y};
    }
};

template<typename T>
Vector2<T> lerp(Vector2<T> a, Vector2<T> b, double t)
{
    return {std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t)};
}