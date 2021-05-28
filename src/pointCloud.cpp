#include "pointCloud.hpp"

#include <fstream>

void PointCloud::addPoint(float x, float y, float z, float intensity)
{
  vbo.emplace_back(x);
  vbo.emplace_back(y);
  vbo.emplace_back(z);
  vbo.emplace_back(intensity);

  size_ += 1;
}

std::vector<PointCloud> PointCloud::loadFrames(const std::string& dir, const unsigned int numFrames)
{
  std::vector<PointCloud> frames;

  for(unsigned int i = 1; i <= numFrames; ++i)
  {
    const auto filename = dir + "/" + std::to_string(i) + ".csv";
    auto file = fopen(filename.c_str(), "r");

    PointCloud cloud;

    float x, y, z, intensity;
    while(std::fscanf(file ,"%f,%f,%f,%f\n", &x, &y, &z, &intensity) > 0)
    {
      cloud.addPoint(x, y, z, intensity / 255.0f);
    }

    fclose(file);
    frames.emplace_back(cloud);
  }

  return frames;
}