#pragma once

#include "vector3.hpp"
#include "matrix.hpp"

class Camera
{
public:
  enum class CameraDirection { Forward, Back, Right, Left };

  Camera(const Vector3& position, const Vector3& forward, const Vector3& up);

  void setPosition(const Vector3& position);
  void setForward(const Vector3& forward);

  void rotateX(float amt);
  void rotateY(float amt);
  void move(CameraDirection direction, float amt);

  const Vector3& getForward() const;
  const Vector3& getRight() const;
  const Vector3& getUp() const;

  Matrix getViewMatrix() const;
private:
  void calculateForwardFromAngles();
  void calculateAngles();
  void calculateVectors();

  Vector3 position_;
  Vector3 forward_;
  Vector3 referenceUp_;
  Vector3 up_;
  Vector3 right_;

  float yaw_;
  float pitch_;
};