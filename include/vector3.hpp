#pragma once

#include <cmath>
#include <iostream>

struct Vector3
{
  Vector3(): x(0), y(0), z(0) {}
  Vector3(float x, float y, float z): x(x), y(y), z(z) {}

  inline float length() const { return std::sqrt(x*x + y*y + z*z); };
  inline float lengthSq() const { return x*x + y*y + z*z; };
  inline Vector3 normalize() const;
  inline float dot(const Vector3& other) const { return x*other.x + y*other.y + z*other.z; };
  inline Vector3 cross(const Vector3& other) const;

  inline Vector3 operator+(const Vector3& other) const;
  inline Vector3& operator+=(const Vector3& other);
  inline Vector3 operator-(const Vector3& other) const;
  inline Vector3& operator-=(const Vector3& other);
  inline Vector3 operator-() const;
  inline Vector3 operator*(float value) const;
  inline Vector3& operator*=(float value);
  inline Vector3 operator/(float value) const;
  inline Vector3& operator/=(float value);
  inline friend std::ostream& operator<<(std::ostream& os, const Vector3& v);

  float x;
  float y;
  float z;
};

inline Vector3 Vector3::normalize() const
{
  float len = length();
  if(len > -0.0001 && len < 0.0001)
    return Vector3();
  return Vector3(x / len, y / len, z / len);
}

inline Vector3 Vector3::cross(const Vector3& other) const
{
  return Vector3(y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
}

inline Vector3 Vector3::operator+(const Vector3& other) const
{
  return Vector3(x + other.x, y + other.y, z + other.z);
}

inline Vector3& Vector3::operator+=(const Vector3& other)
{
  x += other.x;
  y += other.y;
  z += other.z;

  return *this;
}

inline Vector3 Vector3::operator-(const Vector3& other) const
{
  return Vector3(x - other.x, y - other.y, z - other.z);
}

inline Vector3& Vector3::operator-=(const Vector3& other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;

  return *this;
}

inline Vector3 Vector3::operator-() const
{
  return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator*(float value) const
{
  return Vector3(x * value, y * value, z * value);
}

inline Vector3& Vector3::operator*=(float value)
{
  x *= value;
  y *= value;
  z *= value;

  return *this;
}

inline Vector3 Vector3::operator/(float value) const
{
  float inv = 1.0/value;
  return Vector3(x * inv, y * inv, z * inv);
}

inline Vector3& Vector3::operator/=(float value)
{
  float inv = 1.0/value;
  x *= inv;
  y *= inv;
  z *= inv;

  return *this;
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
  os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
  return os;
}