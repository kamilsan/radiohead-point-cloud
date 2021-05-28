#pragma once

#include "pointCloud.hpp"
#include "camera.hpp"
#include "shaderProgram.hpp"
#include "matrix.hpp"

class PointCloudRenderer
{
public:
  PointCloudRenderer();

  void setPointCloud(const PointCloud& pointCloud);
  void render(const Camera& camera, const Matrix& projectionMatrix, const Matrix& modelMatrix);

private:
  ShaderProgram shader_;

  GLuint modelMatrixLocation_;
  GLuint viewMatrixLocation_;
  GLuint projectionMatrixLocation_;

  GLuint vao_;
  GLuint vbo_;
  unsigned int count_ = 0;
};