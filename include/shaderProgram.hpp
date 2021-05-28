#pragma once

#include <glad/glad.h>
#include <string>

class ShaderProgram
{
public:
  explicit ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);

  void use() const;
  GLuint getUniformLocation(const std::string& name) const;
private:
  GLuint program_;

  std::string getShaderFileContet(const char* shaderFile) const;
  GLuint createCompiledShader(const char* source, unsigned int shaderType) const;
};