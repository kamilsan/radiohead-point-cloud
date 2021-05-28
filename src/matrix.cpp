#include "matrix.hpp"

#include <stdexcept>
#include <cmath>

Matrix::Matrix(std::vector<float> data)
{
  if(data.size() != 16)
    throw std::invalid_argument("Matrix data array should contain 16 elements!");

  for(int i = 0; i < 16; ++i)
    data_[i] = data[i];
}

Matrix Matrix::initIdentity()
{
  return Matrix({1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1});
}

Matrix Matrix::initScale(float sx, float sy, float sz)
{
  return Matrix({sx, 0, 0, 0,
                 0, sy, 0, 0,
                 0, 0, sz, 0,
                 0, 0, 0, 1});
}

Matrix Matrix::initTranslation(float tx, float ty, float tz)
{
  return Matrix({1, 0, 0, tx,
                 0, 1, 0, ty,
                 0, 0, 1, tz,
                 0, 0, 0, 1});
}

Matrix Matrix::initPerspective(float fov, float ar, float zNear, float zFar)
{
  float tanHalfFOV = std::tan(fov * 0.5);
  float zRange = zNear - zFar;
  return Matrix({1.0f / (tanHalfFOV * ar), 0, 0, 0,
                 0, 1.0f / tanHalfFOV, 0, 0,
                 0, 0, (-zNear - zFar) / zRange, 2 * zFar * zNear / zRange,
                 0, 0, 1, 0});
}

Matrix Matrix::initRotation(float rx, float ry, float rz)
{
  const float sinX = std::sin(rx);
  const float cosX = std::cos(rx);
  const float sinY = std::sin(ry);
  const float cosY = std::cos(ry);
  const float sinZ = std::sin(rz);
  const float cosZ = std::cos(rz);

  const Matrix Mx = Matrix({1, 0, 0, 0,
                            0, cosX, -sinX, 0,
                            0, sinX, cosX, 0,
                            0, 0, 0, 1});
  const Matrix My = Matrix({cosY, 0, sinY, 0,
                            0, 1, 0, 0,
                            -sinY, 0, cosY, 0,
                            0, 0, 0, 1});
  const Matrix Mz = Matrix({cosZ, -sinZ, 0, 0,
                           sinZ, cosZ, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1});

  return Mz*My*Mx;
}

const float* Matrix::getData() const
{
  return data_;
}

float Matrix::operator[](unsigned int index) const
{
  return data_[index];
}

float& Matrix::operator[](unsigned int index)
{
  return data_[index];
}

Matrix Matrix::operator+(const Matrix& other) const
{
  Matrix result{};
  for(int i = 0; i < 16; ++i)
    result.data_[i] = data_[i] + other.data_[i];

  return result;
}

Matrix Matrix::operator-() const
{
  Matrix result{};
  for(int i = 0; i < 16; ++i)
    result.data_[i] = -data_[i];
  
  return result;
}

Matrix Matrix::operator-(const Matrix& other) const
{
  Matrix result{};
  for(int i = 0; i < 16; ++i)
    result.data_[i] = data_[i] - other.data_[i];

  return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
  Matrix result{};
  for(int row = 0; row < 4; ++row)
  {
    for(int col = 0; col < 4; ++col)
    {
      float sum = 0;
      for(int r = 0; r < 4; ++r)
      {
        sum += data_[idx(r, row)]*other.data_[idx(col, r)];
      }
      result.data_[idx(col, row)] = sum;
    }
  }
  
  return result;
}

Matrix Matrix::operator*(float value) const
{
  Matrix result{};
  for(int i = 0; i < 16; ++i)
    result.data_[i] = data_[i]*value;

  return result;
}