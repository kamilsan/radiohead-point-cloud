#include "pointCloudRenderer.hpp"

PointCloudRenderer::PointCloudRenderer(): shader_("res/vertexShader.vs.glsl", "res/fragmentShader.fs.glsl")
{
  shader_.use();

  modelMatrixLocation_ = shader_.getUniformLocation("modelMatrix");
  viewMatrixLocation_ = shader_.getUniformLocation("viewMatrix");
  projectionMatrixLocation_ = shader_.getUniformLocation("projectionMatrix");

  glGenBuffers(1, &vbo_);
  glGenVertexArrays(1, &vao_);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  
  glBindVertexArray(0);
}

void PointCloudRenderer::setPointCloud(const PointCloud& pointCloud)
{
  glBindVertexArray(vao_);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, pointCloud.vbo.size() * sizeof(float), pointCloud.vbo.data(), GL_DYNAMIC_DRAW);
  count_ = pointCloud.size();

  glBindVertexArray(0);
}

void PointCloudRenderer::render(const Camera& camera, const Matrix& projectionMatrix, const Matrix& modelMatrix)
{
  shader_.use();

  glUniformMatrix4fv(projectionMatrixLocation_, 1, GL_TRUE, projectionMatrix.getData());
  glUniformMatrix4fv(viewMatrixLocation_, 1, GL_TRUE, camera.getViewMatrix().getData());
  glUniformMatrix4fv(modelMatrixLocation_, 1, GL_TRUE, modelMatrix.getData());

  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, 0, count_);
  glBindVertexArray(0);
}
