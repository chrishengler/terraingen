#pragma once
#include <cmath>
#include <memory>
#include <valarray>
#include <vector>

typedef std::vector<std::valarray<double>> Heightmap;

inline std::unique_ptr<std::vector<float>> flattenHeightmap(const Heightmap& hm) {
    std::vector<float> pixels;
    size_t rows = hm.size();
    size_t cols = hm.empty() ? 0 : hm[0].size();
    pixels.reserve(rows * cols);
    for (const auto& row : hm)
      for (double v : row) {
        pixels.push_back(static_cast<float>(v));
      }
    return std::make_unique<std::vector<float>>(pixels);
}

inline std::vector<unsigned int> flatten_heightmap_uint(const Heightmap& hm, const unsigned int max){
    std::vector<unsigned int> pixels;
    size_t rows = hm.size();
    size_t cols = hm.empty() ? 0 : hm[0].size();
    pixels.reserve(rows * cols);
    for (const auto& row : hm)
      for (double v : row) {
        pixels.push_back((unsigned int)(std::clamp((unsigned int)(v*max), (unsigned int)0, max)));
      }
    return pixels;
}

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

using Vec2i = Vector2<int>;

inline Vec2i make_vec2i(int x, int y)
{
    return Vec2i(x, y);
}


template<typename T>
Vector2<T> lerp(Vector2<T> a, Vector2<T> b, double t)
{
    return {std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t)};
}

inline Vector2<int> getDimensions(const Heightmap &hm){
    if(hm.size() == 0)
    {
        return Vector2<int>(0,0);
    }
    return Vector2<int>((int)hm.size(), (int)hm[0].size());
}
