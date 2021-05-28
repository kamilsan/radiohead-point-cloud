#pragma once

#include <vector>
#include <string>

struct PointCloud
{
  PointCloud(): vbo(), size_(0) {}

  void addPoint(float x, float y, float z, float intensity);
  static std::vector<PointCloud> loadFrames(const std::string& dir, const unsigned int numFrames);

  inline size_t size() const { return size_; }

  std::vector<float> vbo;
private:
  size_t size_;
};