#pragma once

#include "vector3.hpp"
#include "vector2.hpp"

class Vertex
{
public:
  Vertex(const Vector3& position, const Vector2& texCoord): position_(position), texCoord_(texCoord) {}

  inline void setPosition(const Vector3& position) { position_ = position; }
  inline void setColor(const Vector2& texCoord) { texCoord_ = texCoord; }

  inline const Vector3& getPosition() const { return position_; }
  inline const Vector2& getTexCoord() const { return texCoord_; }
  inline Vector3& getPosition() { return position_; }
  inline Vector2& getTexCoord() { return texCoord_; }

private:
  Vector3 position_;
  Vector2 texCoord_;
};