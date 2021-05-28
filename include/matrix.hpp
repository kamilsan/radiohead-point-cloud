#pragma once

#include <vector>
#include <iostream>

class Matrix
{
public:
  Matrix() = default;
  Matrix(std::vector<float> data);

  static Matrix initIdentity();
  static Matrix initScale(float sx, float sy, float sz);
  static Matrix initTranslation(float tx, float ty, float tz);
  static Matrix initRotation(float rx, float ry, float rz);
  static Matrix initPerspective(float fov, float ar, float zNear, float zFar);

  const float* getData() const;

  float operator[](unsigned int index) const;
  float& operator[](unsigned int index);
  Matrix operator+(const Matrix& other) const;
  Matrix operator-() const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  Matrix operator*(float value) const;

  inline friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
private:
  inline int idx(int i, int j) const;

  float data_[16];
};

inline int Matrix::idx(int i, int j) const
{
  return 4*j + i;
}

inline std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
  for(int j = 0; j < 4; ++j)
  {
    os << '[';
    for(int i = 0; i < 4; ++i)
    {
      os << m[m.idx(i, j)];
      if(i != 3)
        os << ", ";
    }
    os << ']';
    if(j != 3)
      os << '\n';
  }

  return os;
}