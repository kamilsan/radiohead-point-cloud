#pragma once

#include <cmath>
#include <iostream>

struct Vector2
{
  Vector2(): x(0), y(0) {}
  Vector2(float x, float y): x(x), y(y) {}

  inline float length() const { return std::sqrt(x*x + y*y); };
  inline float lengthSq() const { return x*x + y*y; };
  inline Vector2 normalize() const;
  inline float dot(const Vector2& other) const { return x*other.x + y*other.y; };

  inline Vector2 operator+(const Vector2& other) const;
  inline Vector2& operator+=(const Vector2& other);
  inline Vector2 operator-(const Vector2& other) const;
  inline Vector2& operator-=(const Vector2& other);
  inline Vector2 operator-() const;
  inline Vector2 operator*(float value) const;
  inline Vector2& operator*=(float value);
  inline Vector2 operator/(float value) const;
  inline Vector2& operator/=(float value);
  inline friend std::ostream& operator<<(std::ostream& os, const Vector2& v);

  float x;
  float y;
};

inline Vector2 Vector2::normalize() const
{
  float len = length();
  if(len > -0.0001 && len < 0.0001)
    return Vector2();
  return Vector2(x / len, y / len);
}

inline Vector2 Vector2::operator+(const Vector2& other) const
{
  return Vector2(x + other.x, y + other.y);
}

inline Vector2& Vector2::operator+=(const Vector2& other)
{
  x += other.x;
  y += other.y;

  return *this;
}

inline Vector2 Vector2::operator-(const Vector2& other) const
{
  return Vector2(x - other.x, y - other.y);
}

inline Vector2& Vector2::operator-=(const Vector2& other)
{
  x -= other.x;
  y -= other.y;

  return *this;
}

inline Vector2 Vector2::operator-() const
{
  return Vector2(-x, -y);
}

inline Vector2 Vector2::operator*(float value) const
{
  return Vector2(x * value, y * value);
}

inline Vector2& Vector2::operator*=(float value)
{
  x *= value;
  y *= value;

  return *this;
}

inline Vector2 Vector2::operator/(float value) const
{
  float inv = 1.0/value;
  return Vector2(x * inv, y * inv);
}

inline Vector2& Vector2::operator/=(float value)
{
  float inv = 1.0/value;
  x *= inv;
  y *= inv;

  return *this;
}

inline std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
  os << "[" << v.x << ", " << v.y << "]";
  return os;
}