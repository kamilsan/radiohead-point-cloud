#include "shaderProgram.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile)
{
  std::string vertexShaderSource = getShaderFileContet(vertexShaderFile);
  std::string fragmentShaderSource = getShaderFileContet(fragmentShaderFile);

  auto vertexShader = createCompiledShader(vertexShaderSource.c_str(), GL_VERTEX_SHADER);
  auto fragmentShader = createCompiledShader(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);

  program_ = glCreateProgram();
  glAttachShader(program_, vertexShader);
  glAttachShader(program_, fragmentShader);
  glLinkProgram(program_);

  int result = 0;
  glGetProgramiv(program_, GL_LINK_STATUS, &result);
  if(!result) 
  {
    char infoLog[512];
    glGetProgramInfoLog(program_, 512, NULL, infoLog);
    std::stringstream errorMsgStream;
    errorMsgStream << "An error occured during linking shader program!" << std::endl << infoLog;
    throw std::runtime_error(errorMsgStream.str());
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void ShaderProgram::use() const
{
  glUseProgram(program_);
}

GLuint ShaderProgram::getUniformLocation(const std::string& name) const
{
  return glGetUniformLocation(program_, name.c_str());
}

std::string ShaderProgram::getShaderFileContet(const char* shaderFile) const
{
  std::ifstream file(shaderFile);
  std::stringstream stream;
  stream << file.rdbuf();
  file.close();

  return stream.str();
}

GLuint ShaderProgram::createCompiledShader(const char* source, unsigned int shaderType) const
{
  auto shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  char infoLog[512];
  int result = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if(!result)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::stringstream errorMsgStream;
    errorMsgStream << "An error occured during shader compilation!" << std::endl << infoLog;
    throw std::runtime_error(errorMsgStream.str());
  }

  return shader;
}